CC = gcc
CFLAGS = -Wall -Wextra -std=c99
TARGET = string_demo
SOURCES = main.c func.c

$(TARGET): $(SOURCES)
	$(CC) $(CFLAGS) -o $(TARGET) $(SOURCES)

string_demo: main.c func.c f2unc.c
	gcc -Wall -Wextra -std=c99 -o string_demo main.c func.c f2unc.c

clean:
	rm -f $(TARGET)

run: $(TARGET)
	./$(TARGET)

.PHONY: clean run