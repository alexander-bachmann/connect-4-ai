CXX = g++
CXXFLAGS = -std=c++11 -Wall

OBJECTS = game.o aiplayer.o humanplayer.o
HEADERS = $(shell find . -path ./test -prune -o -name "*.hpp" -print)

main: main.o $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $^

game.o: game.hpp game.cpp
	$(CXX) $(CXXFLAGS) -c game.cpp

aiplayer.o: aiplayer.hpp aiplayer.cpp
	$(CXX) $(CXXFLAGS) -c aiplayer.cpp

humanplayer.o: humanplayer.hpp humanplayer.cpp
	$(CXX) $(CXXFLAGS) -c humanplayer.cpp

$(OBJECTS): $(HEADERS)

clean:
	$(RM) *.o *.gch core main test/TestCase
