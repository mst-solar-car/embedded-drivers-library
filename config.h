/**
 * This file is used to retrieve the user configuration file.
 *
 * If you are looking to see how you can configure your driver library,
 * look at user_config.example
 *
 * If unit testing, it will not do so
 */
#ifndef CONFIG_IMPORTER
#define CONFIG_IMPORTER
#include "library.details.h"

// Default location for the user config file is immediately one directory up
#ifndef USER_CONFIG_FILE
#define USER_CONFIG_FILE "../user_config.h"
#endif


// Include the user config file if not compiling for unit tests
#ifndef UNIT_TEST
  #include USER_CONFIG_FILE
#else
  // No clue yet
#endif


#endif