CC = gcc
CFLAGS = -Wall -Wextra -pedantic -std=c99
INCLUDES = -I..

SRC = test_vecodin_1.c test_vecodin_2.c
OBJS = $(SRC:.c=.o)
BINARIES = $(SRC:.c=)

all: $(BINARIES)

%: %.o
	$(CC) $(CFLAGS) -o $@ $^ $(INCLUDES)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@ $(INCLUDES)

run: all
	@echo "Running tests..."
	@for test in $(BINARIES); do \
		echo "==> $$test"; \
		./$$test || echo "[FAIL] $$test exited with non-zero status"; \
		echo ""; \
	done

clean:
	rm -f $(BINARIES) $(OBJS)
