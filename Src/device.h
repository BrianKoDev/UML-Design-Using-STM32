//Title - device.h
//Purpose - Contains classes for device driver layer.
//Limitations - none
//Special Requirements - none 
#ifndef DEVICE_H
#define DEVICE_H

//Define database size
#define DATABASE_COLS 16
#define DATABASE_ROWS 20

extern int8_t Database[][DATABASE_COLS]; //Linkage of database from "database.h"

// The 'ProcessData' object accesses the database and perform
// data processing operation.
// Each of the 'ProcessData' has the member functions listed below.
//   ProcessData - Constructor to initialize the addresses pointing to the database
//   ProcessRow - data processing of the current row
//   NextRow - change 'row' to point to the next database row
// Each of the 'ProcessData' has the members listed below.
//   database - address of the start of the database
//   row - address of current database row being processed
class ProcessData {
 public:
	ProcessData(int8_t*);
	int32_t ProcessRow();
  void NextRow();
 private:
	int8_t* database;
  int8_t* row;
};

// The 'ModifyMemory' object access an area of memory that keeps the results of the processing.
// Each of the 'ModifyMemory' has the member functions listed below.
//   ModifyMemory - constructor for initial location is the start of the 'Data' data store
//   StoreResult - put an item in the data store
//   EmptyResults - reset to point to the start of the data store
// Each of the 'ModifyMemory' has the members listed below.
//   Data - space to store results of processing each row
//   number - current entry being accessed in the 'Data' data store
class ModifyMemory {
 public:
	ModifyMemory();
	void StoreResult(int32_t);
  void EmptyResults();
 private:
	int32_t Data[DATABASE_ROWS];
  uint32_t number;
};

// The 'UserButton' object checks if the button has been pressed.
// Each of the 'UserButton' has the member functions listed below.
//   CheckButton - Checks and resets the status of the button flag set by ISR
class UserButton {
	public:
		bool CheckButton();
};

// The 'LEDs' object specify LED actions and access through a bit pattern mask .
// Each of the 'LEDs' has the member functions listed below.
//   LEDs - set up the bit pattern mask specifying the LED pin 
//   on - turns led on
//   off - turns led off
//   toggle - toggles led
// Each of the 'LEDs' has the members listed below.
//   bit_pattern - the bit pattern mask specifying the LED pin
class LEDs {
	public:
	  LEDs (uint16_t);
  	void on();
    void off();
    void toggle();
	private:
		uint16_t bit_pattern;
};

// The 'DisplayIndicators' object specify sets of LEDs actions based on states of the system.
// Each of the 'DisplayIndicator' has the member functions listed below.
//   ResultOff - Turn off all blue and orange LEDs 
//	 Result0 - Turn on orange LEDs
//   Result500 - Turn on blue LEDs
//   MemoryDeleted - Toggle green LEDs
//   ProcessingSlowed - Turn on red LEDs
//	 ProcessingNormal - Turn off red LEDs
class DisplayIndicators	{
	public:
  	void ResultOff();
    void Result0();
    void Result500();
	  void MemoryDeleted();
		void ProcessingSpeed();

};
#endif