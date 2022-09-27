#include "TextBox.h"

TextBox::TextBox(sf::Vector2f position)
{
	if (!mainFont.loadFromFile("assets/myFont.ttf"))
		std::cout << "font not loaded" << std::endl;

	borderBox.setSize(sf::Vector2f(700, 600));
	textRectBox.setSize(sf::Vector2f(690, 590));
	borderBox.setPosition(position);
	textRectBox.setPosition(position + sf::Vector2f(5, 5));
	borderBox.setFillColor(sf::Color(sf::Color::Black));
	textRectBox.setFillColor(sf::Color(sf::Color::White));

	fullBoxText.setPosition(sf::Vector2f(position + sf::Vector2f(10, 6)));
	fullBoxText.setFillColor(sf::Color::Black);
	fullBoxText.setFont(mainFont);
	fullBoxText.setCharacterSize(30);
}

void TextBox::AddText(std::string text)
{
	textRows.push_back(text);
	if(textRows.size() > 15) textRows.erase(textRows.begin());
	std::string fullBoxTextString;
	for (std::string txt : textRows)
	{
		fullBoxTextString += txt;
		fullBoxTextString += "\n";
	}
	fullBoxText.setString(fullBoxTextString);
}

void TextBox::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(borderBox);
	target.draw(textRectBox);
	target.draw(fullBoxText);
}

void TextBox::Update(sf::RenderWindow& window)
{

}