/**
 * This file is for easily mocking functions
 */
#ifndef __UNIT_TEST_MOCKING__
#define __UNIT_TEST_MOCKING__
#ifdef UNIT_TEST

#include <stdlib.h>

#define _GENERATE_MOCK_NAME(name)  MOCK_##name


/* Directives for creating Mock Functions */
#define MOCK_FUNC(name, ...)  int NumberTimesMOCK##name##Called; \
                              void _GENERATE_MOCK_NAME(name)(__VA_ARGS__) \
                              { \
                                NumberTimesMOCK##name##Called++; \
                              }

/* Allows for users to specify custom internal workings of a mock function */
#define MOCK_CUSTOM(type, name, args, ...) int NumberTimesMOCK##name##Called; \
                                            type _GENERATE_MOCK_NAME(name)args \
                                            { \
                                              NumberTimesMOCK##name##Called++; \
                                              __VA_ARGS__ \
                                            }


/* Used to check if a mock function was called */
#define TEST_ASSERT_MOCK_CALLED(name)               TEST_ASSERT_TRUE_MESSAGE(WAS_MOCK_CALLED(name), "Mock Function '" #name "' not called")
#define TEST_ASSERT_MOCK_CALLED_COUNT(name, n)      TEST_ASSERT_TRUE_MESSAGE(WAS_MOCK_CALLED_COUNT(name, n), "Mock Function '" #name "' not called " #n " times")

#define WAS_MOCK_CALLED(name)               (NumberTimesMOCK##name##Called > 0)
#define WAS_MOCK_CALLED_COUNT(name, n)      (NumberTimesMOCK##name##Called == n)

/* Resets a mock for another test */
#define RESET_MOCK(name)  NumberTimesMOCK##name##Called = 0;

#define MOCK(name)  _GENERATE_MOCK_NAME(name) /* Used to access mock functions */


#endif
#endif