MAIN_FLAG = gcc -g -Wall -ansi -pedantic

OBJ_FLAG = gcc -c -Wall -ansi -pedantic

OBJECTS = main.o assembler.o pre_assembler.o util.o constants.o list.o hashmap.o instruction_line.o parse.o symbol.o output.o

HEADERS = assembler.h pre_assembler.h util.h constants.h list.h hashmap.h instruction_line.h error.h parse.h symbol.h output.h

assembler: $(OBJECTS)
	$(MAIN_FLAG) $(OBJECTS) -o assembler

main.o: main.c $(HEADERS)
	$(OBJ_FLAG) main.c -o main.o

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

parse.o: parse.c $(HEADERS)
	$(OBJ_FLAG) parse.c -o parse.o

symbol.o: symbol.c $(HEADERS)
	$(OBJ_FLAG) symbol.c -o symbol.o

util.o: util.c $(HEADERS)
	$(OBJ_FLAG) util.c -o util.o

output.o: output.c $(HEADERS)
	$(OBJ_FLAG) output.c -o output.o

clean:
	rm -f *.o

clean-test:
	rm -f ./tests/**/*.am ./tests/**/*.ent ./tests/**/*.ob ./tests/**/*.ext

test-ok:
	./assembler tests/ok/test1 tests/ok/test2 tests/ok/test3 tests/ok/test4 tests/ok/test5 tests/ok/test6 tests/ok/test7 tests/ok/test8 tests/ok/test9 tests/ok/test10 tests/ok/test11 tests/ok/test12 tests/ok/test13 
test-warn:
	./assembler tests/warn/test1 tests/warn/test2 tests/warn/test3 tests/warn/test4 
test-error:
	./assembler tests/error/test1 tests/error/test2 tests/error/pre_assembler_error1 tests/error/pre_assembler_error2 tests/error/not_exist_file
test: clean-test assembler
	make test-ok test-warn test-error

lines-count:
	git ls-files | xargs wc -l
