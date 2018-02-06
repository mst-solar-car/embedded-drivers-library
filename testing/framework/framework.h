/**
 * Unit Testing Framework
 *
 * You can include this file in your unit tests file.
 *
 * This is a fixture around the Unity Framework, a fixture allows for easier interaction
 * with a library/driver
 *
 * Authors: Michael Rouse
 */
#ifndef __UNIT_TEST_FRAMEWORK__
#define __UNIT_TEST_FRAMEWORK__
#ifdef UNIT_TEST

#include "unity.h"
#include <stdio.h>
#include <stdlib.h>


// Used to make a string from the group name
#define TOSTR(x)          STRINGIFY(x)
#define STRINGIFY(x)      #x

// Concatination
#define CAT(a, ...)       _CAT(a, __VA_ARGS__)
#define _CAT(a, ...)      a ## __VA_ARGS__

// Used to make the group setup function
#define GROUP_SETUP()     void CAT(GROUP, _setup)(void)
#define PERFORM_SETUP()   CAT(GROUP, _setup)()

// Used to make unit test functions
#define TEST(name)        void CAT(CAT(CAT(test_, GROUP), _), name)(void)

// Used to run a group unit test
#define RUN(name)         PERFORM_SETUP(); RUN_TEST(CAT(CAT(CAT(test_, GROUP), _), name))

// Used to create function to run group unit tests
#define GROUP_RUNNER()    void CAN(GROUP, _setup)(); \
                          void CAT(run_, GROUP)(void); \
                          void CAT(GROUP, _start)(void) { printf("\n====== %s ======\n", TOSTR(GROUP)); CAT(run_, GROUP)(); } \
                          void CAT(run_, GROUP)(void)

// Used to run a group runner
#define RUN_GROUP(group)  CAT(group, _start)()

#endif
#endif