// 2023/12/22 11:26:44 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "defines.h"
#include "Modules/W25Q80DV/W25Q80DV.h"
#include <cstring>


template void W25Q80DV::WriteBuffer<36>(uint, const void *);
template uint8 *MemBuffer<512>::Read(uint);
template uint8 *MemBuffer<8192>::Read(uint);


namespace W25Q80DV
{
    static uint8 buffer[SIZE];
}


template<int size>
uint8 *MemBuffer<size>::Read(uint address)
{
    std::memcpy(Data(), &W25Q80DV::buffer[address], size);

    return Data();
}


void W25Q80DV::Init()
{
    for (uint i = 0; i < SIZE; i++)
    {
        buffer[i] = 0xFF;
    }
}


template<int count>
void W25Q80DV::WriteBuffer(uint address, const void *_buffer)
{
    std::memcpy(&buffer[address], _buffer, count);
}


void W25Q80DV::ErasePage(int num_page)
{
    uint address = num_page * SIZE_PAGE;
    uint end = address + SIZE_PAGE;

    while (address < end)
    {
        buffer[address++] = 0xFF;
    }
}


void W25Q80DV::WriteUInt(uint address, uint value)
{
    BitSet32 data(value);

    buffer[address++] = data.bytes[0];
    buffer[address++] = data.bytes[1];
    buffer[address++] = data.bytes[2];
    buffer[address++] = data.bytes[3];
}


uint W25Q80DV::ReadUInt(uint address)
{
    BitSet32 data(0);

    data.bytes[0] = buffer[address++];
    data.bytes[1] = buffer[address++];
    data.bytes[2] = buffer[address++];
    data.bytes[3] = buffer[address++];

    return data.word;
}
