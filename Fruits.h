#pragma once
#include<SFML/Graphics.hpp>
#include<SFML/Audio.hpp>
#include <vector>
#include "Player.h"
#include "TextItems.h"

class Player;

class Fruits
{

	friend Player;

private:
	sf::RectangleShape fruitShape;
	sf::Vector2f fruitPosition;
	sf::Texture appleTexture;
	
	sf::Sound appleBite;
	sf::SoundBuffer appleBuffer;
public:
	Fruits();
	~Fruits();
	void randomPosition(sf::RenderWindow &, std::vector<Fruits>&,std::vector<Player>&, Fruits &, bool &, int &, std::string &, bool&);
	void drawFruit(sf::RenderWindow &);
	void collision(std::vector<Player> &, std::vector<Fruits> & );
	void respawnCollision(std::vector<Player> &,std::vector<Fruits> &, TextItems &, TextItems &, sf::RenderWindow &);

	sf::Sprite appleSprite;





};

