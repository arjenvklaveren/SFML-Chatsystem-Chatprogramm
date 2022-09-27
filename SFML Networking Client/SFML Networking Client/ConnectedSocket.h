#pragma once
#include <SFML/Network.hpp>
#include "PacketObserver.h"
#include <vector>

class ConnectedSocket
{
public:
	ConnectedSocket(const ConnectedSocket&) = delete;

	static ConnectedSocket& Get()
	{
		static ConnectedSocket CS;
		return CS;
	}

	static void ConnectToServer() { return Get().IConnectToServer(); };
	static void ReceivePackets() { return Get().IReceivePackets(); };
	static void SendPacket(sf::Packet packet) { return Get().ISendPacket(packet); }
	static void RegisterPacketObserver(PacketObserver& o) { return Get().IRegisterPacketObserver(o); };
	static void RemovePacketObserver(PacketObserver& o) { return Get().IRemovePacketObserver(o); };

private:
	sf::TcpSocket socket;
	ConnectedSocket();
	void IConnectToServer();
	void IReceivePackets();
	void ISendPacket(sf::Packet packet);
	void IRegisterPacketObserver(PacketObserver& o);
	void IRemovePacketObserver(PacketObserver& o);

	std::vector<PacketObserver*> packetObservers;
	void NotifyPacketObservers(sf::Packet packet);
};
