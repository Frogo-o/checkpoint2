CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -pedantic
TARGET = task_manager.exe
SOURCES = $(wildcard src/*.cpp)

.PHONY: all run clean

all: $(TARGET)

$(TARGET): $(SOURCES)
	$(CXX) $(CXXFLAGS) $(SOURCES) -o $(TARGET)

run: $(TARGET)
	./$(TARGET)

clean:
	del /Q $(TARGET) 2>NUL || exit 0
