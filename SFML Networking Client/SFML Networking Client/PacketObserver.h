#pragma once
#include <SFML/Network.hpp>
#include <iostream>

class PacketObserver
{
public:
	virtual void PacketUpdate(sf::Packet packet) { std::cout << "PACKET UPDATE IN BASE\n"; }
};