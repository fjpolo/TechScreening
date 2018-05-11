#include"../include/kenkou_triple_tap.h"
#include<stdio.h>

/****************************
* Global Variables
*****************************/
extern int counter;
extern struct timespec lastTime;


/**@brief Function to detect triple tap for various channels.
*
* @details For a given channel, this function checks a relative time in seconds and ms.
* if the current and two previous calls to the channel fall within TRIPLE_TAP_MAX_DUR,
* and are each a maximum of TRIPLE_TAP_MAX_DELAY apart from the last,
* the function will return True.
* (Optional) if true internally trigger a callback if set by
* setTripleTapCallback(uint8t channel, void* callback)
*
*Conditions
* @pre
* TRIPLE_TAP_MAX_DELAY is set before compile time
* TRIPLE_TAP_MAX_DUR is set at least 2x TRIPLE_TAP_MAX_DELAY before compile time
* (optional)tripleTapCallback is set with setTripleTapCallback
*
* @post
* True or false have been returned.
* All recorded taps are cleared when a triple tap state is encountered
* (to prevent a following 4th tap from triggering another triple tap).
*
* @inv
* TRIPLE_TAP_DUR must be at least 2x TRIPLE_TAP_DELAY
* otherwise a warning is provided at compile time
*
*Parameters
* @param[in] uint8_t tripleTapChannel, time_t epochTime, uint16_t additionalMillis.
*
* @return True if the last three calls to the specified channel qualify as a triple tap,
* and no triple tap has been executed for the oldest two.
* False otherwise.
*/
bool checkTripleTap(uint8_t channel, time_t timeSec, uint16_t timeMs){
	bool ret = false;
	// Check relative time
	if(checkTime(lastTime.tv_sec, timeSec,(lastTime.tv_nsec/1000000), timeMs) && counter < 3) counter++;
	// Check counter
	else if(counter == 3){ 
		counter = 0;
		ret = true;
	}
	else counter = 0;
	// Update lastTime
	updateTime(&lastTime, timeSec, timeMs);
	// Return value
	return ret;
}

/**@brief Function to test if relative time is less than TRIPLE_TAP_MAX_DELAY
*
* @details Checks if the difference between the actual tap and last tap does not
* exceed the time of TRIPLE_TAP_MAX_DELAY.
*
*Parameters
* @param[in] 	lastSec, actualSec, lastmSec, actualmSec
*
* @return true if it does no exceed the time. false if it exceeds the time.
*/
bool checkTime(time_t lastSec, time_t actualSec, uint16_t lastmSec, uint16_t actualmSec){
	uint16_t time = ((actualSec-lastSec)*1000)+(actualmSec-lastmSec);
	if(time <= TRIPLE_TAP_MAX_DELAY) return true;
	else return false;
}



/**@brief Function to update lastTime
*
* @details lastTime needs to be updated every tap, updating seconds and nanoseconds.
*
*Parameters
* @param[in] *time, Sec, mSec
*
* @return nothing.
*
*/
void updateTime(struct timespec *time, time_t Sec, uint16_t mSec){
	time->tv_sec = Sec;
	time->tv_nsec = mSec*1000000;
}
