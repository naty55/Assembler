#ifndef __OUTPUT_H
#define __OUTPUT_H
#include "util.h"
#include "list.h"
#include "hashmap.h"

Bool write_ext(plist externals, ptable symbols_table, char *filename);
Bool write_ent(plist entries, ptable symbols_table, char * filename);
Bool write_obj(plist inst_iamge, plist data_image, char *filename);
void write_result_files(plist inst_image, plist data_image, ptable symbols_table, ptable missing_symbols, plist externals, plist entries, char *filename, Bool *error);

#endif