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
- instruction_image (plist<instruction_line): The instructions image, this includes the IC from course guide.
- data_image (plist<instruction_line>): The data image, this includes the DC image.
- symbols_table (ptable<string, symbol>): The symbols table
- missing_symbols (ptable <string, plist<instruction_line>): missing symbols keep track of the places where label was used, the `key` is the label, and the `value` is `plist` of all instruction lines that should be populated with the real address.
- entries (ptable<string, Bool>): Keep track of entries - with this we assure no entry is printed twice to the `.ent` file, the bool value of `value` does not matter, as long as it's not NULL we consider the entry to exist.
- externals (plist<string>): list of all externals, to print them later to the `.ext` file

### Debugging logs and errors
Thorugh the assemling process the assembler prints logs, for debugging we have `DEBUG_FLAG` in `error.h` 

## Build and run
### Build
run `make`
### Run 
run `./assembler filename1 filename2 ...` without the filen extension (extension should be `.as`)
### Run tests
after build run `make test` to run the assembler against all files in `./test` directory (including missing file to test against such errors)

## Decisions and behaviors that were not specified in the course guide
1. Declaring twice or more label as external or entry will result warning only
2. Instruction of `.string` or `.data` without label will result warning as the data is not accessbiale
3. We check 2 types of errors in macros, (a) macroname is not save (b) line length is no longer than 80 chars. when we have such error we don't generate the `.am` file and skipping to the next file (if any), other than that pre-assembler will not handle errors and we assume the nacros are defined correctly (page 35 in course guide)
