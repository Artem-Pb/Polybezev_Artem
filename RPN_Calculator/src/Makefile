CC = gcc
FLAGS = -Wall -Werror -Wextra
LM = -lm
RM = -rm -f
O = *.o
FLAG_O = -o
C = *.c
FLAG_C = -c
DIR_END = ../build

all:
	$(CC) $(FLAGS) $(C) $(FLAG_C) 
	$(CC) $(O) $(FLAG_O) $(DIR_END)/graph $(LM)
	$(RM) *.o

clean: 
	$(RM) $(O) $(DIR_END)/graph
