//Title - application.h
//Purpose - Contains classes for main operations of the task.
//Limitations - none
//Special Requirements - none 
#ifndef APPLICATION_H
#define APPLICATION_H

// The 'Timer' object configures the system and runs the data processing operation
// at a specific time interval.
// Each of the 'Timer' has the member functions listed below.
//   Timer - constructor to configure the system and run the task.
//   CheckTimer - Check if one tick has elapsed from SysTick using a flag.
//   ChangeFreq - Change the time interval between processing operations.
// Each of the 'Timer' has the members listed below.
//   TickFreq - Stores the time interval between each data processing operation
//   Result - Stores result after data processing operation
class Timer	{
	public:
		Timer();
		bool CheckTimer();
		void ChangeFreq();
	private:
		uint32_t TickFreq;
		uint32_t Result;
};

#endif