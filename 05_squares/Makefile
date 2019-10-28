MAKEFLAGS += --no-builtin-rules

.SUFFIXES:

default: clean build

clean:
	test -f squares && rm squares

build:
	gcc -o squares -Wall -Werror -std=gnu99 --pedantic squares.c squares_test.o
#	gcc -o squares -Wall -Werror -std=gnu99 --pedantic squares_test2.c
