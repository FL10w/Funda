CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -O2
LIBS = -lm

SRCS = main.c operations.c
OBJS = $(SRCS:.c=.o)
TARGET = program

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS) $(LIBS)

main.o: main.c operations.h
	$(CC) $(CFLAGS) -c main.c -o main.o

operations.o: operations.c operations.h
	$(CC) $(CFLAGS) -c operations.c -o operations.o

test: $(TARGET)
	chmod +x test.sh
	./test.sh

clean:
	rm -f $(OBJS) $(TARGET)