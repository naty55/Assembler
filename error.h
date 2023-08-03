#ifndef __ERROR_H
#define __ERROR_H
#include <stdio.h>
#include <stdlib.h>

#define INFO(message) printf("[INFO] %s\n", message);
#define INFO_WORKING_ON_FILE(filename) printf("[INFO] Working on file %s.as\n", filename);
#define INFO_1PARAM_INT(message, param) printf("[INFO] %s %d\n", message, param);
#define WARN(message, index) printf("[WARN] warning at line %d %s \n", index, message);
#define FILE_ERROR(filename) printf("Error: can't open file %s\n", filename);
#define HANDLE_ERROR(message, index, error) \
        printf("Error: error at line %d %s\n", index, message); \
        *error = True;
#define HANDLE_ERROR_ONE_PARAM(message, param1, index, error) \
        printf("Error: error at line %d %s %s\n", index, message, param1); \
        *error = True;
#define IF_ERROR_RETURN(error) if(*error) return
#define FATAL_ERROR(message)\
        printf("Fatal error: %s", message);\
        exit(EXIT_FAILURE);


/*#define DEBUG_FLAG*/
#ifdef DEBUG_FLAG 
#define DEBUG_LINE(line, line_index) printf("[DEBUG] %d\t: %s\n", line_index, line);
#define DEBUG(message) printf("[DEBUG] %s \n", message); 
#define DEBUG_1PARAM_INT(message, param1) printf("[DEBUG] %s '%d'\n", message, param1); 
#define DEBUG_1PARAM_STR(message, param1) printf("[DEBUG] %s '%s'\n", message, param1); 
#define DEBUG_2PARAM(message, param1, param2) printf("[DEBUG] %s %s '%d'\n", message, param1, param2); 
#else
#define DEBUG_LINE(line, line_index)
#define DEBUG(message)
#define DEBUG_1PARAM_INT(message, param1)
#define DEBUG_1PARAM_STR(message, param1) 
#define DEBUG_2PARAM(message, param1, param2) 
#endif
#endif
