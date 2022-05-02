CFLAGS = -std=c99 -lm -g -Wall -Wshadow --pedantic -Wvla -Werror
GCC = gcc $(CFLAGS)
EXEC1 = generate
EXEC2 = note
EXEC3 = note1
VALGRIND = valgrind --tool=memcheck --leak-check=yes --verbose

gen: generatingMusic.c
	$(GCC) $(CFLAGS) -o $(EXEC1) generatingMusic.c generatingMusic.h

note: findNote.c
	$(GCC) $(CFLAGS) -o $(EXEC2) findNote.c

note1: findNote1.c
	$(GCC) $(CFLAGS) -o $(EXEC3) findNote1.c findNote1.h

test1: gen
	./$(EXEC1) output.txt out1

test2: note
	./$(EXEC2) E Gb G A B C D 1

test3: note1
	./$(EXEC3) out1 freqs

	
memory: $(EXEC1)
	$(VALGRIND) --log-file=log1 ./$(EXEC1) output.txt out1

