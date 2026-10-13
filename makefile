CXX      = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -pedantic -g

slm: src/main.cpp src/functions.h
	$(CXX) $(CXXFLAGS) -o slm src/main.cpp

clean:
	rm -f slm

.PHONY: clean