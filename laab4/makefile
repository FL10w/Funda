CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -pedantic
LIBS = -lm

TARGET = constants
SOURCES = main.c constants.c
HEADERS = constants.h

$(TARGET): $(SOURCES) $(HEADERS)
	$(CC) $(CFLAGS) -o $(TARGET) $(SOURCES) $(LIBS)

clean:
	rm -f $(TARGET)

.PHONY: clean