#include <SFML/Graphics.hpp>c
#include <SFML/Audio.hpp>
#include "GameOfLifeMap.h"
#include <stdlib.h>
#include "PerlinNoise.h"
#include <stdio.h>
#include <fstream>
#include <iostream>


using namespace std;

float fitnessFunction(GameOfLifeMap* output, GameOfLifeMap* current, int cellWindow_X, int cellWindow_Y, int x, int y, float averageBodySize, int species) {

	float mostFitSize = -1.0, mostFitValue = 0, bestSize = 1 - averageBodySize;
	int c = 0;
	float localCompetitiveBodyMass = 0.0;

	for (int i = -1; i <= 1; i++) {
		for (int j = -1; j <= 1; j++) {

			int x2 = x + i;
			int y2 = y + j;

			if (!(i == 0 && j == 0)) {

				if (0 < x2 && x2 < (cellWindow_X) && (0 < y2) && y2 < (cellWindow_Y)) {

					if (current->cells[x2][y2].isAlive() && current->cells[x2][y2].species == species) {


						if (abs((1-current->cells[x][y].temp)- current->cells[x2][y2].size) <= .3 && abs((1 - current->cells[x][y].temp) - mostFitSize) > abs((1 - current->cells[x][y].temp) - current->cells[x2][y2].size)){
							
								mostFitSize = current->cells[x2][y2].size;
						}
					}

					if (current->cells[x2][y2].isAlive() && current->cells[x2][y2].species != species && current->cells[x2][y2].species != 0) {
						localCompetitiveBodyMass = localCompetitiveBodyMass + current->cells[x2][y2].size;
						c++;
					}
				}
			}


		}
	}//most close to ideal size for temp location is most fit

	//perlin map gave way to evolution accidentally, counted empty spaces as a species and 
	//used their size =0  to select for a large size in the surrdoing species

	localCompetitiveBodyMass = localCompetitiveBodyMass / c;

	if (c > 0) {

		for (int i = -1; i <= 1; i++) {
			for (int j = -1; j <= 1; j++) {

				int x2 = x + i;
				int y2 = y + j;

				if (!(i == 0 && j == 0)) {

					if (0 < x2 && x2 < (cellWindow_X) && (0 < y2) && y2 < (cellWindow_Y)) {

						if (current->cells[x2][y2].isAlive() && current->cells[x2][y2].species == species) {

							if (localCompetitiveBodyMass > current->cells[x2][y2].size) {
								if (mostFitValue < (localCompetitiveBodyMass- current->cells[x2][y2].size)) {

									mostFitValue = (localCompetitiveBodyMass - current->cells[x2][y2].size);
									mostFitSize = current->cells[x2][y2].size;
								}
							}
							else {
								if (mostFitValue < (current->cells[x2][y2].size - localCompetitiveBodyMass)) {

									mostFitValue = (current->cells[x2][y2].size - localCompetitiveBodyMass);
									mostFitSize = current->cells[x2][y2].size;
								}
							}
						}
					}
				}
			}
		}
	} //largest difference in body size is more fit. This only occurs if species 2 is in neighborhood of species 1.


	//remeber we will be testing on more than two species, must account for that in the alg
	////

	///
	///
	/// 

	return mostFitSize;
}

void selection(GameOfLifeMap* output, GameOfLifeMap* current, bool cur,float yourSize, float yourTemp,int species, int liveNeighbors, int cellWindow_X, int cellWindow_Y,int averageBodySize,int a,int i) {
	
	//2x2
	//conway game of life
	//pseudo life


	//2x2
	if (cur) {

		if ((liveNeighbors != 5 && liveNeighbors!= 1 && liveNeighbors != 2)) {

		output->cells[a][i].setAlive(false,0.0,0);
		}
	}
	else if (!cur) {


		if (liveNeighbors == 3 || liveNeighbors == 6) {

				float size = fitnessFunction(output, current, cellWindow_X, cellWindow_Y, a, i, averageBodySize, species);
				if (size != -1.0) {
					output->cells[a][i].setAlive(true, size, species);
				}
				//cout << mBodySize2 / species2Count << endl;
		}

	}

	
	//john conway game of life
	/*if (cur) {

		if ((liveNeighbors < 2 || liveNeighbors >3)) {

			output->cells[a][i].setAlive(false, 0.0, 0);
		}
	}
	else if (!cur) {


		if (liveNeighbors == 3) {

			float size = fitnessFunction(output, current, cellWindow_X, cellWindow_Y, a, i, averageBodySize, species);
			if (size != -1.0) {
				output->cells[a][i].setAlive(true, size, species);
			}
			//cout << mBodySize2 / species2Count << endl;
		}

	}*/



	
	//pseudo life
	
	/*if (cur) {

		if ((liveNeighbors < 2 || liveNeighbors >3) && liveNeighbors != 8) {

			output->cells[a][i].setAlive(false, 0.0, 0);
		}
	}
	else if (!cur) {


		if (liveNeighbors == 3 || liveNeighbors == 5 || liveNeighbors == 7) {

			float size = fitnessFunction(output, current, cellWindow_X, cellWindow_Y, a, i, averageBodySize, species);
			if (size != -1.0) {
				output->cells[a][i].setAlive(true, size, species);
			}
			//cout << mBodySize2 / species2Count << endl;
		}

	}*/

	
	//if when dead and neighbors around you == 3, you become the species 
	//that is most around you
	//john conway game of life rules

}

void neighBorhoodCount(GameOfLifeMap* output, GameOfLifeMap* current, int cellWindow_X, int cellWindow_Y,int x, int y) {

	int species1Count = 0, species2Count = 0, species3Count = 0;
	int liveNeighbors = 0;
	bool cur = current->cells[x][y].isAlive();
	float bodySize1 = 0.0, bodySize2 = 0.0, bodySize3 = 0.0;

	for (int c = -1; c <= 1; c++) {
		for (int d = -1; d <= 1; d++) {

			if (!(c==0 && d==0)) {

				int x2 = x + d;
				int y2 = y + c;
				if (0 < x2 && x2 < (cellWindow_X-1) && (0 < y2) && y2 < (cellWindow_Y-1)) {

					if (current->cells[x2][y2].isAlive()) {

						if (current->cells[x2][y2].species == 1) {
							species1Count++;
							bodySize1 = bodySize1 + current->cells[x2][y2].size;
						}
						else if (current->cells[x2][y2].species == 2) {
							species2Count++;
							bodySize2 = bodySize2 + current->cells[x2][y2].size;
						}
						else {
							species3Count++;
							bodySize3 = bodySize3 + current->cells[x2][y2].size;
						}
						liveNeighbors++;
					}
					
				}
			}
		}
	}

	//above we are checking all 8 neighbors of our cell. if alive, we note their species
	//and +1 to our live neighbor species
	
	float averageBodySize = (bodySize1 + bodySize2 + bodySize3) / (species1Count + species2Count + species3Count);
	
	float domSpecies = 0.0;


		if (species1Count >= species2Count && species1Count >= species3Count) {
			domSpecies = 1;
		}
		else if (species2Count >= species1Count && species2Count >= species3Count) {
			domSpecies = 2;
		}
		else if (species3Count >= species1Count && species3Count >= species2Count) {
			domSpecies = 3;
		}

		selection(output, current, cur, current->cells[x][y].size, current->cells[x][y].temp, domSpecies, liveNeighbors, cellWindow_X, cellWindow_Y, averageBodySize, x, y);

}

int main() {

	int randNum, randSpecies;
	srand(time(NULL));

	int windowSize_X = 800;
	int windowSize_Y = 800;

	int cellWindow_X = windowSize_X / 4;
	int cellWindow_Y = windowSize_Y / 4;

	//create main window
	sf::RenderWindow window(sf::VideoMode(windowSize_X, windowSize_Y), "GameOfLife");
	GameOfLifeMap* output = new GameOfLifeMap();
	GameOfLifeMap* current = new GameOfLifeMap();
	*output = *current;
	
	for (int a = 0; a < cellWindow_X; a++) {
		for (int i = 0; i < cellWindow_Y; i++) {

			//if (a>150) {
				randNum = rand() % 10 + 1;

					if (randNum > 9) {

						/*if (i < 75) {
							current->cells[a][i].setAliveOnStartUp(true, 1);
						}
						else if (i > 125) {
							current->cells[a][i].setAliveOnStartUp(true, 2);
						}*/

						if (a > 130 && i < 40) {
							current->cells[a][i].setAliveOnStartUp(true, 3);
						}
						else if (a < 50 && i < 75) {
								current->cells[a][i].setAliveOnStartUp(true, 1);
							}
						else if (a >70 && a< 110 && i > 125) {
								current->cells[a][i].setAliveOnStartUp(true, 2);
							} //both if statements above deliminate a starting range
					}
					
			// above is for two species initialization
			//all cells are dead initially. 1/10 chance of becoming living cell. if you become
			//a living cell you have a 1/2 chance of becoming species 1, 1/2 chance of becoming species 2
			
			/*if (randNum > 9) {
				
				current->cells[a][i].species = 1;
				current->cells[a][i].setAliveOnStartUp(true);

			}*/	
		}
	}

	*output = *current;
	double zoff = 0;

	ofstream aFile;
	aFile.open("C:/Users/OLIVI/gnuplot/C_Scripts/allopatricData.tmp", ios::out);

	ofstream sFile;
	sFile.open("C:/Users/OLIVI/gnuplot/C_Scripts/sympatricData.tmp", ios::out);

	ofstream tFile;
	tFile.open("C:/Users/OLIVI/gnuplot/C_Scripts/tTestData.tmp", ios::out);

	std::vector<float>* sympX = new vector<float>;
	std::vector<float>* sympY = new vector<float>;

	std::vector<float>* allopX = new vector<float>;
	std::vector<float>* allopY = new vector<float>;

	std::vector<string>* tTestX = new vector<string>;
	std::vector<float>* tTestM = new vector<float>;
	std::vector<float>* tTestSTD = new vector<float>;

	//start game loop

	int xS = 0, xA = 0;
	while (window.isOpen())
	{
		window.setFramerateLimit(90);

		//process events
		sf::Event event;
		if (window.pollEvent(event)) {
			//close the window
			if (event.type == sf::Event::Closed)
				window.close();
		}

		while (window.isOpen() && sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		{

			window.clear();

			PerlinNoise pn;
			float inc = .02;

			double yoff = 0;

			for (int a = 0; a < cellWindow_X; a++) {
				double xoff = 0;
				for (int i = 0; i < cellWindow_Y; i++) {

					double noise = pn.noise(xoff, yoff, zoff);

					current->cells[a][i].perlinValue = noise;
					xoff += inc;

				}
				yoff += inc;
			}

			zoff += inc;

			//set noise value for each cell to noise value above. say if your above .8 or bellow .2 you die and can't live. tweak this a bit
			int c = 0;

			int species1 = 0, species2 = 0;

			for (int x = 0; x < cellWindow_X; x++) {
				for (int y = 0; y < cellWindow_Y; y++) {

					neighBorhoodCount(output, current, cellWindow_X, cellWindow_Y, x, y);

					window.draw(output->cells[x][y].box);

					int randX = 0, randY = 0;
					randX = rand() % cellWindow_X;
					randY = rand() % cellWindow_Y;

					if (c==0) {

						int species = output->cells[randX][randY].species;
						species1 = species;

						if (output->cells[randX][randY].isAlive()) {

							for (int i = -1; i <= 1; i++) {
								for (int j = -1; j <= 1; j++) {

									int x2 = randX + i;
									int y2 = randY + j;

									if (!(i == 0 && j == 0)) {

										if (0 < x2 && x2 < (cellWindow_X) && (0 < y2) && y2 < (cellWindow_Y)) {

											if (output->cells[x2][y2].isAlive() && output->cells[x2][y2].species != species) {

												species2 = output->cells[x2][y2].species;

												//we have size difference in sympatric cells and the species values involved
												//lets looks for two cells not living in sympatry, one for each species involved in the sympatry pair
												//record size difference

												//go through each row of the map, look for two cells of species 1 and 2 respectively that are allopatric, if not found skip data point for allopatric cells
												//make sure to be random

												for (int x = 0; x < cellWindow_X; x++) {

													int xcoord = rand() % cellWindow_X;
													//get random row to check for appropriate cells

													for (int y = 0; y < cellWindow_Y; y++) {

														if (output->cells[xcoord][y].isAlive() && output->cells[xcoord][y].species == species1) {
															int counter = 0;
															for (int i = -1; i <= 1; i++) {
																for (int j = -1; j <= 1; j++) {

																	int x2 = xcoord + i;
																	int y2 = y + j;

																	if (!(i == 0 && j == 0)) {

																		if (0 < x2 && x2 < (cellWindow_X) && (0 < y2) && y2 < (cellWindow_Y)) {

																			if (output->cells[x2][y2].isAlive() && output->cells[x2][y2].species != species1) {

																				counter++;
																			}

																		}

																	}

																}
															}

															if (counter == 0) {
																//if within that row we have one allopatric cell for species 1, 
																//lets look for one for species 2

																for (int y1 = 0; y1 < cellWindow_Y; y1++) {

																	if (output->cells[xcoord][y1].isAlive() && output->cells[xcoord][y1].species == species2) {
																		int counter = 0;
																		for (int i = -1; i <= 1; i++) {
																			for (int j = -1; j <= 1; j++) {

																				int x2 = xcoord + i;
																				int y2 = y1 + j;

																				if (!(i == 0 && j == 0)) {

																					if (0 < x2 && x2 < (cellWindow_X) && (0 < y2) && y2 < (cellWindow_Y)) {

																						if (output->cells[x2][y2].isAlive() && output->cells[x2][y2].species != species2) {

																							counter++;
																						}

																					}

																				}

																			}
																		}

																		if (counter == 0) {
																			//if within that row we have one allopatric cell for species 2, 
																			//lets add them to the array

																			allopX->push_back(xS);
																			allopY->push_back(abs(output->cells[xcoord][y].size - output->cells[xcoord][y1].size));

																			sympX->push_back(xS);
																			sympY->push_back(abs(output->cells[x2][y2].size - output->cells[randX][randY].size));

																			y1 = cellWindow_Y;
																			y = cellWindow_Y;
																			x = cellWindow_X;

																			xA++;
																			xS++;

																		}

																	}

																}

															}

														}

													}

												}



												i = 2;
												j = 2;
												c++;
											}

										}

									}

								}
							}
						}

					}

				}
			}

		

			window.display();

			*current = *output;
			//update the window, end the current frame
		}
	}

	tTestX->push_back("sympatric");
	tTestX->push_back("allopatric");

	float popSize = 0.0;
	float popSum = 0.0;

	auto y = sympY->begin();
	for (auto x = sympX->begin(); x != sympX->end(); ++x) {
		popSum = popSum + *y;
		popSize = *x;
		//this is the size of our population on the last looping of this for loop
		++y;
	}
	float mean = popSum / (popSize+1);
	tTestM->push_back(mean);
	float stdSum = 0.0;
	y = sympY->begin();
	for (auto x = sympX->begin(); x != sympX->end(); ++x) {
		stdSum = stdSum + powf((*y - mean), 2.0);
		++y;
	}
	tTestSTD->push_back(powf(stdSum/(popSize+1),.5));




	popSize = 0.0;
	popSum = 0.0;
	y = allopY->begin();
	for (auto x = allopX->begin(); x != allopX->end(); ++x) {
		popSum = popSum + *y;
		popSize = *x;
		//this is the size of our population on the last looping of this for loop
		++y;
	}
	mean = popSum / (popSize+1);
	tTestM->push_back(mean);
	stdSum = 0.0;
	y = allopY->begin();
	for (auto x = allopX->begin(); x != allopX->end(); ++x) {
		stdSum = stdSum + powf((*y - mean), 2.0);
		++y;
	}
	tTestSTD->push_back(powf(stdSum / (popSize+1), .5));

	y = sympY->begin();
	for (auto x = sympX->begin(); x != sympX->end(); ++x){
		sFile << *y << "\n";
		//sFile << *x << " "<<*y<<"\n";
		++y;
	}

	y = allopY->begin();
	for (auto x = allopX->begin(); x != allopX->end(); ++x) {
		aFile << *y << "\n";
		//aFile << *x << " " << *y << "\n";
		++y;
	}

	y = tTestM->begin();
	auto z = tTestSTD->begin();
	for (auto x = tTestX->begin(); x != tTestX->end(); ++x) {
		tFile << *x << " " << *y << " " << *z << "\n";
		++y;
		++z;
	}

	allopX->clear();
	allopY->clear();

	sympX->clear();
	sympY->clear();

	tTestX->clear();
	tTestM->clear();
	tTestSTD->clear();

	aFile.close();
	sFile.close();
	tFile.close();

	return EXIT_SUCCESS;

	

}