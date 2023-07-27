#ifndef __ERROR_H
#define __ERROR_H
#include <stdio.h>
#include <stdlib.h>

#define INFO(message) printf("[INFO] %s\n", message);
#define WARN(message, index) printf("[WARN] warning at line %d %s \n", index, message);
#define HANDLE_ERROR(message, index) \
        printf("Error: error at line %d %s\n", index, message); \
        *error = True;
#define HANDLE_ERROR_ONE_PARAM(message, param1, index) \
        printf("Error: error at line %d %s %s\n", index, message, param1); \
        *error = True;
#define IF_ERROR_RETURN() if(*error == True) return
#define FATAL_ERROR(message)\
        printf("Fatal error: %s", message);\
        exit(EXIT_FAILURE);
#endif
