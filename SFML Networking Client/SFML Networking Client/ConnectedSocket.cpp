#include "ConnectedSocket.h"
#include <iostream>

ConnectedSocket::ConnectedSocket()
{
    //std::cout << "test";
}

void ConnectedSocket::IConnectToServer()
{
    sf::Socket::Status status = socket.connect(sf::IpAddress::LocalHost, 50007);
    if (status != sf::Socket::Done)
    {
        std::cout << "ERROR, NO SERVER FOUND";
        return;
    }

    std::cout << "Connected to server \n";

    socket.setBlocking(false);
}

void ConnectedSocket::IRegisterPacketObserver(PacketObserver& o)
{
    packetObservers.push_back(&o);
    //std::cout << "Observers in list: " << packetObservers.size() << "\n";
}

void ConnectedSocket::IRemovePacketObserver(PacketObserver& o)
{
    //packetObservers.erase(o);
}

void ConnectedSocket::NotifyPacketObservers(sf::Packet packet)
{
    for (PacketObserver* obs : packetObservers)
    {
        obs->PacketUpdate(packet);
    }
}

void ConnectedSocket::IReceivePackets()
{
    sf::Packet packet;
    if (socket.receive(packet) == sf::Socket::Done)
    {
        NotifyPacketObservers(packet);
    }
}


void ConnectedSocket::ISendPacket(sf::Packet packet)
{
    std::cout << "send packet to server\n";
    socket.send(packet);
}
