# Allow CC, CFLAGS, and LDFLAGS to be overridden by environment or default to sensible values
CC ?= gcc
CFLAGS ?= -I ./ -Wall -Werror
LDFLAGS ?= -static

# Object files and binary output
OBJS = main.o ssd1306.o linux_i2c.o
BIN = ssd1306_bin

# Default target
default: $(BIN)

# Rule to link the object files into the binary
$(BIN): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS) $(LDFLAGS)

# Rule to compile individual .c files into .o files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean rule to remove binaries and object files
clean:
	rm -f $(BIN) $(OBJS)

.PHONY: default clean
