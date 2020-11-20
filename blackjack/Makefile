TARGET = blackjack
C = gcc
CFLAGS = -Wall -Wextra -std=c99

$(TARGET): main.o functions.o
	$(C) $(CFLAGS) -o $@ $^
functions.o: blackjack.c blackjack.h
	$(C) $(CFLAGS) -c -o $@ $<

.PHONY: clean

clean:
	rm $(TARGET) cards/*.txt
