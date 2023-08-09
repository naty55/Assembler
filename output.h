#ifndef __OUTPUT_H
#define __OUTPUT_H
#include "util.h"
#include "list.h"
#include "hashmap.h"
/**
 * Write externals file, return True if success
*/
Bool write_ext(plist externals, ptable symbols_table, char *filename);
/**
 * Write entries file, return True if success
*/
Bool write_ent(ptable entries, ptable symbols_table, char * filename);
/**
 * Write object file, return True if success
*/
Bool write_obj(plist inst_iamge, plist data_image, char *filename);
/**
 * Write all result file of assembly process
*/
void write_result_files(plist inst_image, plist data_image, ptable symbols_table, ptable missing_symbols, plist externals, ptable entries, char *filename, Bool *error);

#endif