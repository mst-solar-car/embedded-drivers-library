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


/* Use this directive before writing any tests */
#define CREATE_GROUP(group)   void test_##group##_group_setup__(void); \
                              void test_##group##_group_teardown__(void); \
                              void test_##group##_group_runner__(void); \
                              void test_##group##_group_begin__(void); \
                              void test_##group##_group_begin__(void) { \
                                Unity.TestFile = __FILE__; \
                                printf("\n====== %s ======\n", #group);  \
                                test_##group##_group_runner__(); \
                              }

/* Directive that creates a test for a group */
#define TEST(group, name) void test_##group##_##name(void); \
                          void test_##group##_test_##name##_runner__(const int line); \
                          void test_##group##_test_##name##_runner__(const int line) { \
                            if (TEST_PROTECT()) { \
                              test_##group##_group_setup__(); \
                              UnityDefaultTestRun(test_##group##_##name, #name, line); \
                            } \
                            if (TEST_PROTECT()) { \
                              test_##group##_group_teardown__(); \
                            } \
                          } \
                          void test_##group##_##name(void)

/* Test Setups are performed before every test */
#define GROUP_TEST_SETUP(group) void test_##group##_group_setup__(void)

/* Test Teardowns are peformed after every test */
#define GROUP_TEST_TEARDOWN(group)  void test_##group##_group_teardown__(void)

/* Used to create function to run group unit tests */
#define GROUP_RUNNER(group)  void test_##group##_group_runner__(void)

/* Used to run a test */
#define PERFORM_TEST(group, name)   test_##group##_test_##name##_runner__(__LINE__);
#define IGNORE_TEST(group, name)    printf("%s:%i:%s:IGNORE\n", __FILE__, __LINE__, #name); \
                                    Unity.NumberOfTests++; \
                                    Unity.TestIgnores++;

/* Used to run a group runner */
#define RUN_GROUP(group)  { \
                            void test_##group##_group_begin__(void); \
                            test_##group##_group_begin__(); \
                          }

/* Create this function if you are using this test framework and you want to add */
/* tests to drivers that are not in this library */
#define CUSTOM_TESTS() void UserCustomTests(void)


#include "mock.h"
#endif
#endif