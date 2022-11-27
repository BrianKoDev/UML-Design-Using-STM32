//Title - application.cpp
//Purpose - Contains main operations of the task. 
//Limitations - none
//Special Requirements - none

#include <cstdint>
#include "application.h"
#include "device.h"
extern "C" { 
	#include "gpio_setup.h"  // for calling function SysTick_Handler
}

//Specify the time intervals during normal and slowed operation
#define NormalFreq 2500000 //250ms
#define SlowFreq 5000000   //500ms

volatile bool Timer_flag; //flag to indicate if one tick has elapsed

// This construction initizes the GPIO, creates objects and runs the loop
// for the processing task.
//   Arguments:
//     None 
//   Returns: 
//     None
Timer::Timer(){
	gpio_setup(); //Setup GPIO
	TickFreq = NormalFreq;
	SysTick_Config(TickFreq); //Configure Systick to operate at Normal time interval
	
	//Creates objects
	UserButton U;
	ProcessData P(*Database);
	ModifyMemory M;
	DisplayIndicators D;

	while (true) {
		if (U.CheckButton()){ChangeFreq();D.ProcessingSpeed();} //Check if button is pressed and change time interval
		
		if (CheckTimer()){										//Check if one tick has elapsed
			M.EmptyResults();										//Delete stored results
			D.MemoryDeleted(); 								 	//Indicate memory has been deleted to user
			D.ResultOff(); 											//Turn results LEDs off
			Result = P.ProcessRow();						//Process data and store in member function
			if (Result>500){D.Result500();} 		//Turn on LEDs when result is greater than 500
			if (Result==0){D.Result0();} 	//Turn on LEDs when result is 0
			M.StoreResult(Result);							//Store result in memory
			P.NextRow();												//Move to next row of data to be processed
		}
	}
}

// This function checks the value of the timer flag
// resets the flag if true and returns the current flag value.
//   Arguments:
//     None 
//   Returns: 
//     bool - Status of timer flag
bool Timer::CheckTimer()
{
	if (Timer_flag) {Timer_flag = false; return true;}
	
	else {return false;}
}

// This function changes the timer interval between each data processing operation
// and calls additional functions to indicate the current processing time interval
//   Arguments:
//     None 
//   Returns: 
//     None
void Timer::ChangeFreq(){
	
	if (TickFreq == NormalFreq){TickFreq = SlowFreq;} //Change to longer time interval and display in hardware
	else if (TickFreq == SlowFreq){TickFreq = NormalFreq;} //Change to normal time interval and display in hardware
	SysTick_Config(TickFreq); //Change Tick Frequency
}

// This function handles the system tick timer interrupt and sets a flag if its called
//   Arguments:
//     None 
//   Returns: 
//     None
void SysTick_Handler(void)
{
		Timer_flag = true;
}