#include "Player.h"
#include "Fruits.h"
#include <iostream>
#include <windows.h>

Player::Player(sf::RenderWindow &window )
{

	playerBody.setSize(sf::Vector2f(20.0f, 20.0f));
	playerBody.setPosition(sf::Vector2f(window.getSize().x/2-30, window.getSize().y/2+330));
	playerBody.setFillColor(sf::Color::Green);
	actualDir = LEFT;
	timer = 0;
	
}
Player::Player()
{
	;
}

Player::~Player()
{
	
}
void Player::setHeadPosition(sf::RenderWindow &window, unsigned int &lvl)
{
	;
}

int Player::speedSetup(sf::RenderWindow &window, bool &easylvl, bool &mediumlvl, bool &hardlvl)
{
	
		if (easylvl)
		{
			difficultyValue = 0;
		}
		else if (mediumlvl)
		{
			difficultyValue = 1;

		}
		else if (hardlvl)
		{
			difficultyValue = 2;

		}


	return difficultyValue;
}

void Player::snakeMove(sf::RenderWindow &window, bool &isPressed, Player&snakeObject, std::vector<Player> &snakeVector, bool &playerAlive, bool& lvlchanged, bool &easylv, bool &mediumlv, bool &hardlv)
{
	
	isPressed = false;
	//SPEED
	speedSetup(window, easylv, mediumlv, hardlv);
	unsigned int *difficultyPtr = &difficultyValue;
	switch (*difficultyPtr)
	{
	case 0: snakeMovementSpeed = 7; break;
	case 1: snakeMovementSpeed = 6; break;
	case 2: snakeMovementSpeed = 4; break;

	}
	
	//MOVEMENT TIMER
	if (timer <= snakeMovementSpeed)
	{
		timer++;
		
		
	}
	//CONTROL KEYS
	if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)) && actualDir != RIGHT && !(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) && !(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)))
		{

			actualDir = LEFT;

		}
		else if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W) ||sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up)) && actualDir != DOWN&& !(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) && !(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)))
		{
			actualDir = UP;

		}
		else if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down)) && actualDir != UP&& !(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) && !(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)))
		{

			actualDir = DOWN;

		}
		else if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)) && actualDir != LEFT && !(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) && !(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)))
		{
			actualDir = RIGHT;
		}
		
	
	

	//IF PLAYER IS ALIVE - CHECKING DIRECTION
	if (playerAlive)
	{

		switch (actualDir)
		{
		case LEFT:
			if (timer >= snakeMovementSpeed)
			{
				isPressed = true;
				snakeVector[0].playerBody.setPosition(snakeVector[0].playerBody.getPosition().x - 20, snakeVector[0].playerBody.getPosition().y);
				timer = 0;

			}break;
		case RIGHT:
			if (timer >= snakeMovementSpeed)
			{
				isPressed = true;
				snakeVector[0].playerBody.setPosition(snakeVector[0].playerBody.getPosition().x + 20, snakeVector[0].playerBody.getPosition().y);
				timer = 0;
				if (lvlchanged == true)
					actualDir = LEFT;
			}break;
		case UP:
			if (timer >= snakeMovementSpeed)
			{
				isPressed = true;
				snakeVector[0].playerBody.setPosition(snakeVector[0].playerBody.getPosition().x, snakeVector[0].playerBody.getPosition().y - 20);
				timer = 0;
				if (lvlchanged == true)
					actualDir = LEFT;
			}break;

		case DOWN:
			if (timer >= snakeMovementSpeed)
			{
				isPressed = true;
				snakeVector[0].playerBody.setPosition(snakeVector[0].playerBody.getPosition().x, snakeVector[0].playerBody.getPosition().y + 20);
				timer = 0;
				if (lvlchanged == true)
					actualDir = LEFT;
			}break;
		}

	}
	

	
}
void Player::bodyUpdate(sf::RenderWindow &window, bool &isPressed, std::vector<Fruits> &fruitVector, std::vector<Player> &snakeVector, Player *snakePtr, int ArrayX[400], int ArrayY[400], bool &playerAlive)
{
	if (snakeVector.empty())
	{
		snakeVector.push_back(*snakePtr);
		
	}
	if (fruitVector.empty())
		snakeVector.push_back(*snakePtr);

	for (int i = 0; i < snakeVector.size(); i++)
	{
		if (isPressed == false)
		{


			ArrayX[i] = snakeVector[i].playerBody.getPosition().x;
			ArrayY[i] = snakeVector[i].playerBody.getPosition().y;



		}
		if (isPressed == true)
		{
			if (i != 0)
			{
				snakeVector[i].playerBody.setPosition(ArrayX[i - 1], ArrayY[i - 1]);

			}
		}
		if (playerAlive)
		{
			snakeVector[i].playerBody.setFillColor(sf::Color::Green);
			window.draw(snakeVector[i].playerBody);
		}
		else if (!playerAlive)
		{
			snakeVector[i].playerBody.setFillColor(sf::Color::Red);
			window.draw(snakeVector[i].playerBody);
			
		}
	}

	

}
void::Player::acrossTheWall(sf::RenderWindow &window, std::vector<Player> &snakeVector)
{
	for (int i = 0; i < snakeVector.size(); i++)
	{
		//RIGHT WALL PROTECTION
		if (snakeVector[i].playerBody.getPosition().x > window.getSize().x)
		{
			snakeVector[i].playerBody.setPosition(window.getSize().x-window.getSize().x+10, snakeVector[i].playerBody.getPosition().y);
		}
		//BOTTOM WALL PROTECTION
		else if (snakeVector[i].playerBody.getPosition().y > 859)
		{
			snakeVector[i].playerBody.setPosition(snakeVector[i].playerBody.getPosition().x, window.getSize().y-window.getSize().y+20);
		}
		//LEFT WALL PROTECION
		else if (snakeVector[i].playerBody.getPosition().x < window.getSize().x-window.getSize().x)
		{
			snakeVector[i].playerBody.setPosition(window.getSize().x-10 , snakeVector[i].playerBody.getPosition().y);
		}
		//TOP WALL PROTECTION
		else if (snakeVector[i].playerBody.getPosition().y < 1)
		{
			snakeVector[i].playerBody.setPosition(snakeVector[i].playerBody.getPosition().x, window.getSize().y-20);
		}
	}
		
}
void::Player::selfCollision(std::vector<Player> &snakeVector, bool &playerAlive)
{
	//DYING BY SELF COLLISION
	for (int i = 3; i < snakeVector.size(); i++)
	{
		if (snakeVector[0].playerBody.getGlobalBounds().intersects(snakeVector[i].playerBody.getGlobalBounds())&&snakeVector.size()>3)
		{
			playerAlive = false;
			
			
				
		}
		
	}
		
}


