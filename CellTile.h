#include <SFML/Graphics.hpp>

#ifndef GAMETILE_H
#define GAMETILE_H

class CellTile {

public:

	int gene[3];
	int species; //false = coyote, true = wolf
	double perlinValue;
	bool living;
	float temp;
	float size;

	sf::Vector2f pos; //x and y values for position of gametile
	sf::RectangleShape box;

	CellTile();
	CellTile(bool,int);
	void setUpBoxColor();
	bool isAlive();
	void setGene(float,int,int,int);
	void setAliveOnStartUp(bool,int);
	void setUpSize();
	void setGeneOnStartup(int,int,int);
	void setSize(float);
	void setAlive(bool,float,int);
};

#endif
