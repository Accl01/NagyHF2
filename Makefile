CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++11 -g

TARGET = utvonaltervezo

SRCS = main.cpp graph.cpp planner.cpp file.cpp
OBJS = 	$(SRCS:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)
	@echo "Sikeres fordítás: $(TARGET)"

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@
main.o: main.cpp main.h graph.h node.h edge.h planner.cpp planner.h file.cpp file.h
graph.o: graph.cpp graph.h node.h edge.h


clean:
	rm -f $(OBJS) $(TARGET)
	@echo "Takarítás kész."

run: all
	./$(TARGET)

.PHONY: all clean run