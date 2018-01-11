/**
 * This file is home to the unit tests for the drivers. 
 * 
 * It should just test the basic functionality provided by the library.
 * Nothing specific like microcontrollers or SPI, just basic PIN/PORT control.
 * 
 * Author: Michael Rouse
 */
// gcc drivers/tests/tests.c drivers/microcontrollers/microcontroller.c drivers/microcontrollers/test/test_microcontroller.c drivers/tests/unity/unity.c -o tests.out -D UNIT_TEST

#ifdef UNIT_TEST
#include <stdlib.h>
#include "unity/unity.h"
#include "../solarcar.h" // See, this is all you need to do to use the drivers :)

// Unity will call the setUp function BEFORE every test, so we use this function to 
// reset all of our registers to default values
void setUp(void) 
{ 
  *port1_dir_reg = 0x00; 
  *port1_out_reg = 0x00; 
  *port1_in_reg = 0x00; 
  *port1_sel_reg = 0x00; 
}



/**
 * Test the functionality of setting a pin as OUTPUT 
 */
void test_setPinAsOutput(void) 
{ 
  TEST_ASSERT_BITS_LOW(BIT0, *port1_dir_reg); // Confirm that P1.0 is HIGH to begin with 

  setPinMode(P1_0, OUTPUT); // Set the pin as output (should make it HIGH)

  TEST_ASSERT_BITS_HIGH(BIT0, *port1_dir_reg); // Confirm that P1.0 is now HIGH
}


/**
 * Test setting a pin as INPUT 
 */
void test_setPinAsInput(void) 
{ 
  TEST_ASSERT_BITS_LOW(BIT0, *port1_dir_reg); // Confirm it's LOW to begin with 
  setPinMode(P1_0, OUTPUT);
  TEST_ASSERT_BITS_HIGH(BIT0, *port1_dir_reg); // Confirm that it's now HIGH

  setPinMode(P1_0, INPUT); 

  TEST_ASSERT_BITS_LOW(BIT0, *port1_dir_reg); // Should be LOW after being marked as INPUT
}


/**
 * Test setting multiple pins 
 */
void test_setMultiplePins(void) 
{ 
  TEST_ASSERT_BITS_LOW(BIT0, *port1_dir_reg); 
  TEST_ASSERT_BITS_LOW(BIT1, *port1_dir_reg); 

  setPinMode(P1_0, OUTPUT); 
  setPinMode(P1_1, OUTPUT); 
  
  TEST_ASSERT_BITS_HIGH(BIT0, *port1_dir_reg); 
  TEST_ASSERT_BITS_HIGH(BIT1, *port1_dir_reg);
}



/**
 * The main function starts the Unity framework and runs all of the tests 
 */
int main(void) 
{ 
  UNITY_BEGIN(); 

  RUN_TEST(test_setPinAsOutput);
  RUN_TEST(test_setPinAsInput);
  RUN_TEST(test_setMultiplePins);

  return UNITY_END();
}


#endif