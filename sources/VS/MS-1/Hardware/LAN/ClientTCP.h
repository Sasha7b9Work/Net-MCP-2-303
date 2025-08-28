// 2022/05/04 14:41:11 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once


namespace ClientTCP
{
    void Connect(uint16 port);

    bool Connected();

    void Disconnect();

    void Transmit(const void *buffer, int size);
};
