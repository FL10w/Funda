CC=gcc
CFLAGS=-Wall -Wextra -std=c99 -lm
TARGET=uwu
SOURCES=main.c operations.c
OBJECTS=$(SOURCES:.c=.o)

$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) -o $(TARGET) $(CFLAGS)

%.o: %.c
	$(CC) -c $< -o $@

clean:
	rm -f $(OBJECTS) $(TARGET)

.PHONY: clean