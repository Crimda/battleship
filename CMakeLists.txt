cmake_minimum_required(VERSION 3.0)
project(BattleShip)

SET(CMAKE_CXX_COMPILER "clang++")
SET(CC "clang++")

SET(CMAKE_CXX_FLAGS "-Wall --std=c++11")

add_executable(battleship
	"src/types.cpp"
	"src/ship.cpp"
	"src/ui.cpp"
	"src/util.cpp"
	"src/map.cpp"
	"src/ai.cpp"
	"src/gm.cpp"
	"src/main.cpp"
)

