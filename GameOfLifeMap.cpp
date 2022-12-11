#include <SFML/Graphics.hpp>
#include "GameOfLifeMap.h"
#include <array>
#include <iostream>
using namespace std;

GameOfLifeMap::GameOfLifeMap() {
	gridLength = 200;
	setUpInitialState();
}

void GameOfLifeMap::setUpInitialState() {

	setUpTiles(); 
}

void GameOfLifeMap::setUpTiles() { //understand vectors and get them working

	for (int i = 0; i < gridLength; i++) {

		CellTile* row = new CellTile[gridLength];
		for (int a = 0; a < gridLength; a++) {
			CellTile* cell = new CellTile(false,i);
			row[a] = *cell;
		}
		cells[i] = row;
	}
	for (int a = 0; a < gridLength; a++) {
		for (int i = 0; i < gridLength; i++) {
			cells[a][i].box.setPosition(sf::Vector2f(i * 4, a * 4));
		}
	}


}