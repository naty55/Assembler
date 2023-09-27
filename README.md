# Assembler
## Overview
Few words on implementation and code structure
### Data structures
We have 3 data structure, `plist` list of pointers, `clist` list of char data type, `ptable` which is hashmap of <string, pointer>.
- `plist` and `clist` are in file `list.c` and are locating memory dynamically as the list grows in size.
- `ptable` is in file `hashmap.c`, the keys are of type string and values can be pointer to any object. collision handling is done via chaining.

Those data structures are as generic as possible in the limit of the course requirements, so for example deletion is not supported as it's ont needed.
### Data types 
We have 2 main data types
- `instruction_line` which holds the binary line data and has interface to handle it.
- `symbol` which holds the data on labels in the assembling process.
### Implementation
We have couple of objects generated for every assembly file 
- instruction_image (plist<instruction_line): The instructions image, this includes the IC from course guide.
- data_image (plist<instruction_line>): The data image, this includes the DC image.
- symbols_table (ptable<string, symbol>): The symbols table
- missing_symbols (ptable <string, plist<instruction_line>): missing symbols keep track of the places where label was used, the `key` is the label, and the `value` is `plist` of all instruction lines that should be populated with the real address.
- entries (ptable<string, Bool>): Keep track of entries - with this we assure no entry is printed twice to the `.ent` file, the bool value of `value` does not matter, as long as it's not NULL we consider the entry to exist.
- externals (plist<string>): list of all externals, to print them later to the `.ext` file  
---
For every file
#### Preassemble
Remove macros and output `.am` file
#### First pass 
Read `.am` file and build the whole image except for the lines that should hold symbol address, keep track of those lines using `missing_symbols` object.
#### Second pass 
Fill the missing addresses in the lines, also validate all declared entries are declares
#### Output 
Output binary file, and `.ext`, `.ent` files

### Debugging logs and errors
Through the assembling process the assembler prints logs, for debugging we have `DEBUG_FLAG` in `error.h`, logs usually contain code line index, which refer to the `.am` file.

## Build and run
### Build
run `make`
### Run 
run `./assembler filename1 filename2 ...` without the file extension (extension should be `.as`)
### Run tests
after build run `make test` to run the assembler against all files in `./test` directory (including missing file to test against such errors)  
It's also possible to run specific type of test, 
- `make test-ok` will run only tests without errors or warnings
- `make test-warn` will run tests with warnings and without errors
- `make test-ok` will run only tests with errors

## Decisions and behaviors that were not specified in the course guide
1. Declaring twice or more label as external or entry will result warning only
2. Instruction of `.string` or `.data` without label will result warning as the data is not accessible
3. We check 2 types of errors in macros, (a) macro name is not saved keyword (b) line length is no longer than 80 chars. when we have such an error we don't generate the `.am` file and skipping to the next file (if any), other than that pre-assembler will not handle errors and we assume the macros are defined correctly (page 35 in course guide)
4. When we have data overflow the assembler will output a warning and set the value to 0
5. Char `;` after spaces is not considered as comment for example `    ;comment` will not be treated as comment line (The more intuitive approach is to treat it as comment - but I'm not sure it's according to the course guide)
