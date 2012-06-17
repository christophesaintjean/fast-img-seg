CC=clang
CFLAGS=-W -Wall -pedantic -g
LDFLAGS=-lm -lpng
EXEC=fast-seg
SRC= $(wildcard *.c)
OBJ= $(SRC:.c=.o)

all: $(EXEC)

$(EXEC): $(OBJ)
	@$(CC) -o $@ $^ $(LDFLAGS)
	
%.o: %.c
	@$(CC) -o $@ -c $< $(CFLAGS)
	
clean:
	rm *.o

mrproper: clean
	rm $(EXEC)
