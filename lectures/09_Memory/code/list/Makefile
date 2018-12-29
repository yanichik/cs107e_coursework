CFLAGS = --std=c99 -g

all: test
	./test | cmp - tests.gold

test: test.o list.o block.o
	$(CC) $(CFLAGS) $^ -o $@

gold:
	./test > tests.gold

clean:
	rm -fr test *.o

list.o:	list.c list.h block.h
test.o: list.h
