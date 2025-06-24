CC = gcc
FLAGS = -Wall -Werror -Wextra
LM = -lm
RM = -rm -f
O = *.o
FLAG_O = -o
C = *.c
FLAG_C = -c
DIR_END = ../build
QUEST = Quest*

door_struct:
	$(CC) $(FLAGS) $(FLAG_C) dmanager_module.c
	$(CC) $(O) $(FLAG_O) $(DIR_END)/Quest_1 $(LM)
	$(RM) *.o

list_test:
	$(CC) $(FLAGS) $(FLAG_C) list_test.c list.c
	$(CC) $(O) $(FLAG_O) $(DIR_END)/Quest_2 $(LM)
	$(RM) *.o

clean: 
	$(RM) $(O) $(DIR_END)/$(QUEST)