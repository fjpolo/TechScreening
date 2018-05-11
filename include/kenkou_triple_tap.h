
#ifndef KENKOU__TRIPLE_TAP__H
#define KENKOU__TRIPLE_TAP__H

#include <stdint.h>
#include <stdbool.h>
#include <time.h>

#define KENKOU__TRIPLE_TAP_CHANNELS 10
#define TRIPLE_TAP_MAX_DELAY 1000
#define TRIPLE_TAP_MAX_DUR   (TRIPLE_TAP_MAX_DELAY * 2) + 100
//#define TRIPLE_TAP_MAX_DUR   (TRIPLE_TAP_MAX_DELAY)
// TRIPLE_TAP_DUR must be at least 2x TRIPLE_TAP_DELAY
#if TRIPLE_TAP_MAX_DUR < (2*TRIPLE_TAP_MAX_DELAY)
# warning "TRIPLE_TAP_MAX_DUR must be at least 2 times TRIPLE_TAP_MAX_DELAY"
#endif

bool checkTripleTap(uint8_t channel
        	   , time_t epochTime
        	   , uint16_t additionalMillis);
bool checkTime(time_t lastSec, time_t actualSec, uint16_t lastmSec, uint16_t actualmSec);
void updateTime(struct timespec *time, time_t Sec, uint16_t mSec);
#endif
