CC=g++
CFLAGS=-Wall -g
LDFLAGS=-lm
EXEC=projet
SRC=$(wildcard *.cpp)
OBJ=$(SRC:.c=.o)

all: $(EXEC)

$(EXEC): $(OBJ)
	@$(CC) -o $@ $^ $(LDFLAGS)

%.o: %.cpp
	@$(CC) -o $@ -c $< $(CFLAGS)

clean:
	@rm -rf *.o

cleanall: clean
	@rm -rf $(EXEC)