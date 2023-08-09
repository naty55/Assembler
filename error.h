#ifndef __ERROR_H
#define __ERROR_H
#include <stdio.h>
#include <stdlib.h>


#define INFO(message) printf("\033[0;34m[INFO]\033[0;37m %s\n", message);
#define INFO_WORKING_ON_FILE(filename) printf("\033[0;34m[INFO]\033[0;37m Working on file %s.as\n", filename);
#define INFO_1PARAM_INT(message, param) printf("\033[0;34m[INFO]\033[0;37m %s %d\n", message, param);
#define INFO_1PARAM_STR(message, param) printf("\033[0;34m[INFO]\033[0;37m %s %s\n", message, param);
#define WARN(message, index) printf("\033[0;33m[WARN]\033[0;37m warning at line %d %s \n", index, message);
#define WARN_1PARAM(message, index, param) printf("\033[0;33m[WARN]\033[0;37m warning at line %d %s %s\n", index, message, param);
#define FILE_ERROR(filename) printf("\033[0;31mError\033[0;37m: can't open file %s\n", filename);
#define ERROR(message, index) printf("\033[0;31mError\033[0;37m: error at line %d %s\n", index, message);
#define HANDLE_ERROR(message, index, error) \
        ERROR(message, index)\
        *error = True;
#define HANDLE_ERROR_ONE_PARAM(message, param1, index, error) \
        printf("\033[0;31mError\033[0;37m: error at line %d %s '%s'\n", index, message, param1); \
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
#define DEBUG_2PARAM(message, param1, param2) printf("[DEBUG] %s '%s' %d\n", message, param1, param2); 
#else
#define DEBUG_LINE(line, line_index)
#define DEBUG(message)
#define DEBUG_1PARAM_INT(message, param1)
#define DEBUG_1PARAM_STR(message, param1) 
#define DEBUG_2PARAM(message, param1, param2) 
#endif
#endif
