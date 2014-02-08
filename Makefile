CC=g++
CPPFLAGS=-Wall -Wextra -g
SRCS = $(wildcard *.cpp)
OBJS = $(patsubst %.cpp,%.o,$(SRCS))
BINS = sudoku

all: $(BINS)

%.o: %.cpp
	$(CC) $(CPPFLAGS) -c $<

sudoku: $(OBJS)
	$(CC) $(CPPFLAGS) -o sudoku $(OBJS)

clean:
	-@rm $(OBJS) $(BINS) 2>/dev/null || true
	@echo "Removed object files and binaries"
