#ifndef __LIST_H
#define __LIST_H
typedef struct CharList *char_list;

char_list create_char_list();
char append_char(char_list l, char item);
char append_all_chars(char_list l, char *items, int size);
char get_char(char_list l, int i);

#endif
