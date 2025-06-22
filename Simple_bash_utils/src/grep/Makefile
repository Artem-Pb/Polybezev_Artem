CC=gcc 
FLAGS=-std=c11 -Wall -Wextra -Werror

SRC=s21_grep.c
EXE=s21_grep
LOG=*.log
TXT=*.txt

OBJDIR=../obj
OBJECT=$(addprefix $(OBJDIR)/,$(SRC:.c=.o))

all: $(EXE)

$(EXE): $(OBJECT)
	$(CC) $(OBJECT) -o $(EXE)

$(OBJDIR)/%.o: %.c 
	mkdir -p $(OBJDIR)
	$(CC) $(FLAGS) -c $< -o $@

clean:
	rm -rf $(OBJDIR) $(EXE) $(LOG) $(TXT)

.PHONY: clean 