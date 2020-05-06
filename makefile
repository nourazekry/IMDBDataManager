CC = gcc
CFLAGS = -Wall -ansi -pedantic
OBJ = binary.o name.o title.o principals.o a3.o common.o
COM = ${CC} ${CFLAGS} -c $<

all: ${OBJ}
	${CC} ${CFLAGS} -o a3 ${OBJ}

a3.o: a3.c binary.h name.h title.h principals.h common.h
	${COM}

title.o: title.c binary.h common.h
	${COM}

common.o: common.c common.h
	${COM}

name.o: name.c binary.h common.h
	${COM}

principals.o: principals.c binary.h common.h
	${COM}

clean:
	rm *.o *.exe
