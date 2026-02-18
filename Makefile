CC = g++
CFLAGS = -std=c++17 -O2 -Wall -Wextra
TARGET = columnsolver

all: build

build:
	$(CC) $(CFLAGS) columnsolver.cpp -o $(TARGET)

run: build
	./$(TARGET)

clean:
	rm -f $(TARGET)

test:
	@echo "No unit tests yet — add tests/ and `make test` will run them"
