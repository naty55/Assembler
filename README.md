# assembler
## Overview
Few words on implemntation and code structure
### Data structures
We have 3 data structure, `plist` list of pointers, `clist` list of char data type, `ptable` which is hasmap of <string, pointer>.
- `plist` and `clist` are in file `list.c` and are locating memory dynamically as the list grows in size.
- `ptable` is in file `hashmap.c`, the keys are of type string and values can be pointer to any object. collision handling is done via chaining.

Those data structures are as generic as possible in the limit of the course requirements, so for example deletion is not supported as it's ont needed.
### Data types 
We have 2 main data types
- `instruction_line` which holds the binary line data and has interface to handle it.
- `symbol` which holds the data on labels in the assembling process.
### Implemtation
We have couple of objects generated for every assembly file 
- instruction_image (plist<instruction_line)
- data_image (plist<instruction_line>)
- symbols_table (ptable<string, symbol>)
- missing_symbols (ptable <string, plist<instruction_line>)
- entries (ptable<string, Bool>);
- externals (plist<string>)
## Decisions and behaviors that were not specified in the course guide
