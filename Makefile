CFLAGS = -std=c99 -lm -g -Wall -Wshadow --pedantic -Wvla -Werror
GCC = gcc $(CFLAGS)
EXEC1 = generate
EXEC2 = note
VALGRIND = valgrind --tool=memcheck --leak-check=yes --verbose

gen: generatingMusic.c
	$(GCC) $(CFLAGS) -o $(EXEC1) generatingMusic.c generatingMusic.h

note: findNote.c
	$(GCC) $(CFLAGS) -o $(EXEC2) findNote.c

test1: gen
	./$(EXEC1) test1 out1

test2: note
	./$(EXEC2) E Gb G A B C D 1

	
memory: $(EXEC1)
	$(VALGRIND) --log-file=log1 ./$(EXEC1) 75 117 158

