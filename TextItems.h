#pragma once
#include<SFML/Graphics.hpp>
#include<SFML/Audio.hpp>



class TextItems
{
private:
	
	std::string text;
	sf::Font textFont;
	sf::Font brushFont;
	sf::Sound menuSound1;
	sf::SoundBuffer menuBuffer1;
	
	
	float windowHeight;
	float windowWidth;
	float textThickness;
	unsigned int startingPointsValue;
	unsigned int timerm1;
	unsigned int pulseTimerIncreasing;
	unsigned int pulseTimerDecreasing;
	unsigned int textSize;
	
	
	
public:
	bool soundToBePlayed;
	sf::Text textObject;
	void textDisplay(sf::RenderWindow & );
	TextItems(float height, float width);
	void setColor(TextItems &, int colorNumber);
	void setTextString(std::string buttonString, TextItems &);
	void setTextDesign(TextItems &, float textThickness, unsigned int charSize, unsigned int thicknessNumber);
	void setPointsString(std::string &, TextItems &);
	void menuTextDisplay(sf::RenderWindow &, bool&);
	void menuButtonPressed(TextItems &, sf::RenderWindow &, bool&, bool&, bool&, bool&, bool&, bool&, bool&, bool&);
	void textPulsation(TextItems &);
	~TextItems();

};

