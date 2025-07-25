# tictactoe.cpp icin

CXX = g++

CXXFLAGS = -Wall -Wextra -std=c++17

TARGET = tictactoe

SRCS = tictactoe.cpp

OBJS = $(SRCS:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: all clean
