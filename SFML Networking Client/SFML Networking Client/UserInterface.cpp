#include "UserInterface.h"

UserInterface::UserInterface()
{
	testTextInput.SetSendAction([&]()
	{
		sf::Packet packet;
		packet << testTextInput.GetLastSendText();
		ConnectedSocket::SendPacket(packet);	
	});	
}

void UserInterface::UpdateAndDraw(sf::RenderWindow& window)
{
	//draw
	window.draw(testTextBox);
	window.draw(testTextInput);

	//update
	testTextInput.Update(window);
	testTextBox.Update(window);
}

void UserInterface::PacketUpdate(sf::Packet packet)
{
	std::string inString;
	packet >> inString;
	testTextBox.AddText(inString);
}

void UserInterface::GetTextUserInput(sf::Event& event)
{
	testTextInput.GetKeyBoardInput(event);
}