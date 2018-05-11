#include "../include/unity.h"
#include"../include/kenkou_triple_tap.h"


/****************************
* Global Variables
*****************************/
int counter;
struct timespec lastTime;

// Test function checkTime above threshold
void test_aboveThreshold(void)
{
	// Test 1001mS
	TEST_ASSERT_FALSE(checkTime(918, 919, 153, 154));
	// Test 1100mS
	TEST_ASSERT_FALSE(checkTime(918, 919, 153, 253));
	// Test 2500mS
	TEST_ASSERT_FALSE(checkTime(918, 920, 153, 653));
}

// Test function checkTime below threshold
void test_belowThreshold(void)
{
	// Test 100mS
	TEST_ASSERT_TRUE(checkTime(918, 918, 153, 253));
	// Test 500mS
	TEST_ASSERT_TRUE(checkTime(918, 918, 153, 653));
	// Test 999mS
	TEST_ASSERT_TRUE(checkTime(918, 919, 153, 152));
}

// Test checkTripleTap for a normal tap
void test_TripleTapdoesnotOccur(void)
{
	//
	TEST_ASSERT_FALSE(checkTripleTap(10, 2, 564));
}

// Test checkTripleTap for a second tap
void test_SecondTaptOccurs(void)
{
	//
	TEST_ASSERT_FALSE(checkTripleTap(10, 0, 333));
}

// Test checkTripleTap when a triple tap occurs
void test_TripleTapOccurs(void)
{
	//
	TEST_ASSERT_TRUE(checkTripleTap(10, 0, 222));
}

int main(void)
{
	// Need to initialize counter and lastTime;
	counter = 0;
	lastTime.tv_sec = 0;
	lastTime.tv_nsec = 0;
	// Begin
	UNITY_BEGIN();
	// Test CheckTime
	RUN_TEST(test_aboveThreshold);
	RUN_TEST(test_belowThreshold);
	// Test checkTripleTap
	RUN_TEST(test_TripleTapdoesnotOccur);	// normal tap
	counter = 1;
	RUN_TEST(test_SecondTaptOccurs);		// second tap
	counter = 3;
	RUN_TEST(test_TripleTapOccurs);			// triple tap
	// End
	return UNITY_END();
}
