#include <SFML/Graphics.hpp>
#include <iostream>
#include "ConnectedSocket.h"
#include "UserInterface.h"

int main()
{    
    ConnectedSocket::ConnectToServer();
    UserInterface UI = UserInterface();
    ConnectedSocket::RegisterPacketObserver(UI);

    sf::RenderWindow window(sf::VideoMode(800, 800), "SFML works!", sf::Style::Close);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::TextEntered)
            {
                UI.GetTextUserInput(event);
            }
        }

        window.clear(sf::Color(sf::Color::Blue));

        ConnectedSocket::ReceivePackets();
        UI.UpdateAndDraw(window);     

        window.display();
    }

    return 0;
}
