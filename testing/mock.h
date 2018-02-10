/**
 * This file is for easily mocking functions
 */
#ifndef __UNIT_TEST_MOCKING__
#define __UNIT_TEST_MOCKING__
#ifdef UNIT_TEST

#include <stdlib.h>

/* Helper directives to avoid typing things out multiple times */
#define MOCK(name)                  MOCK_##name
#define _MOCK_COUNTER_NAME(name)    NumberTimesMOCK##name##Called
#define _MOCK_TMP_NAME(name) 		    MOCK_TEMP_##name##_TEMP

#define _INC_MOCK(name)   _MOCK_COUNTER_NAME(name)++;
#define RESET_MOCK(name)  _MOCK_COUNTER_NAME(name) = 0;


/* Helpers */
#define _C(a, ...)	_PRIMITIVE_CAT(a, __VA_ARGS__)
#define _PRIMITIVE_CAT(a, ...) 	a ## __VA_ARGS__
#define _NUM_ARGS(P1, P2, P3, P4, P5, P6, P7, P8, P9, P10, P11, P12, P13, P14, P15, Pn, ...) Pn
#define NUM_ARGS(...) _NUM_ARGS(-1, ##__VA_ARGS__, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0)


/* Directives for creating Mock Functions */
#define MOCK_FUNC(name, ...) 	*_MOCK_TMP_NAME(name); \
								              _C(__MOCK_FUNC_, NUM_ARGS(__VA_ARGS__))(name, __typeof__(*_MOCK_TMP_NAME(name)), __VA_ARGS__)

#define __MOCK_FUNC_0(name, type)             __MOCK_FUNC_2(name, type, (void), {})
#define __MOCK_FUNC_1(name, type, args)			  __MOCK_FUNC_2(name, type, args, {})

#define __MOCK_FUNC_2(name, type, args, code) int _MOCK_COUNTER_NAME(name); \
                                              type MOCK(name)args \
                                              { \
                                                _INC_MOCK(name); \
                                                code \
                                              }


/* Used to check if a mock function was called */
#define TEST_ASSERT_MOCK_CALLED(name)               TEST_ASSERT_TRUE_MESSAGE(WAS_MOCK_CALLED(name), "Mock Function '" #name "' not called")
#define TEST_ASSERT_MOCK_CALLED_COUNT(name, n)      TEST_ASSERT_TRUE_MESSAGE(WAS_MOCK_CALLED_COUNT(name, n), "Mock Function '" #name "' not called " #n " times")

#define WAS_MOCK_CALLED(name)               (_MOCK_COUNTER_NAME(name) > 0)
#define WAS_MOCK_CALLED_COUNT(name, n)      (_MOCK_COUNTER_NAME(name) == n)



#endif
#endif