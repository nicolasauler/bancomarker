#######################################################

CFLAGS=-Wall -Wextra -Wshadow -Wconversion -Wcast-align -Wunused -Wmissing-prototypes -Wno-missing-braces -std=c99 -pedantic -g -O2 -lsqlite3 -lmysqlclient #-D_POSIX_C_SOURCE=199309L
CC=gcc

SRC=src
SRCS=$(wildcard $(SRC)/*.c)

OBJ=obj
OBJS=$(patsubst $(SRC)/%.c, $(OBJ)/%.o, $(SRCS))

BIN=bin
BINS= $(BIN)/main

#######################################################

all: $(BINS)

run: $(BINS)
	./$(BINS)

$(BINS): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

$(OBJ)/%.o: $(SRC)/%.c $(SRC)/%.h
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ)/%.o: $(SRC)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(BIN):
	mkdir $@

$(OBJ):
	mkdir $@

clean:
	rm -r $(OBJ) $(BIN)
