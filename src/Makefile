CXX := g++
CXXFLAGS := -O2 -std=c++17 -Wall -Wextra

SRCS := benchmark.cpp insertion_sort.cpp merge_sort.cpp hybrid_sort.cpp
OBJS := $(SRCS:.cpp=.o)
TARGET := benchmark

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

clean:
	rm -f $(OBJS) $(TARGET)
