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
QUEST1 = -DSTRLEN
QUEST2 = -DSTRCMP
QUEST3 = -DSTRCPY
QUEST4 = -DSTRCAT
QUEST5 = -DSTRCHR
QUEST6 = -DSTRSTR
QUEST7 = -DSTRTOK

s21_strlen_tests: 
	$(CC) $(FLAGS) $(QUEST1) $(FLAG_C) $(C) 
	$(CC) $(O) $(FLAG_O) $(DIR_END)/Quest_1 $(LM)

strcmp_tests: 
	$(CC) $(FLAGS) $(QUEST2) $(FLAG_C) $(C) 
	$(CC) $(O) $(FLAG_O) $(DIR_END)/Quest_2 $(LM)

strcpy_tests:
	$(CC) $(FLAGS) $(QUEST3) $(FLAG_C) $(C) 
	$(CC) $(O) $(FLAG_O) $(DIR_END)/Quest_3 $(LM)
	
strcat_tests:
	$(CC) $(FLAGS) $(QUEST4) $(FLAG_C) $(C) 
	$(CC) $(O) $(FLAG_O) $(DIR_END)/Quest_4 $(LM)

strchr_tests:
	$(CC) $(FLAGS) $(QUEST5) $(FLAG_C) $(C) 
	$(CC) $(O) $(FLAG_O) $(DIR_END)/Quest_5 $(LM)

strstr_tests:
	$(CC) $(FLAGS) $(QUEST6) $(FLAG_C) $(C) 
	$(CC) $(O) $(FLAG_O) $(DIR_END)/Quest_6 $(LM)

strtok_tests:
	$(CC) $(FLAGS) $(QUEST7) $(FLAG_C) $(C) 
	$(CC) $(O) $(FLAG_O) $(DIR_END)/Quest_7 $(LM)

clean:
	$(RM) $(O) $(DIR_END)/$(QUEST)
