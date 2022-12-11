#include "CellTile.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <stdlib.h>
using namespace std;

CellTile::CellTile() {

}

CellTile::CellTile(bool deadAlive, int y) {

	perlinValue = 0.0;
	gene[0] = 3;
	gene[1] = 3;
	gene[2] = 3;
	box.setSize(sf::Vector2f(4, 4));
	temp = ((float)(y+1) / 201); //value between 0 and 1, higher temperature at lower latitudes
    living = deadAlive;
	species = 0;
	size = 0.0; //val between 0 and 1

	box.setFillColor(sf::Color::Black);
}

void CellTile::setAliveOnStartUp(bool life, int speciesAssign) {

		species = speciesAssign;
		living = life;
		setGeneOnStartup(1 + (std::rand() % (100 - 1 + 1)), 1 + (std::rand() % (100 - 1 + 1)), 1 + (std::rand() % (100 - 1 + 1)));
		setUpSize();
		setUpBoxColor();
	
}

void CellTile::setAlive(bool life, float parentSize, int speciesAssign) {
	
		if (life && perlinValue > .2 && perlinValue < .7) {
			species = speciesAssign;
			living = life;
			setGene(parentSize, 1 + (std::rand() % (100 - 1 + 1)), 1 + (std::rand() % (100 - 1 + 1)), 1 + (std::rand() % (100 - 1 + 1)));
			setUpSize();
			setUpBoxColor();
		}
		else {
			species = 0;
			living = false;
			size = 0.0;
			gene[0] = 3;
			gene[1] = 3;
			gene[2] = 3;
			setUpBoxColor();

		}
	
}

void CellTile::setUpSize() {

	if (gene[0] == 0 && gene[1] == 0 && gene[2] == 0) {
		size = .125;
	}
	else if (gene[0] == 1 && gene[1] == 0 && gene[2] == 0) {
		size = .250;
	}
	else if (gene[0] == 0 && gene[1] == 1 && gene[2] == 0) {
		size = .375;
	}
	else if (gene[0] == 1 && gene[1] == 1 && gene[2] == 0) {
		size = .500;
	}
	else if (gene[0] == 0 && gene[1] == 0 && gene[2] == 1) {
		size = .625;
	}
	else if (gene[0] == 1 && gene[1] == 0 && gene[2] == 1) {
		size = .750;
	}
	else if (gene[0] == 0 && gene[1] == 1 && gene[2] == 1) {
		size = .875;
	}
	else if (gene[0] == 1 && gene[1] == 1 && gene[2] == 1) {
		size = 1;
	}

	//if temperature is larger, size is smaller
	//if temperature is smaller, size is larger
	//temp is between 0 and 1

}

void CellTile::setUpBoxColor() {

	if (living && species == 1) {

		box.setFillColor(sf::Color(0, size * 200, 200, 255));
	}
	else if (living && species == 2) {

		box.setFillColor(sf::Color(size * 200, 200, 0, 255));
	}
	else if (living && species == 3) {

		box.setFillColor(sf::Color(200, 0, size * 200, 255));
	}
	else {
		box.setFillColor(sf::Color::Black);
	}
}

void CellTile::setGeneOnStartup(int randNum1, int randNum2, int randNum3) { 
	
	// distribution based on temperature (not even distribution) 
	
	//cout << temp << endl;
	
	/*if (temp <= .125) {
		gene[0] = 1;
		gene[1] = 1;
		gene[2] = 1;
	}
	else if (temp <= .250) {
		gene[0] = 0;
		gene[1] = 1;
		gene[2] = 1;
	}
	else if (temp <= .375) {
		gene[0] = 1;
		gene[1] = 0;
		gene[2] = 1;
	}
	else if (temp <= .5) {
		gene[0] = 0;
		gene[1] = 0;
		gene[2] = 1;
	}
	else if (temp <= .625) {
		gene[0] = 1;
		gene[1] = 1;
		gene[2] = 0;
	}
	else if (temp <= .750) {
		gene[0] = 0;
		gene[1] = 1;
		gene[2] = 0;
	}
	else if (temp <= .875) {
		gene[0] = 1;
		gene[1] = 0;
		gene[2] = 0;
	}
	else if (temp <= 1) {
		gene[0] = 0;
		gene[1] = 0;
		gene[2] = 0;
	}*/


	if (randNum1 > 50) {
		gene[0] = 1;
	}
	else {
		gene[0] = 0;
	}

	if (randNum2 > 50) {
		gene[1] = 1;
	}
	else {
		gene[1] = 0;
	}

	if (randNum3 > 50) {
		gene[2] = 1;
	}
	else {
		gene[2] = 0;
	}

}

void CellTile::setGene(float parentSize, int mutationG1, int mutationG2, int mutationG3) {

	//cout << "1st:"<<mutationG1 << " 2nd:" << mutationG2 << " 3rd:" << mutationG3;

	if (parentSize <= .125) {
		gene[0] = 0;
		gene[1] = 0;
		gene[2] = 0;
	}
	else if (parentSize <= .250) {
		gene[0] = 1;
		gene[1] = 0;
		gene[2] = 0;
	}
	else if (parentSize <= .375) {
		gene[0] = 0;
		gene[1] = 1;
		gene[2] = 0;
	}
	else if (parentSize <= .5) {
		gene[0] = 1;
		gene[1] = 1;
		gene[2] = 0;
	}
	else if (parentSize <= .625) {
		gene[0] = 0;
		gene[1] = 0;
		gene[2] = 1;
	}
	else if (parentSize <= .750) {
		gene[0] = 1;
		gene[1] = 0;
		gene[2] = 1;
	}
	else if (parentSize <= .875) {
		gene[0] = 0;
		gene[1] = 1;
		gene[2] = 1;
	}
	else if (parentSize <= 1) {
		gene[0] = 1;
		gene[1] = 1;
		gene[2] = 1;
	}
	

	if (mutationG1 <= 10) {
		if (gene[0] == 0) {
			gene[0] = 1;
		}
		else {
			gene[0] = 0;
		}

	//	//cout << " --> mutation in gene 1";
	}
	//else {
	//	//cout << "                       ";
	//}

	if (mutationG2 <= 5) {
		if (gene[1] == 0) {
			gene[1] = 1;
		}
		else {
			gene[1] = 0;
		}
	//	//cout << " --> mutation in gene 2";

	}
	//else {
	//	//cout << "                       ";
	//}

	if (mutationG3 <= 1) {
		if (gene[2] == 0) {
			gene[2] = 1;
		}
		else {
			gene[2] = 0;
		}
		//cout << " --> mutation in gene 3";

	}
	//else {
	//	//cout << "                       ";
	//}

	//cout<<endl;

	//gene mutatgion rates for size is something to research, these values have no real life basis

} //takes a parent size and gives you a gene, with mutations included in the calculation

void CellTile::setSize(float mParentSize) {
	size = mParentSize;
}

bool CellTile::isAlive() {

	return living;
}


//dont think i need isalive and get position
