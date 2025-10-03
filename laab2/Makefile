CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -O2 -lm
TARGET = prime
SOURCES = main.c prime.c
OBJECTS = $(SOURCES:.c=.o)

$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^ -lm

%.o: %.c prime.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(TARGET) $(OBJECTS)

.PHONY: clean