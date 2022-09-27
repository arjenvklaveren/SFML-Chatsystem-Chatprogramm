#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <string>

class TextBox: public sf::Drawable
{
public:
	TextBox(sf::Vector2f position);
	void Update(sf::RenderWindow& window);
	void AddText(std::string text);
private:
	sf::RectangleShape borderBox;
	sf::RectangleShape textRectBox;
	sf::Font mainFont;
	std::vector<sf::String> textRows;
	sf::Text fullBoxText;
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

