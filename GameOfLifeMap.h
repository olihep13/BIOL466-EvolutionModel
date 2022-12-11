#pragma once
#include <SFML/Graphics.hpp>
#include "CellTile.h"
#include <array>
#include <vector> //our multidimensional arrays for our map of cells

#ifndef GAMEOFLIFEMAP_H                          
#define GAMEOFLIFEMAP_H                                       

class GameOfLifeMap { 
// map with grid of tiles, so vector of vector of the game cells.
// the map itself is made of cells that are either alive, empty, food, or a barrier

public:

	CellTile* cells[200];
	int gridLength;
	GameOfLifeMap();
	void setUpInitialState(); //want to use state machine for p[ause menu, maybe stats menmu
	void setUpTiles();

};

#endif