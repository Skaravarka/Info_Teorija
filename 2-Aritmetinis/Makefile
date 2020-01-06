CC = g++
TARGET = main
CFLAGS = -Wall -Werror -Wextra
SRC = main compress encode decode functions

$(TARGET): $(addsuffix .cpp, $(SRC))
	$(CC) $(CFLAGS) -o $@ $^

clean:
	/bin/rm -f $(addsuffix .o, $(SRC))
