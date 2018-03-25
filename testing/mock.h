/**
 * This file is for easily mocking functions
 */
#ifdef UNIT_TEST
#include <stdlib.h>
#include "../datatypes.h"


/* Mocking Functions in Unit Tests */
#ifndef __FUNCTION_MOCKING__
#define __FUNCTION_MOCKING__

#define MOCK(name)                  MOCK_##name
#define _MOCK_COUNTER_NAME(name)    NumberTimesMOCK##name##Called
#define _MOCK_TMP_NAME(name) 		    MOCK_TEMP_##name##_TEMP

#define _INC_MOCK(name)             _MOCK_COUNTER_NAME(name)++;
#define RESET_MOCK(name)            _MOCK_COUNTER_NAME(name) = 0;



#define MOCK_FUNC(name, ...) 	*_MOCK_TMP_NAME(name); \
								              CAT(__MOCK_FUNC_, NUM_ARGS(__VA_ARGS__))(name, __typeof__(*_MOCK_TMP_NAME(name)), __VA_ARGS__)

#define __MOCK_FUNC_0(name, type)             __MOCK_FUNC_2(name, type, (void), {})
#define __MOCK_FUNC_1(name, type, args)			  __MOCK_FUNC_2(name, type, args, {})

#define __MOCK_FUNC_2(name, type, args, code) int _MOCK_COUNTER_NAME(name); \
                                              static type MOCK(name)args \
                                              { \
                                                _INC_MOCK(name); \
                                                code \
                                              }

/* Used to check if a mock function was called */
#define TEST_ASSERT_MOCK_CALLED(name)               TEST_ASSERT_TRUE_MESSAGE(WAS_MOCK_CALLED(name), "Mock Function '" #name "' not called")
#define TEST_ASSERT_MOCK_CALLED_COUNT(name, n)      TEST_ASSERT_TRUE_MESSAGE(WAS_MOCK_CALLED_COUNT(name, n), "Mock Function '" #name "' not called " #n " times")
#define TEST_ASSERT_MOCK_NOT_CALLED(name)           TEST_ASSERT_MOCK_CALLED_COUNT(name, 0)

#define WAS_MOCK_CALLED(name)                       (_MOCK_COUNTER_NAME(name) > 0)
#define WAS_MOCK_CALLED_COUNT(name, n)              (_MOCK_COUNTER_NAME(name) == n)

#define MOCK_CALLED_COUNT(name)                     (_MOCK_COUNTER_NAME(name))

#endif



/* Mocking Registers */
#undef MOCK_REGISTER
#ifdef RUN_SPEC_FILE_LIKE_C_FILE
  /* C File */
  #define MOCK_REGISTER(r)      vuint8_t r;
#else
  /* Header File */
  #define MOCK_REGISTER(r)      extern vuint8_t r;
#endif

#undef MOCK_REGISTERS
#define MOCK_REGISTERS(...)   EVAL256(MAP(MOCK_REGISTER, __VA_ARGS__))



/* Mock Constants */
#undef MOCK_CONSTANT
#undef MOCK_CONSTANTS
#ifndef RUN_SPEC_FILE_LIKE_C_FILE
  /* Header File */
  #define _MOCK_CONSTANT(e)   e,

  #define MOCK_CONSTANTS(...)   enum{ EVAL256(MAP(_MOCK_CONSTANT, __VA_ARGS__)) };
  #define MOCK_CONSTANT(e)      enum{ _MOCK_CONSTANT(e) };
#else
  /* C File */
  #define MOCK_CONSTANT(...)      /* Nothing */
  #define MOCK_CONSTANTS(...)     /* Nothing */
#endif


#endif