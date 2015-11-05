cmake_minimum_required(VERSION 3.0)
project(BattleShip)

SET(CMAKE_CXX_COMPILER "clang++")
SET(CC "clang++")

SET(CMAKE_CXX_FLAGS "-Wall --std=c++11")

add_executable(battleship
	"src/ui.cpp"
	"src/gameconf.cpp"
	"src/map.cpp"
	"src/gm.cpp"
	"src/main.cpp"
)

