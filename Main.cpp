#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Fruits.h"
#include "TextItems.h"
#include <iostream>
#include "LevelEditor.h"

int main()
{
	//WINDOW 
	sf::RenderWindow window(sf::VideoMode(1360, 780), "Snake!", sf::Style::None);
	window.setFramerateLimit(60);
	sf::Event evnt;
	//RANDOMIZING
	srand(time(NULL));//START RANDOMIZING
	//GLOBAL BOOLEANS TO CONTROL GAME EVENTS
	bool isPressed = false;
	bool isMenuActive = true;
	bool informationDisplayed = false;
	bool difficultyDisplayed = false;
	bool isEasyChosen = false;
	bool isMediumChosen = false;
	bool isHardChosen = false;
	bool isLevelCompleted = false;
	bool gameActive = false;
	bool snakeAlive = true;
	
	
	//COORDINATES ARRAYS-DYNAMIC FOR SNAKE UPDATE
	int* xArray = new int[400];
	int* yArray = new int [400];
	//LEVEL
	unsigned int actualLevel = 1;
	//OBJECTS
	//PLAYER AND APPLE OBJECTS
	Player snake(window);
	Fruits apple;
	//LEVEL OBJECTS
	LevelEditor gameControl;
	
	//TEXT OBJECTS
	TextItems Points(window.getSize().x-window.getSize().x*0.99,0);
	TextItems pointsValue(window.getSize().x - window.getSize().x*0.88, 0);
	TextItems menuButtonStart(window.getSize().x / 2-130, window.getSize().y / 2-200);
	TextItems menuButtonAbout(window.getSize().x / 2 - 80, window.getSize().y / 2 - 100);
	TextItems menuButtonExit(window.getSize().x / 2 - 60, window.getSize().y / 2);
	TextItems menuInfo1(window.getSize().x / 2 -400, window.getSize().y / 2 -250);
	TextItems menuInfo2(window.getSize().x / 2 - 300, window.getSize().y - 80);
	TextItems backButton(window.getSize().x / 2 -90, window.getSize().y - 280);
	TextItems gameOver(window.getSize().x / 2-270, window.getSize().y / 2);
	TextItems continueButton(window.getSize().x / 2 - 200, window.getSize().y / 2 );
	TextItems levelCompleted(window.getSize().x/2-200, window.getSize().y / 2-200);
	TextItems easyButton(window.getSize().x / 2 - 400, window.getSize().y / 2 - 100);
	TextItems mediumButton(window.getSize().x / 2 - 100, window.getSize().y / 2 - 100);
	TextItems hardButton(window.getSize().x / 2 +250, window.getSize().y / 2 -100);
		
	//POINTS STRING
	std::string pointsStartStr;
	int ptsVal =0;
	pointsStartStr=std::to_string(ptsVal);
	//POINTERS
	//APPLE AND SNAKE POINTERS
	Player *snakePtr=&snake;
	Fruits *fruitPtr=&apple;
	//TEXT POINTERS
	TextItems *textPtr1 = &Points;
	TextItems *textPtr2 = &pointsValue;
	TextItems *textPtrStart = &menuButtonStart;
	TextItems *textPtrAbout = &menuButtonAbout;
	TextItems *textPtrExit = &menuButtonExit;
	TextItems *textPtrInfo1 = &menuInfo1;
	TextItems *textPtrInfo2 = &menuInfo2;
	TextItems *textPtrBack = &backButton;
	TextItems *textPtrOver = &gameOver;
	TextItems *textPtrLvl = &levelCompleted;
	TextItems *textPtrContinue = &continueButton;
	TextItems *textPtrEasy = &easyButton;
	TextItems *textPtrMedium = &mediumButton;
	TextItems *textPtrHard = &hardButton;
	//LEVEL POINTERS
	LevelEditor *managerPtr = &gameControl;
	//CONTAINERS 
	std::vector<Fruits> fruitVector;
	fruitVector.push_back(apple);
	std::vector<Player> playerBodyVector;
	//GAME LOOP
	while (window.isOpen())
	{
		while (window.pollEvent(evnt))
		{
			if (evnt.type == sf::Event::Closed)
			{
				window.close();
			}
			
		}
		//CLEARING A WINDOW
		window.clear(sf::Color::Black);
		
		//LEVEL AND GAME RESET 
		managerPtr->gameReset(window, gameActive, snakeAlive, isMenuActive, playerBodyVector, ptsVal, pointsValue, actualLevel, difficultyDisplayed, isEasyChosen, isMediumChosen, isHardChosen);
		managerPtr->levelChange(window, actualLevel, ptsVal, isLevelCompleted, playerBodyVector);
		
		

		if (!isMenuActive)
		{
		//PLAYER INTERACTIONS
			
			snakePtr->acrossTheWall(window, playerBodyVector);
			snakePtr->bodyUpdate(window, isPressed, fruitVector, playerBodyVector, snakePtr, xArray, yArray, snakeAlive);
			snakePtr->snakeMove(window, isPressed, snake, playerBodyVector, snakeAlive, isLevelCompleted, isEasyChosen, isMediumChosen, isHardChosen);
			snakePtr->selfCollision(playerBodyVector, snakeAlive);
			snakePtr->setHeadPosition(window, actualLevel);
			 
			
		
		//FRUITS INTERACTIONS
			fruitPtr->randomPosition(window, fruitVector, playerBodyVector, apple, isPressed, ptsVal, pointsStartStr, snakeAlive);
			fruitPtr->collision(playerBodyVector, fruitVector);
			fruitPtr->respawnCollision(playerBodyVector, fruitVector, Points, pointsValue, window);
			fruitPtr->drawFruit(window);
		//BARRIERS 
			managerPtr->drawBarrier(window, actualLevel, playerBodyVector, fruitVector, apple, snakeAlive);
		
		
		//IF MENU IS NOT ACTIVE DRAW THE TEXT
			textPtr1->setColor(Points, 2);
			textPtr1->setTextString("POINTS: ", Points);
			textPtr1->setTextDesign(Points, 5, 40, 1);
			textPtr1->textDisplay(window);

			textPtr2->setColor(pointsValue, 1);
			textPtr2->setPointsString(pointsStartStr, pointsValue);
			textPtr2->setTextDesign(pointsValue, 0, 40, 0);
			textPtr2->textDisplay(window);
			if (!snakeAlive)//IN CASE OF SNAKE DEATH
			{
				textPtrOver->setColor(gameOver, 2);
				textPtrOver->setTextString("GAME OVER! Press escape.", gameOver);
				textPtrOver->setTextDesign(gameOver, 5, 50, 1);
				textPtrOver->textDisplay(window);
			}
		
			
	
		}
	//INFO ABOUT COMPLETED LEVEL
	if (isLevelCompleted == true)
	{
		window.clear(sf::Color::Black);
		textPtrLvl->setColor(levelCompleted, 2);
		textPtrLvl->setTextString("LEVEL COMPLETED!", levelCompleted);
		textPtrLvl->setTextDesign(levelCompleted, 5, 65, 1);
		textPtrLvl->textDisplay(window);

		textPtrContinue->setColor(continueButton, 2);
		textPtrContinue->setTextString("PRESS SPACE TO CONTINUE....", continueButton);
		textPtrContinue->setTextDesign(continueButton, 5, 55, 1);
		textPtrContinue->textPulsation(continueButton);
		textPtrContinue->textDisplay(window);

		
	}


		//MAIN MENU
		if (!informationDisplayed&&!gameActive && !difficultyDisplayed)
		{
			//START BUTTON
			textPtrStart->setColor(menuButtonStart, 2);
			textPtrStart->setTextString("START GAME", menuButtonStart);
			textPtrStart->setTextDesign(menuButtonStart, 5, 55, 1);
			textPtrStart->menuButtonPressed(menuButtonStart, window, isMenuActive, informationDisplayed, gameActive, isLevelCompleted, difficultyDisplayed, isEasyChosen, isMediumChosen, isHardChosen);
			textPtrStart->menuTextDisplay(window, isMenuActive);
			//ABOUT BUTTON AND MENU INFO
			textPtrAbout->setColor(menuButtonAbout, 2);
			textPtrAbout->setTextString("ABOUT", menuButtonAbout);
			textPtrAbout->setTextDesign(menuButtonAbout, 5, 55, 1);
			textPtrAbout->menuButtonPressed(menuButtonAbout, window, isMenuActive, informationDisplayed, gameActive, isLevelCompleted, difficultyDisplayed, isEasyChosen, isMediumChosen, isHardChosen);
			textPtrAbout->menuTextDisplay(window, isMenuActive);

			//EXIT BUTTON 
			textPtrExit->setColor(menuButtonExit, 2);
			textPtrExit->setTextString("EXIT", menuButtonExit);
			textPtrExit->setTextDesign(menuButtonExit, 5, 55, 1);
			textPtrExit->menuButtonPressed(menuButtonExit, window, isMenuActive, informationDisplayed, gameActive, isLevelCompleted, difficultyDisplayed,isEasyChosen, isMediumChosen, isHardChosen);
			textPtrExit->menuTextDisplay(window, isMenuActive);


		}
		//DIFFICULTY MENU
		if (difficultyDisplayed &&!gameActive)
		{
			textPtrEasy->setColor(easyButton, 2);
			textPtrEasy->setTextString("EASY", easyButton);
			textPtrEasy->setTextDesign(easyButton, 5, 55, 1);
			textPtrEasy->menuButtonPressed(easyButton, window, isMenuActive, informationDisplayed, gameActive, isLevelCompleted, difficultyDisplayed, isEasyChosen, isMediumChosen, isHardChosen);
			textPtrEasy->textDisplay(window);

			textPtrMedium->setColor(mediumButton, 2);
			textPtrMedium->setTextString("MEDIUM", mediumButton);
			textPtrMedium->setTextDesign(mediumButton, 5, 55, 1);
			textPtrMedium->menuButtonPressed(mediumButton, window, isMenuActive, informationDisplayed, gameActive, isLevelCompleted, difficultyDisplayed, isEasyChosen, isMediumChosen, isHardChosen);
			textPtrMedium->textDisplay(window);

			textPtrHard->setColor(hardButton, 2);
			textPtrHard->setTextString("HARD", hardButton);
			textPtrHard->setTextDesign(hardButton, 5, 55, 1);
			textPtrHard->menuButtonPressed(hardButton, window, isMenuActive, informationDisplayed, gameActive, isLevelCompleted, difficultyDisplayed, isEasyChosen, isMediumChosen, isHardChosen);
			textPtrHard->textDisplay(window);
			snakePtr->speedSetup(window, isEasyChosen, isMediumChosen, isHardChosen);
			
		}

		if (informationDisplayed&&!gameActive )//IF INFO IS DISPLAYED BY USER
		{
			//INFO
			textPtrInfo1->setColor(menuInfo1, 2);
			textPtrInfo1->setTextString("               Welcome to the Arcade Snake Game! \n\n\nCollect the fruits, make your snake bigger and bigger\n       and try to avoid obstacles and barriers.\n          Use 'WASD' keys to control the snake.\n\n\n                                   ENJOY!", menuInfo1);
			textPtrInfo1->setTextDesign(menuInfo1, 3, 35, 1);
			textPtrInfo1->menuButtonPressed(menuInfo1, window, isMenuActive, informationDisplayed, gameActive, isLevelCompleted, difficultyDisplayed, isEasyChosen, isMediumChosen, isHardChosen);
			textPtrInfo1->menuTextDisplay(window, isMenuActive);

			textPtrInfo2->setColor(menuInfo2, 2);
			textPtrInfo2->setTextString("Created by Lukasz Walocha 2017. All rights reserved", menuInfo2);
			textPtrInfo2->setTextDesign(menuInfo2, 3, 25, 1);
			textPtrInfo2->menuTextDisplay(window, isMenuActive);
			//BACK BUTTON
			textPtrBack->setColor(backButton, 2);
			textPtrBack->setTextString("BACK", backButton);
			textPtrBack->setTextDesign(backButton, 3, 55, 1);
			textPtrBack->menuButtonPressed(backButton, window, isMenuActive, informationDisplayed, gameActive, isLevelCompleted, difficultyDisplayed, isEasyChosen, isMediumChosen, isHardChosen);
			textPtrBack->menuTextDisplay(window, isMenuActive);


		}
		//CREDIT INFO
		   textPtrInfo2->setColor(menuInfo2, 2);
		   textPtrInfo2->setTextString("Created by Lukasz Walocha 2017. All rights reserved", menuInfo2);
		   textPtrInfo2->setTextDesign(menuInfo2, 3, 25, 1);
		   textPtrInfo2->menuTextDisplay(window, isMenuActive);
		
		
		window.display();
	}
	delete[] xArray;
	delete[] yArray;
	return 0;
}