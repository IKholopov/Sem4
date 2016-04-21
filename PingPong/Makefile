all: pingpong nopingpong
pingpong: pingpong.cpp
	g++ -std=c++14 -o pingpong -lpthread pingpong.cpp
nopingpong: nopingpong.cpp
	g++ -std=c++14 -o nopingpong -lpthread nopingpong.cpp
clean:
	rm pingpong nopingpong
