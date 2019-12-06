CXX = g++ 
CXXFLAGS = -g3 -Wall -Wextra -std=c++17

all: task1.elf task2.elf

%.o: %.cpp
	$(CXX) -c $(CXXFLAGS) $< -o $@
%.elf: %.o
	$(CXX) $(CXXFLAGS) $< -o $@
clean:
	rm -fv task1.elf task2.elf

.PHONY: all clean

