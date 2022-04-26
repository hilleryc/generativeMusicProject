CFLAGS = -std=c99 -g -Wall -Wshadow --pedantic -Wvla -Werror
GCC = gcc $(CFLAGS)
EXEC = notes
VALGRIND = valgrind --tool=memcheck --leak-check=yes --verbose

all: generatingMusic.c
	$(GCC) $(CFLAGS) -o $(EXEC) generatingMusic.c generatingMusic.h


test: all
	./$(EXEC) 75 117 158
	
memory: $(EXEC)
	$(VALGRIND) --log-file=log1 ./$(EXEC) 75 117 158
