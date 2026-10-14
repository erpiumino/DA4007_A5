CXX      = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -pedantic -g

OBJ = src/main.o src/Config.o src/Vocabulary.o

slm: $(OBJ)
	$(CXX) $(CXXFLAGS) -o slm $(OBJ)

src/main.o: src/main.cpp src/Config.h src/Vocabulary.h
	$(CXX) $(CXXFLAGS) -c src/main.cpp -o src/main.o

src/config.o: src/config.cpp src/Config.h
	$(CXX) $(CXXFLAGS) -c src/Config.cpp -o src/Vonfig.o

src/vocabulary.o: src/Vocabulary.cpp src/Vocabulary.h
	$(CXX) $(CXXFLAGS) -c src/Vocabulary.cpp -o src/Vocabulary.o

clean:
	rm -f slm src/*.o

.PHONY: clean