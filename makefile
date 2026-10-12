CXX      = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -pedantic -g

slm: main.cpp
	$(CXX) $(CXXFLAGS) -o slm src/main.cpp

clean:
	rm -f slm

.PHONY: clean