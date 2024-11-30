CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -g

TARGET = test_tree

SRCS = tree.cc

$(TARGET): $(SRCS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRCS)

test: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET)

.PHONY: clean test