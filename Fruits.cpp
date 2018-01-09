#include "Fruits.h"
#include "Player.h"
#include "TextItems.h"
#include <iostream>

Fruits::Fruits()
{
	fruitShape.setSize(sf::Vector2f(20.0f, 20.0f));
	fruitShape.setFillColor(sf::Color::Cyan);
	appleTexture.loadFromFile("apple1.png");
	appleSprite.setTexture(appleTexture);
	appleSprite.setPosition(rand() % int(500) + 1, rand() % int(500) + 1);
	//BITESOUND
	appleBuffer.loadFromFile("apple_bite.wav");
	appleBite.setBuffer(appleBuffer);

}


Fruits::~Fruits()
{	
	;
}

void Fruits::randomPosition(sf::RenderWindow &window, std::vector<Fruits> &fruitVector, std::vector<Player>& bodyVector, Fruits &object, bool&pressed, int &pts, std::string &ptsString, bool &playerAl)
{
	
	
	if (fruitVector.empty())
	{
		pts++;
		
		ptsString = std::to_string(pts);
		
		
		fruitVector.push_back(object);
		
		object.appleSprite.setPosition(rand() % int(window.getSize().x - 0.1*window.getSize().x), rand() % int(window.getSize().y - 0.1*window.getSize().y));
		
	}

	if (playerAl)
		ptsString = std::to_string(pts);
	
}
void Fruits::drawFruit(sf::RenderWindow &window)
{
	
	window.draw(appleSprite);

}
void Fruits::collision(std::vector<Player> &snakeVector, std::vector<Fruits> &fruitVector)
{
	if (snakeVector[0].playerBody.getGlobalBounds().intersects(appleSprite.getGlobalBounds()))
	{
		for (int i = 0; i < fruitVector.size(); i++)
		{
			fruitVector.erase(fruitVector.begin()+i);
			appleBite.play();
		}
	
	}



}
void Fruits::respawnCollision(std::vector<Player> &snakeVector,std::vector<Fruits> &fruitVector, TextItems &pointsText, TextItems &pointsValueText, sf::RenderWindow &window)
{
	
		if (appleSprite.getGlobalBounds().intersects(pointsValueText.textObject.getGlobalBounds()) || appleSprite.getGlobalBounds().intersects(pointsText.textObject.getGlobalBounds()))
		{
			appleSprite.setPosition(rand() % int(window.getSize().x - 0.1*window.getSize().x), rand() % int(window.getSize().y - 0.1*window.getSize().y));
		}
		for (int i = 1; i < snakeVector.size(); i++)
		{
			if (appleSprite.getGlobalBounds().intersects(snakeVector[i].playerBody.getGlobalBounds()))
				appleSprite.setPosition(rand() % int(window.getSize().x - 0.1*window.getSize().x), rand() % int(window.getSize().y - 0.1*window.getSize().y));
		}
	
}
