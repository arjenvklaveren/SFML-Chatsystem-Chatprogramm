#include <SFML/Network.hpp>
#include <iostream>
#include <list>
#include <thread>

sf::TcpListener listener;
const unsigned short portnumber = 50007;
std::map<std::string, sf::TcpSocket*> clients;

sf::SocketSelector selector;

int clientTotalCount;

void ProcessNewClients();
void ProcessExistingClients();
void CleanupClients();
void SendToAllClients(sf::Packet packet);
void SendToSingleClient(sf::Packet packet, sf::TcpSocket* client);

int main()
{
    std::cout << "Established a server on port: " << portnumber << "\n";
    listener.listen(portnumber);
    selector.add(listener);

    while (true)
    {
        if (selector.wait())
        {
            if (selector.isReady(listener))
            {
                ProcessNewClients();
            }
            else
            {
                ProcessExistingClients();               
            }
        }  
        //CleanupClients();
    }

    return 0;
}

void ProcessNewClients()
{
    sf::TcpSocket* client = new sf::TcpSocket;
    if (listener.accept(*client) == sf::Socket::Done)
    {
        clientTotalCount++;
        std::pair<std::string, sf::TcpSocket*> newClient("Client" + std::to_string(clientTotalCount), client);

        clients.insert(newClient);
        selector.add(*newClient.second);
        std::cout << "New client connected\n";

        std::string outmsg = "Welcome to the chatroom, " + newClient.first;

        sf::Packet packet;
        packet << outmsg;
        SendToSingleClient(packet, client);
    }
    else
    {
        delete client;
    }
}

void ProcessExistingClients()
{
    for (std::map<std::string, sf::TcpSocket*>::iterator it = clients.begin(); it != clients.end(); ++it)
    {
        sf::TcpSocket& client = *it->second;
        if (selector.isReady(client))
        {
            sf::Packet inPacket;
            if (client.receive(inPacket) == sf::Socket::Done)
            {
                std::string inString;
                inPacket >> inString;

                std::string outString;
                outString = it->first + ": " + inString;

                sf::Packet outPacket;
                outPacket << outString;

                std::cout << outString + "\n";

                SendToAllClients(outPacket);
            }
        }
    }
}

void CleanupClients()
{
    std::cout << "CLEANING?\n";
    for (int i = 0; i < clients.size(); i++)
    {
        std::map<std::string, sf::TcpSocket*>::iterator it = clients.begin();
        std::advance(it, i);
        sf::TcpSocket& client = *it->second;

        if (selector.isReady(client))
        {
            sf::Packet randomPacket;
            if (client.receive(randomPacket) == sf::Socket::Disconnected)
            {
                selector.remove(client);
                clients.erase(it);
                delete(&client);
                std::cout << "A client has been disconnected\n";
            }
            else
            {
                return;
            }
        }
        else
        {
            return;
        }
    }
}

void SendToAllClients(sf::Packet packet)
{
    for (std::map<std::string, sf::TcpSocket*>::iterator it = clients.begin(); it != clients.end(); ++it)
    {
        sf::TcpSocket& client = *it->second;
        client.send(packet);
    }
}

void SendToSingleClient(sf::Packet packet, sf::TcpSocket* client)
{
    client->send(packet);
}
