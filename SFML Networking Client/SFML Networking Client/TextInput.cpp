#include "TextInput.h"

TextInput::TextInput(sf::Vector2f position)
{
	if (!mainFont.loadFromFile("assets/myFont.ttf"))
		std::cout << "font not loaded" << std::endl;

	borderBox.setSize(sf::Vector2f(700, 50));
	textRectBox.setSize(sf::Vector2f(690, 40));
	borderBox.setPosition(position);
	textRectBox.setPosition(position + sf::Vector2f(5,5));
	borderBox.setFillColor(sf::Color(sf::Color::Black));
	textRectBox.setFillColor(sf::Color(sf::Color::White));

	inputText.setPosition(sf::Vector2f(position + sf::Vector2f(10, 6)));
	inputText.setFillColor(sf::Color::Black);	
	inputText.setFont(mainFont);
	inputText.setCharacterSize(30);
}


void TextInput::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(borderBox);
	target.draw(textRectBox);
	target.draw(inputText);
}

void TextInput::CheckClick(sf::RenderWindow& window)
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		if (canClick)
		{
			if (sf::Mouse::getPosition(window).x > this->textRectBox.getPosition().x && sf::Mouse::getPosition(window).x < this->textRectBox.getPosition().x + (textRectBox.getSize().x * this->textRectBox.getScale().x))
			{
				if (sf::Mouse::getPosition(window).y > this->textRectBox.getPosition().y && sf::Mouse::getPosition(window).y < this->textRectBox.getPosition().y + (textRectBox.getSize().y * this->textRectBox.getScale().y))
				{
					canClick = false;
					dashFlashString = "|";
					selected = true;
				}
				else
				{
					selected = false;
				}
			}
			else
			{
				selected = false;
			}
		}
	}
	if (!sf::Mouse::isButtonPressed(sf::Mouse::Left))
		canClick = true;
	{
	}
}

void TextInput::SetInputText()
{
	if (selected)
	{		
		inputText.setString(currentInput + dashFlashString);

		sf::Time time1 = clock.getElapsedTime();
			
		while (time1 >= sf::milliseconds(1000))
		{
			dashFlashString = "|";
			break;
		}
		while (time1 >= sf::milliseconds(2000))
		{
			dashFlashString = "";
			clock.restart();
			break;
		}
	}
	else
	{
		dashFlashString = "";
		inputText.setString(currentInput + dashFlashString);
	}
}

void TextInput::GetKeyBoardInput(sf::Event& event)
{
	if (selected)
	{
		if (event.text.unicode != 8 && !sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
		{
			currentInput += event.text.unicode;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::BackSpace))
		{
			if (currentInput.getSize() >= 1)
			{
				currentInput.erase(currentInput.getSize() - 1, 1);
			}
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
		{
			lastSendText = currentInput;
			onSendAction();
			currentInput.clear();
		}		
	}
}

std::string TextInput::GetLastSendText()
{
	return lastSendText;
}

void TextInput::SetSendAction(std::function<void()> action)
{
	onSendAction = action;
}

void TextInput::Update(sf::RenderWindow& window)
{
	CheckClick(window);	
	SetInputText();
}
