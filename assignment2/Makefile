main: EntityManager.cpp Game.cpp main.cpp Vec2.cpp
	g++ *.cpp -Isrc -std=c++23 -o bin/sfmlgame -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

test: tests/testentity.cpp
	g++ tests/testentity.cpp -Isrc -std=c++23 -o bin/testentity -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio