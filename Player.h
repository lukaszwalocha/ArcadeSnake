#pragma once
#include <SFML/Graphics.hpp>
#include "Fruits.h"
#include "TextItems.h"


class Fruits;

class Player
{
	
private:
	
	int snakeMovementSpeed;
	unsigned int timer;
	enum dir{ LEFT, RIGHT, UP, DOWN };
	int actualDir;
	
	
	
public:
	Player(sf::RenderWindow &);
	Player();
	~Player();
	void snakeMove(sf::RenderWindow &, bool &, Player &, std::vector<Player> &, bool&, bool&, bool&, bool&, bool&);
	void acrossTheWall(sf::RenderWindow &, std::vector<Player> &);
	void bodyUpdate(sf::RenderWindow &, bool&, std::vector<Fruits> &, std::vector<Player> &, Player *snakePtr, int ArrayX[300], int Array[300], bool&);
	void selfCollision(std::vector<Player> &, bool &);
	void setHeadPosition(sf::RenderWindow &, unsigned int &);
	int speedSetup(sf::RenderWindow &,bool &, bool &, bool &);
	sf::RectangleShape playerBody;
	unsigned int difficultyValue;
	

	
};

