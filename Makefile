MAIN_FLAG = gcc -g -Wall -ansi -pedantic

OBJ_FLAG = gcc -c -Wall -ansi -pedantic

OBJECTS = assembler.o pre_assembler.o util.o constants.o list.o hashmap.o instruction_line.o #data_structure.o first_pass.o second_pass.o parse.o errors.o output.o

HEADERS = assembler.h pre_assembler.h util.h constants.h list.h hashmap.h instruction_line.h #data_structure.h first_pass.h second_pass.h parse.h errors.h output.h

assembler: $(OBJECTS)
	$(MAIN_FLAG) $(OBJECTS) -o assembler

assembler.o: assembler.c $(HEADERS)
	$(OBJ_FLAG) assembler.c -o assembler.o

constants.o: constants.c $(HEADERS)
	$(OBJ_FLAG) constants.c -o constants.o


list.o: list.c $(HEADERS)
	$(OBJ_FLAG) list.c -o list.o

hashmap.o: hashmap.c $(HEADERS)
	$(OBJ_FLAG) hashmap.c -o hashmap.o

pre_assembler.o: pre_assembler.c $(HEADERS)
	$(OBJ_FLAG) pre_assembler.c -o pre_assembler.o

instruction_line.o: instruction_line.c $(HEADERS)
	$(OBJ_FLAG) instruction_line.c -o instruction_line.o

#first_pass.o: first_pass.c $(HEADERS)
#	$(OBJ_FLAG) first_pass.c -o first_pass.o

#second_pass.o: second_pass.c $(HEADERS)
#	$(OBJ_FLAG) second_pass.c -o second_pass.o

#parse.o: parse.c $(HEADERS)
#	$(OBJ_FLAG) parse.c -o parse.o

#errors.o: errors.c $(HEADERS)
#	$(OBJ_FLAG) errors.c -o errors.o

util.o: util.c $(HEADERS)
	$(OBJ_FLAG) util.c -o util.o

#output.o: output.c $(HEADERS)
#	$(OBJ_FLAG) output.c -o output.o

#debug: $(OBJECTS)
#	$(MAIN_FLAG) $(OBJECTS) -o assembler-debug

clean:
	rm -f *.o