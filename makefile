CXX = g++
CXXFLAGS = -std=c++11 -Wall

OBJECTS = game.o
HEADERS = $(shell find . -path ./test -prune -o -name "*.hpp" -print)

main: main.o $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $^

game.o: game.hpp game.cpp
	$(CXX) $(CXXFLAGS) -c game.cpp

$(OBJECTS): $(HEADERS)

clean:
	$(RM) *.o *.gch core main test/TestCase
