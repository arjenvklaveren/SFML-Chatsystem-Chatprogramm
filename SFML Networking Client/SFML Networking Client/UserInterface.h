#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "ConnectedSocket.h"
#include "TextInput.h"
#include "TextBox.h"
#include "PacketObserver.h"

class UserInterface: public PacketObserver
{
public:
	UserInterface();
	void UpdateAndDraw(sf::RenderWindow& window);
	void GetTextUserInput(sf::Event& event);
private:
	TextInput testTextInput = TextInput(sf::Vector2f(50, 700));
	TextBox testTextBox = TextBox(sf::Vector2f(50, 50));
	void PacketUpdate(sf::Packet packet) override;
};

