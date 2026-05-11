CC=gcc
CFLAGS=-Wall -Wextra -std=c11
TARGET=assn2
SRC=assn2.c

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm -f $(TARGET) *.o
