# Makefile for Unit Tests
CC=gcc
CFLAGS=-g -Wall
LANGUAGE_FLAGS=-x c
DIRECTIVES=-D UNIT_TEST -D __$(shell echo $@ | tr a-z A-Z)__
OUT=$@.tests

# Files to compile (for all targets)
SOURCES=./can/can.c ./can_controllers/can_controller.c.mock ./microcontrollers/microcontroller.c ./spi/spi.c ./tests/tests.c.test ./tests/unity/unity.c.test

# Files to compile for the target
TARGET_SOURCES=$(shell find './microcontrollers/$@' -name '*.c.mock')




# Make unit tests for a target
%:
	$(CC) $(LANGUAGE_FLAGS) $(SOURCES) $(TARGET_SOURCES) -o $(OUT) $(DIRECTIVES)