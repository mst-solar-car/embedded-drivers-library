# Makefile for Unit Tests
CC=gcc
CFLAGS=-g -Wall
LANGUAGE_FLAGS=-x c
DIRECTIVES=-D UNIT_TEST -D __$(shell echo $@ | tr a-z A-Z)__
OUT=$@.test.out

# Files to compile (for all targets)
SOURCES=./library.c ./testing/unity.driver

# Find all the unit tests
UNIT_TEST_FILES=$(shell find '.' -name '*.tests')



# Make unit tests for a target
%:
	$(CC) $(CFLAGS) $(LANGUAGE_FLAGS) $(SOURCES) $(UNIT_TEST_FILES) -o $(OUT) $(DIRECTIVES)