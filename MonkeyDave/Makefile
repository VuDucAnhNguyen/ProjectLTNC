CXX = g++

CXXFLAGS = $(shell sdl2-config --cflags)
LIBS = $(shell sdl2-config --libs) -lSDL2_image -lSDL2_mixer -lSDL2_ttf

TARGET = play_game

all:
	$(CXX) *.cpp $(CXXFLAGS) $(LIBS) -o $(TARGET)

clean:
	rm -f $(TARGET)