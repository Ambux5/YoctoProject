# Definice proměnných
CC ?= gcc
CFLAGS ?= -I${STAGING_INCDIR} -I/path/to/ssd1306/includes -I/path/to/ina219/includes -Wall -Werror
LDFLAGS ?= -L${STAGING_LIBDIR} -lssd1306 -lina219
LDFLAGS += -L/path/to/ssd1306/libs -L/path/to/ina219/libs
LDFLAGS += -Wl,--trace

# Object files and binary output
OBJS = helloworld.o ina219_interface.o ina219_basic.o
BIN = helloworld

# Default target
default: check_libs $(BIN)

# Check if libraries are found
check_libs:
	@if ! $(CC) -lssd1306 -lina219 --print-file-name=libssd1306.so; then \
		echo "makefile!!: Error: ssd1306 library not found"; \
		exit 1; \
	else \
		echo "makefile!!: ssd1306 library found"; \
	fi
	@if ! $(CC) -lina219 --print-file-name=libina219.so; then \
		echo "makefile!!: Error: ina219 library not found"; \
		exit 1; \
	else \
		echo "makefile!!: ina219 library found"; \
	fi

$(BIN): $(OBJS)
	$(CC) -o $@ $(OBJS) $(LDFLAGS)

%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(BIN) $(OBJS)

.PHONY: default clean check_libs