#include "LevelEditor.h"
#include "Player.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <Windows.h>
#include "Fruits.h"



LevelEditor::LevelEditor()
{
	isGameOver = false;
	failBuffer.loadFromFile("fail.wav");
	failSound.setBuffer(failBuffer);

	mainTheme.openFromFile("main.wav");
	mainTheme.setLoop(true);
	mainTheme.setVolume(25);
	mainTheme.play();
}


LevelEditor::~LevelEditor()
{
}

void LevelEditor::nextLevelCommunicate(sf::RenderWindow &window,int ptsMax, int &pts, bool &isLvlChanged, std::vector<Player> &playerVector)
{
	if (pts == ptsMax )
	{
		playerVector.clear();
		
		isLvlChanged = true;
		
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space) && isLvlChanged == true)
	{
		window.clear(sf::Color::Black);
		
		isLvlChanged = false;
		pts = ptsMax+1;
		
	}
	
}
void LevelEditor:: levelChange(sf::RenderWindow &window, unsigned int&lvl, int&pts, bool &isLvlChanged, std::vector<Player> &playerVector)
{
	
	
	
	
	
	//POINTS FOR LEVELS AND RESETING LEVELS
	if (pts <= 10)
	{
	
		nextLevelCommunicate(window,10, pts, isLvlChanged, playerVector);
		lvl = 1;
		
	}
	else if (pts > 10 && pts <= 20)
	{
		
		nextLevelCommunicate(window, 20, pts, isLvlChanged, playerVector);
		lvl = 2;
		
	}
	else if (pts > 20 && pts <= 35)
	{
		
		nextLevelCommunicate(window, 35, pts, isLvlChanged, playerVector);
		lvl = 3;
	}
	else if (pts > 35 && pts <= 55)
	{
		
		nextLevelCommunicate(window, 55, pts, isLvlChanged, playerVector);
		lvl = 4;
	}
	else if (pts > 55 && pts <= 85)
	{
		
		nextLevelCommunicate(window,85, pts, isLvlChanged, playerVector);
		lvl = 5;
	}
	else if (pts > 85 && pts <= 120)
	{
		
		nextLevelCommunicate(window, 120, pts, isLvlChanged, playerVector);
		lvl = 6;
	}
	else if (pts > 120 && pts <= 160)
	{
		
		nextLevelCommunicate(window, 160, pts, isLvlChanged, playerVector);
		lvl = 7;
	}
	else if (pts > 160 && pts <= 200)
	{
		
		nextLevelCommunicate(window, 200, pts, isLvlChanged, playerVector);
		lvl = 8;
	}
	else if (pts > 200 && pts < 300)
	{
		
		nextLevelCommunicate(window, 300, pts, isLvlChanged, playerVector);
		lvl = 9;
	}
	else if (pts > 300)
	{
		lvl = 10;
	}
	
	
}
void LevelEditor::barrierSnakeCollision( sf::RenderWindow &window, sf::RectangleShape barrier[],int count, std::vector<Player> &snakeVector, bool&playerAlive)//MULTIBARRIER LEVELS
{
	if (snakeVector.empty() == false)
	{
		for (int i = 0; i < count; i++)
		{
			if (snakeVector[0].playerBody.getGlobalBounds().intersects(barrier[i].getGlobalBounds()))
			{
	
				playerAlive = false;
			

			}
		}
	}

}
void LevelEditor::barrierSnakeCollision(sf::RenderWindow &window, sf::RectangleShape barrier, std::vector<Player> &snakeVector, bool&playerAlive)//OVERLOADED - SINGLE BARRIER LV1
{
	if (snakeVector.empty() == false)
	{
			if (snakeVector[0].playerBody.getGlobalBounds().intersects(barrier.getGlobalBounds()))
			{
				playerAlive = false;

			}
		
	}

}
void LevelEditor::barrierRespCollision(sf::RenderWindow &window, sf::RectangleShape barrier, Fruits &fobj )//OVERLOADED
{
	
			
	if (fobj.appleSprite.getGlobalBounds().intersects(barrier.getGlobalBounds()))
	{
		fobj.appleSprite.setPosition(rand() % int(window.getSize().x - 0.1*window.getSize().x), rand() % int(window.getSize().y - 0.1*window.getSize().y));
		
	}
			
		
	
}
void LevelEditor::barrierRespCollision(sf::RenderWindow &window, sf::RectangleShape barrier[], int count, Fruits &fobj)//OVERLOADED
{
	for (int i = 0; i < count; i++)
	{

		if (fobj.appleSprite.getGlobalBounds().intersects(barrier[i].getGlobalBounds()))
		{
			fobj.appleSprite.setPosition(rand() % int(window.getSize().x - 0.1*window.getSize().x), rand() % int(window.getSize().y - 0.1*window.getSize().y));
			std::cout << "buch" << std::endl;
		}

	}


}



void LevelEditor::drawBarrier(sf::RenderWindow &window, unsigned int &level, std::vector<Player> &snakeVector,std::vector<Fruits> &fruitVect, Fruits &fruitObject, bool &playerAlive)
{
	sf::RectangleShape rect;
	sf::RectangleShape rectArray[4];
	sf::RectangleShape outlines[4];
	sf::RectangleShape squares4Array[5];
	sf::RectangleShape line3Array[11];
	sf::RectangleShape line6Array[10];
	sf::RectangleShape lines7Array[4];

	switch (level)
	{
		
	case 1://LEVEL1
	{
		
		rect.setSize(sf::Vector2f(440, 40));
		rect.setFillColor(sf::Color::Yellow);
		rect.setPosition(window.getSize().x / 2 - 210, window.getSize().y / 2 - 10);

		window.draw(rect);

		barrierSnakeCollision(window, rect, snakeVector, playerAlive);
		barrierRespCollision(window, rect, fruitObject);

	}break;
	
	case 2://LEVEL2
	{
		
		for (int i = 0; i < 4; i++)
		{
			rectArray[i].setSize(sf::Vector2f(100, 100));
			rectArray[i].setFillColor(sf::Color::Blue);
			if (i <= 1)
				rectArray[i].setPosition(110, 100 + i * 600);
			else if (i == 2)
				rectArray[i].setPosition(1110, 700);
			else
				rectArray[i].setPosition(1110, 100);
			
			window.draw(rectArray[i]);
			
		}
		barrierRespCollision(window, rectArray,4,fruitObject);
		barrierSnakeCollision(window, rectArray,4, snakeVector, playerAlive);
		
	}break;
	case 3://LEVEL 3
	{
		
		
		for (int i = 0; i < 11; i++)
		{
			if (i>=0&&i<=1)
			{
				line3Array[i].setSize(sf::Vector2f(360, 20));
				line3Array[i].rotate(90);
				line3Array[i].setPosition(330 + i * 700, 200);
			}
			else if (i >= 2 && i <= 3)
			{
				line3Array[i].setSize(sf::Vector2f(280, 20));

				line3Array[2].setPosition(line3Array[0].getPosition().x-line3Array[0].getSize().y,180);
				line3Array[3].setPosition(line3Array[1].getPosition().x -line3Array[1].getSize().x+80, 180);

			}
			else if (i>=4 && i <= 5)
			{
				line3Array[i].setSize(sf::Vector2f(120, 20));
				line3Array[i].rotate(90);
				line3Array[4].setPosition(line3Array[0].getPosition().x + 260, 180);
				line3Array[5].setPosition(line3Array[0].getPosition().x + 440, 180);
				//line3Array[5].setPosition(line3Array[1].getPosition().x - line3Array[1].getSize().x + 80, 180);
			}
			else if (i >= 6 && i <= 7)
			{
				line3Array[i].setSize(sf::Vector2f(280, 20));

				line3Array[6].setPosition(line3Array[0].getPosition().x - line3Array[0].getSize().y, 560);
				line3Array[7].setPosition(line3Array[6].getPosition().x + 440, 560);

			}
			else if (i >= 8 && i <= 9)
			{
				line3Array[i].setSize(sf::Vector2f(120, 20));
				line3Array[i].rotate(90);
				line3Array[8].setPosition(line3Array[4].getPosition().x , 460);
				line3Array[9].setPosition(line3Array[5].getPosition().x , 460);
				//line3Array[5].setPosition(line3Array[1].getPosition().x - line3Array[1].getSize().x + 80, 180);
			}
			else if (i == 10)
			{
				line3Array[i].setSize(sf::Vector2f(200, 20));
				

				line3Array[i].setPosition(line3Array[4].getPosition().x-20, 300);

			}
			line3Array[i].setFillColor(sf::Color::Blue);
			window.draw(line3Array[i]);
		}
		barrierRespCollision(window, line3Array, 11, fruitObject);
		barrierSnakeCollision(window, line3Array, 11, snakeVector, playerAlive);
		
	}break;
	case 4://LEVEL4
	{
		
		
		for (int i = 0; i < 5; i++)
		{
			squares4Array[i].setSize(sf::Vector2f(140, 140));
			squares4Array[i].setFillColor(sf::Color::Yellow);

			if (i >= 0 && i <= 1)
			{
				squares4Array[i].setPosition(430 + i * 280, 200);
			}
			if (i >= 2 && i <= 3)
			{
				squares4Array[2].setPosition(430 , 480);
				squares4Array[3].setPosition(squares4Array[1].getPosition().x, 480);
			}
			if (i == 4)
			{
				squares4Array[4].setPosition(squares4Array[0].getPosition().x+squares4Array[0].getSize().x, 340);
				
			}

			window.draw(squares4Array[i]);

		}
		barrierRespCollision(window, squares4Array, 5, fruitObject);
		barrierSnakeCollision(window, squares4Array, 5, snakeVector, playerAlive);
	}break;

	case 5://LEVEL5
	{
		
		for (int i = 0; i < 4; i++)
		{
			rectArray[i].setSize(sf::Vector2f(100, 100));
			rectArray[i].setFillColor(sf::Color::Blue);
			if (i <= 1)
				rectArray[i].setPosition(110, 100 + i * 600);
			else if (i == 2)
				rectArray[i].setPosition(1110, 700);
			else
				rectArray[i].setPosition(1110, 100);
			window.draw(rectArray[i]);
		}
		
		for (int i = 0; i < 11; i++)
		{
			if (i >= 0 && i <= 1)
			{
				line3Array[i].setSize(sf::Vector2f(360, 20));
				line3Array[i].rotate(90);
				line3Array[i].setPosition(330 + i * 700, 200);
			}
			else if (i >= 2 && i <= 3)
			{
				line3Array[i].setSize(sf::Vector2f(280, 20));

				line3Array[2].setPosition(line3Array[0].getPosition().x - line3Array[0].getSize().y, 180);
				line3Array[3].setPosition(line3Array[1].getPosition().x - line3Array[1].getSize().x + 80, 180);

			}
			else if (i >= 4 && i <= 5)
			{
				line3Array[i].setSize(sf::Vector2f(120, 20));
				line3Array[i].rotate(90);
				line3Array[4].setPosition(line3Array[0].getPosition().x + 260, 180);
				line3Array[5].setPosition(line3Array[0].getPosition().x + 440, 180);
				//line3Array[5].setPosition(line3Array[1].getPosition().x - line3Array[1].getSize().x + 80, 180);
			}
			else if (i >= 6 && i <= 7)
			{
				line3Array[i].setSize(sf::Vector2f(280, 20));

				line3Array[6].setPosition(line3Array[0].getPosition().x - line3Array[0].getSize().y, 560);
				line3Array[7].setPosition(line3Array[6].getPosition().x + 440, 560);

			}
			else if (i >= 8 && i <= 9)
			{
				line3Array[i].setSize(sf::Vector2f(120, 20));
				line3Array[i].rotate(90);
				line3Array[8].setPosition(line3Array[4].getPosition().x, 460);
				line3Array[9].setPosition(line3Array[5].getPosition().x, 460);
				//line3Array[5].setPosition(line3Array[1].getPosition().x - line3Array[1].getSize().x + 80, 180);
			}
			else if (i == 10)
			{
				line3Array[i].setSize(sf::Vector2f(200, 20));


				line3Array[i].setPosition(line3Array[4].getPosition().x - 20, 300);

			}
			line3Array[i].setFillColor(sf::Color::Blue);
			window.draw(line3Array[i]);
		}
		barrierRespCollision(window, rectArray, 4, fruitObject);
		barrierRespCollision(window, line3Array, 11, fruitObject);
		barrierSnakeCollision(window, line3Array, 11, snakeVector, playerAlive);
		barrierSnakeCollision(window, rectArray, 4, snakeVector, playerAlive);

	}break;
	case 6://LEVEL 6
	{
		
		
		for (int i = 0; i < 10; i++)
		{
			line6Array[i].setFillColor(sf::Color::Yellow);
			
			if (i >= 0 && i <= 1)
			{
				line6Array[i].setSize(sf::Vector2f(540, 20));
				line6Array[i].rotate(90);
				line6Array[i].setPosition(130 + i * 1120, 100);


			}
			else if (i >= 2 && i <= 3)
			{
				line6Array[i].setSize(sf::Vector2f(840, 20));
	
				line6Array[2].setPosition(250, 40);
				line6Array[3].setPosition(250, 680);

			}
			else if (i >= 4 && i <= 5)
			{
				line6Array[i].setSize(sf::Vector2f(720, 20));
				
				line6Array[4].setPosition(310, 140);
				line6Array[5].setPosition(310, 580);

			}
			else if (i >= 6 && i <= 7)
			{
				line6Array[i].setSize(sf::Vector2f(340, 20));
				line6Array[i].rotate(90);
				line6Array[6].setPosition(470, 200);
				line6Array[7].setPosition(910, 200);

			}
			else if (i ==8)
			{
				line6Array[8].setSize(sf::Vector2f(420, 20));
				
				line6Array[8].setPosition(470, 200);
				

			}
			else if (i == 9)
			{
				line6Array[9].setSize(sf::Vector2f(100, 100));

				line6Array[9].setPosition(630, 320);


			}

			window.draw(line6Array[i]);
		}
		barrierRespCollision(window, line6Array, 10, fruitObject);
		barrierSnakeCollision(window, line6Array, 10, snakeVector, playerAlive);

	}break;
	case 7://LEVEL 7
	{

		
		for (int i = 0; i < 5; i++)
		{
			squares4Array[i].setSize(sf::Vector2f(140, 140));
			squares4Array[i].setFillColor(sf::Color::Blue);

			if (i >= 0 && i <= 1)
			{
				squares4Array[i].setPosition(430 + i * 280, 200);
			}
			if (i >= 2 && i <= 3)
			{
				squares4Array[2].setPosition(430, 480);
				squares4Array[3].setPosition(squares4Array[1].getPosition().x, 480);
			}
			if (i == 4)
			{
				squares4Array[4].setPosition(squares4Array[0].getPosition().x + squares4Array[0].getSize().x, 340);

			}

			window.draw(squares4Array[i]);

		}
		
		for (int i = 0; i < 4; i++)
		{
			rectArray[i].setSize(sf::Vector2f(100, 100));
			rectArray[i].setFillColor(sf::Color::Magenta);
			if (i <= 1)
				rectArray[i].setPosition(110, 100 + i * 600);
			else if (i == 2)
				rectArray[i].setPosition(1110, 700);
			else
				rectArray[i].setPosition(1110, 100);
			window.draw(rectArray[i]);
		}
		
		for (int i = 0; i < 4; i++)
		{
			lines7Array[i].setSize(sf::Vector2f(340, 20));
			lines7Array[i].setFillColor(sf::Color::Yellow);

			if (i >= 0 && i <= 1)
			{
				lines7Array[i].setPosition(170+i*1000, 280);
				lines7Array[i].rotate(90);
			}
			else if (i >= 2 && i <= 3)
			{
				lines7Array[2].setPosition(470,140);
				lines7Array[3].setPosition(470, 700);
			}


			window.draw(lines7Array[i]);
		}
		barrierRespCollision(window, rectArray, 4, fruitObject);
		barrierRespCollision(window, squares4Array, 5, fruitObject);
		barrierRespCollision(window, lines7Array, 4, fruitObject);

		barrierSnakeCollision(window, squares4Array, 5, snakeVector, playerAlive);
		barrierSnakeCollision(window, rectArray, 4, snakeVector, playerAlive);
		barrierSnakeCollision(window, lines7Array, 4, snakeVector, playerAlive);
	}break;

	case 8://LEVEL8
	{
		
		
		for (int i = 0; i < 4; i++)
		{
			outlines[i].setFillColor(sf::Color::Red);
			
			if (i == 0 )
			{
				outlines[i].setSize(sf::Vector2f(740, 15));
				outlines[i].rotate(90);
				outlines[i].setPosition(110+i*1180, 60);
			}
			if (i == 1)
			{
				outlines[i].setSize(sf::Vector2f(740, 20));
				outlines[i].rotate(90);
				outlines[i].setPosition(110 + i * 1180, 60);
			}
			else if (i >= 2 && i <= 3)
			{
				outlines[2].setSize(sf::Vector2f(1170, 20));
				outlines[3].setSize(sf::Vector2f(1070, 20));
				outlines[2].setPosition(100, 60);
				outlines[3].setPosition(100, 780);
			}

			window.draw(outlines[i]);

		}

		barrierRespCollision(window, outlines, 4, fruitObject);
		barrierSnakeCollision(window, outlines, 4, snakeVector, playerAlive);


	}break;
	case 9://LEVEL 9
	{
		

		for (int i = 0; i < 4; i++)
		{
			outlines[i].setFillColor(sf::Color::Blue);

			if (i >= 0 && i <= 1)
			{
				outlines[i].setSize(sf::Vector2f(740, 20));
				outlines[i].rotate(90);
				outlines[i].setPosition(110 + i * 1180, 60);
			}
			else if (i >= 2 && i <= 3)
			{
				outlines[2].setSize(sf::Vector2f(1170, 20));
				outlines[3].setSize(sf::Vector2f(1070, 20));
				outlines[2].setPosition(100, 60);
				outlines[3].setPosition(100, 780);
			}

			window.draw(outlines[i]);
		}
		
		for (int i = 0; i < 11; i++)
		{
			if (i >= 0 && i <= 1)
			{
				line3Array[i].setSize(sf::Vector2f(360, 20));
				line3Array[i].rotate(90);
				line3Array[i].setPosition(330 + i * 700, 200);
			}
			else if (i >= 2 && i <= 3)
			{
				line3Array[i].setSize(sf::Vector2f(280, 20));

				line3Array[2].setPosition(line3Array[0].getPosition().x - line3Array[0].getSize().y, 180);
				line3Array[3].setPosition(line3Array[1].getPosition().x - line3Array[1].getSize().x + 80, 180);

			}
			else if (i >= 4 && i <= 5)
			{
				line3Array[i].setSize(sf::Vector2f(120, 20));
				line3Array[i].rotate(90);
				line3Array[4].setPosition(line3Array[0].getPosition().x + 260, 180);
				line3Array[5].setPosition(line3Array[0].getPosition().x + 440, 180);
				//line3Array[5].setPosition(line3Array[1].getPosition().x - line3Array[1].getSize().x + 80, 180);
			}
			else if (i >= 6 && i <= 7)
			{
				line3Array[i].setSize(sf::Vector2f(280, 20));

				line3Array[6].setPosition(line3Array[0].getPosition().x - line3Array[0].getSize().y, 560);
				line3Array[7].setPosition(line3Array[6].getPosition().x + 440, 560);

			}
			else if (i >= 8 && i <= 9)
			{
				line3Array[i].setSize(sf::Vector2f(120, 20));
				line3Array[i].rotate(90);
				line3Array[8].setPosition(line3Array[4].getPosition().x, 460);
				line3Array[9].setPosition(line3Array[5].getPosition().x, 460);
				
			}
			else if (i == 10)
			{
				line3Array[i].setSize(sf::Vector2f(200, 20));


				line3Array[i].setPosition(line3Array[4].getPosition().x - 20, 300);

			}
			line3Array[i].setFillColor(sf::Color::Yellow);
			window.draw(line3Array[i]);
		}
		barrierRespCollision(window, line3Array, 11, fruitObject);
		barrierRespCollision(window, outlines, 4, fruitObject);

		barrierSnakeCollision(window, line3Array, 11, snakeVector, playerAlive);
		barrierSnakeCollision(window, outlines, 4, snakeVector, playerAlive);
	}break;

	}
	
}
	


void LevelEditor::gameReset(sf::RenderWindow &window,bool &gameAct, bool &playerAlive,bool &menuAct, std::vector<Player> &playerVector , int &ptValue, TextItems &ptsValueItem, unsigned int &lv, bool &diffDisplayed, bool &easyChosen, bool &mediumChosen, bool &hardChosen)
{
	
	if (playerAlive == false && sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape))
	{
		gameAct = false;
		menuAct = true;
		diffDisplayed = false;
		easyChosen = false;
		mediumChosen = false;
		hardChosen = false;
		ptValue = 0;
		std::string newVal;
		newVal = std::to_string(ptValue);
		ptsValueItem.textObject.setString("0");
		playerVector.clear();
		
		playerAlive = true;
	

	}
	else if (!playerAlive)
	{

		if (isGameOver == false)
		{
			failSound.play();
			isGameOver = true;
		}
	}
	if (menuAct == true)
		isGameOver = false;
	

}