CC=gcc
CFLAGS=-Wall -Wextra -std=c11 -g
SRC=src/main.c src/territorio.c src/attack.c src/mission.c
OBJ=$(SRC:.c=.o)
OUT=war

all: $(OUT)

$(OUT): $(SRC)
	$(CC) $(CFLAGS) -o $(OUT) $(SRC)

clean:
	rm -f $(OUT) *.o
