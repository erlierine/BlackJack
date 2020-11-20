TARGET = blackjack
C = gcc
CFLAGS = -Wall -Wextra -std=c99

$(TARGET): main.c
	$(C) $(CFLAGS) -o $@ $<

.PHONY: clean

clean:
	rm $(TARGET) cards/*.txt
