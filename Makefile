CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++11 -g -DTEST_MODE

TARGET = utvonaltervezo

CPPS = main.cpp graph.cpp planner.cpp file.cpp
CS = memtrace.c

OBJS = 	$(CPPS:.cpp=.o) $(CS:.c=.o)


all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)
	@echo "Sikeres fordítás: $(TARGET)"

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

%.o: %.c
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)
	rm -f $(TARGET).dSYM
	@echo "Takarítás kész."

run: all
	./$(TARGET)

.PHONY: all clean run