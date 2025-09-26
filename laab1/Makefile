CC = gcc
CFLAGS = -Wall -Wextra -std=c99
LDFLAGS = -lm
TARGET = uwu
OBJS = main.o operations.o

$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $(TARGET) $(LDFLAGS)

clean:
	rm -f $(OBJS) $(TARGET)