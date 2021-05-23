CC=gcc
CFLAGS=-I.
DEPS = lin.h
OBJ = lin.o main.o


.PHONY: all #.PHONY говорит что all это только команда
all: lin

# $@ - это %.o
%.o: %.c $(DEPS)  # вместо * - %
		$(CC) -c -o $@ $< $(CFLAGS) # $< берет только %.c

# $@ - это lin
lin: $(OBJ)
		$(CC) -o $@ $^ $(CFLAGS) # $^ берет все $(OBJ)

.PHONY: run
run: all
		./lin

.PHONY: clean
clean:
	rm -f $(OBJ) lin