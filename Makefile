# Quais objetos têm que ser compilados
OBJS = main.cpp trie.cpp outras.cpp

# Qual compilador usar
CC = g++

# Flags para o compilador
COMPILER_FLAGS = -Wall

# aqui eu recebo o uname para depois usar sabendo de é mac ou linux. Windows não trabalho no momento
# os = $(shell uname -s)

# Nome da saída
OUTPUT_NAME = a.out

FLAGS = -std=c++11

all : $(OBJS)
	$(CC) $(OBJS) $(INCLUDE_PATHS) $(LIBRARY_PATHS) $(COMPILER_FLAGS) $(FLAGS) -o $(OUTPUT_NAME)
