// 2022/05/04 14:41:28 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "defines.h"
#include "Hardware/LAN/ClientTCP.h"
#include "Hardware/LAN/libnet/netclient.h"


namespace ClientTCP
{
    net__::netclient client(2);

    sock_t socket = -1;
}


void ClientTCP::Connect(uint16 port)
{
    Disconnect();

    client.setConnTimeout(0);

    socket = client.doConnect("localhost", port);
}


bool ClientTCP::Connected()
{
    return !client.isClosed(socket);
}


void ClientTCP::Disconnect()
{
    if (!Connected())
    {
        return;
    }

    client.disconnect(socket);
}


void ClientTCP::Transmit(const void *buffer, int size)
{
    if (!Connected())
    {
        return;
    }

    net__::netpacket packet((size_t)size, (uint8 *)buffer);

    if (client.sendPacket(socket, packet) < 0)
    {
        client.disconnect(socket);
    }
}
