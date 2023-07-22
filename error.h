#ifndef __ERROR_H
#define __ERROR_H
#include <stdio.h>
#define PRINT_ERROR_WITH_INDEX(message, index) printf("Error: error at line %d %s\n", index, message)
#define LOG_INFO(message) printf("[INFO] %s\n", message);
#endif
