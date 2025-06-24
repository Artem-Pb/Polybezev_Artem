CC = gcc
CFLAGS = -Wall -Werror -Wextra
LIBS = -lm
BUILD_DIR = ../../build

DIR_DATA_LIB = ../data_libs
DIR_DATA_MODULE = ../data_module
DIR_MAIN_EXE = .
DIR_YET = ../yet_another_decision_module

PROGRAM = $(BUILD_DIR)/Quest*

.PHONY: all clear rebuild

all : $(PROGRAM)

$(PROGRAM): 
	$(CC) $(CFLAGS) -c *.c $(DIR_DATA_MODULE)/data_process.c $(DIR_DATA_LIB)/*.c $(DIR_YET)/decision.c
	$(CC) *.o -o ../../build/Quest_3 -lm

data_stat.a:
	$(CC) $(CFLAGS) -c $(DIR_DATA_LIB)/data_stat.c 
	ar r data_stat.a *.o

build_with_static: data_stat.a
	$(CC) $(CFLAGS) -c *.c $(DIR_DATA_MODULE)/data_process.c $(DIR_DATA_LIB)/data_io.c $(DIR_YET)/decision.c
	$(CC) *.o -L. -l:data_stat.a -o $(BUILD_DIR)/Quest_5 $(LIBS)

data_process.so:
	$(CC) $(CFLAGS) -c -fPIC $(DIR_DATA_MODULE)/data_process.c
	$(CC) -shared -o data_process.so *.o

build_with_dynamic: data_process.so
	$(CC) $(CFLAGS) -c *.c $(DIR_DATA_MODULE)/data_process.c $(DIR_DATA_LIB)/*.c $(DIR_YET)/decision.c
	$(CC) *.o -L. -l:data_process.so -Wl,-rpath,. -o $(BUILD_DIR)/Quest_6 $(LIBS)

clean:
	rm -f *.o $(PROGRAM)

rebuild: clean all