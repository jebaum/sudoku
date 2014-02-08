CC=g++
CPPFLAGS=-Wall -Wextra -g
DEPS = $(wildcard *.h)
SRCS = $(wildcard *.cpp)
OBJS = $(patsubst %.cpp,%.o,$(SRCS))
BINS = sudoku

all: $(BINS)

%.o: %.cpp
	$(CC) $(CPPFLAGS) -c $<

sudoku: $(OBJS)
	$(CC) $(CPPFLAGS) -o sudoku $(OBJS)

clean:
	-@rm $(OBJS) $(BINS) recv_* 2>/dev/null || true
	@echo "Removed object files, binaries, and recv_* files"
