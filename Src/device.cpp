//Title - device.cpp
//Purpose - Contains member functions for device driver layer.
//Limitations - none
//Special Requirements - none 
#include <cstdint>
#include "device.h"
#include "database.h"
extern "C" { 
	#include "gpio_setup.h"  // set up input/output ports and interrupts
}
#include <cmath>

// interrupt service routine called when button pressed
void HAL_GPIO_EXTI_Callback(uint16_t); 

// indicates when input is received
volatile bool IP_flag = false;

// number of LEDs on the board
#define NUM_LEDs 8

// define the LEDs
LEDs LED[NUM_LEDs] = {LED8,LED6,LED4,LED3,LED5,LED7,LED9,LED10};

// Set up a pointer to the database and start at row 0
//   Arguments:
//     (1) Start of the database values 
//   Returns: 
//     None
ProcessData::ProcessData(int8_t* DB) {
	database = DB;
	row = database;
}

// processing of one row of the database
//   Arguments:
//     (1) none
//   Returns: 
//     a single value that is the output of all the processing
int32_t ProcessData::ProcessRow() {
	int32_t sum = 0;
	for(uint32_t i=0;i<DATABASE_COLS;i++) {
	  for(uint32_t j=i;j<DATABASE_COLS;j++) {		
		  sum += sqrt(row[i]*row[1] + row[j]*row[j]);
		}
	}
	return sum;
}

// read database rows in a circular manner
//   Arguments:
//     none
//   Returns: 
//     none
void ProcessData::NextRow() {
	row = row + DATABASE_COLS;
  if (row >= database + DATABASE_ROWS*DATABASE_COLS) {
		row = database;
	}
}

// Constructor to set beginning of memory
//   Arguments:
//     none
//   Returns: 
//     none
ModifyMemory::ModifyMemory() {
	number = 0;
}

// Add a result to the next location in memory
//   Arguments:
//     (1) - the value to add to the memory area
//   Returns: 
//     none
void ModifyMemory::StoreResult(int32_t res) {
	Data[number] = res;
	__disable_irq(); //Disable IRQ to protect shared resource
	number++;
	__enable_irq(); //Enable IRQ
}

// Empty by just going back to start of the buffer
//   Arguments:
//     none
//   Returns: 
//     none
void ModifyMemory::EmptyResults() {
	number = 0;
}

// Check and reset when interrupt flag is set 
//   Arguments:
//     none
//   Returns: 
//     bool - status of flag
bool UserButton::CheckButton()
{
	if (IP_flag) {IP_flag = false; return true;}
	else {return false;}
}

// Configure an LED by connecting to a specific pin
//   Arguments:
//     bit_pattern - the bit pattern mask specifying the LED pin
//   Returns: 
//     none
LEDs::LEDs(uint16_t _bit_pattern) {
	bit_pattern = _bit_pattern;
	off();
}

// Turn on an LED
//   Arguments:
//     none
//   Returns: 
//     none
void LEDs::on()
{
  GPIOE->ODR = GPIOE->ODR | (uint16_t) bit_pattern;
}

// Turn off an LED
//   Arguments:
//     none
//   Returns: 
//     none
void LEDs::off()
{
  GPIOE->ODR = GPIOE->ODR & ~((uint16_t) bit_pattern);
}

// Toggle an LED 
//   Arguments:
//     none
//   Returns: 
//     none
void LEDs::toggle()
{
  GPIOE->ODR = GPIOE->ODR ^ ((uint16_t) bit_pattern);
}

// Turn off all results LEDs
//   Arguments:
//     none
//   Returns: 
//     none
void DisplayIndicators::ResultOff()
{
  LED[0].off();
	LED[4].off();
	LED[2].off();
	LED[6].off();
}

// Turn on orange LEDs
//   Arguments:
//     none
//   Returns: 
//     none
void DisplayIndicators::Result0()
{
	LED[0].on();
	LED[4].on();
}

// Turn on Blue LEDs
//   Arguments:
//     none
//   Returns: 
//     none
void DisplayIndicators::Result500()
{
	LED[2].on();
	LED[6].on();
}

// Toggle Green LEDs
//   Arguments:
//     none
//   Returns: 
//     none
void DisplayIndicators::MemoryDeleted()
{
	LED[1].toggle();
	LED[5].toggle();
}

// Turn on Red LEDs
//   Arguments:
//     none
//   Returns: 
//     none
void DisplayIndicators::ProcessingSpeed()
{
	LED[3].toggle(); 
	LED[7].toggle();
}


// Interrupt service routine for handling Port A interrupts
//   Arguments:
//     (1) - the pin generating the input
//   Returns: 
//     none
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	// check the user button has generated the interrupt
  if(GPIO_Pin == GPIO_PIN_0) {IP_flag = true;}
}