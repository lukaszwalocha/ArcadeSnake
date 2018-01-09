#pragma once
#include "Player.h"
#include "TextItems.h"
#include "Fruits.h"
#include <vector>
class LevelEditor : public Fruits, public Player
{
private:
	sf::Sound failSound;
	sf::SoundBuffer failBuffer;
	bool isGameOver;

	sf::Music mainTheme;
	

public:
	LevelEditor();
	~LevelEditor();
	void gameReset(sf::RenderWindow &,bool&, bool&, bool&, std::vector<Player> & ,int &, TextItems &, unsigned int &, bool&, bool&, bool&, bool&);
	void drawBarrier(sf::RenderWindow &, unsigned int &, std::vector<Player> &, std::vector<Fruits> &, Fruits &, bool &);
	void levelChange(sf::RenderWindow &, unsigned int&, int&, bool&, std::vector<Player> &);
	void nextLevelCommunicate(sf::RenderWindow &,int ptsMax, int &, bool &, std::vector<Player> &);
	void barrierSnakeCollision(sf::RenderWindow &, sf::RectangleShape barrier[], int count, std::vector<Player> &, bool&);
	void barrierSnakeCollision(sf::RenderWindow &, sf::RectangleShape barrier, std::vector<Player> &, bool&);
	void barrierRespCollision(sf::RenderWindow &, sf::RectangleShape barrier, Fruits &);
	void barrierRespCollision(sf::RenderWindow &, sf::RectangleShape barrier[], int count, Fruits &);
	
};

