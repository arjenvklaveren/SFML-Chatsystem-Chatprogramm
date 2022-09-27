#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <functional>

class TextInput: public sf::Drawable
{
public:
	TextInput(sf::Vector2f position);
	void Update(sf::RenderWindow& window);
	void GetKeyBoardInput(sf::Event& event);
	void SetSendAction(std::function<void()> action);
	std::string GetLastSendText();
private:
	sf::RectangleShape textRectBox;
	sf::RectangleShape borderBox;
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	void CheckClick(sf::RenderWindow& window);
	void SetInputText();
	
	sf::Clock clock;

	sf::Font mainFont;

	sf::String currentInput = "";
	sf::String dashFlashString = "";
	sf::Text inputText;
	std::string lastSendText;

	int loopCount;
	
	bool canClick = true;
	bool selected = false;
	std::function<void()> onSendAction;
};

