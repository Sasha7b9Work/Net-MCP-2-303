// Sasha7b9@tut.by (c)
#include "defines.h"
#include "Hardware/InterCom.h"
#include "Hardware/CDC/CDC.h"
#include "Modules/HC12/HC12.h"
#include "Modules/ST7735/ST7735.h"
#include "Display/Display.h"
#include "Utils/Text/String.h"
#include "Utils/Buffer.h"
#include "Utils/Math.h"
#include "Settings/Settings.h"
#include "Hardware/HAL/HAL.h"
#include "Storage/Measures.h"

#ifdef GUI
    #include "Hardware/LAN/ClientTCP.h"
#endif


namespace InterCom
{
    static Direction::E direction = Direction::_None;

    static Buffer<16> CreateMessage(const Measure &measure)
    {
        Buffer<16> message;

        message[0] = 'A';
        message[1] = 'B';
        message[2] = 'C';
        message[3] = (uint8)measure.GetName();

        uint id = HAL::GetUID();

        std::memcpy(&message[4], &id, sizeof(id));

        float value = (float)measure.GetDouble();

        std::memcpy(&message[8], &value, sizeof(value));

        uint hash = Math::CalculateCRC(&value, sizeof(value));

        std::memcpy(&message[12], &hash, sizeof(hash));

        return message;
    }
}


void InterCom::SetDirection(Direction::E dir)
{
    direction = dir;
}


void InterCom::Send(const Measure &measure, uint timeMS)
{
    static const pchar names[Measure::Count] =
    {
        "Temperature",
        "Pressure",
        "Humidity",
        "DewPoint",
        "Velocity",
        "Latitude",
        "Longitude",
        "Altitude",
        "Azimuth"
    };

    static const pchar units[Measure::Count] =
    {
        "degress Celsius",
        "hPa",
        "%%",
        "degress Celsius",
        "m/s",
        "degress",
        "degress",
        "m",
        "degress"
    };

    if (direction & Direction::Display)
    {
        if (!Measures::IsFixed())
        {
            Display::SetMeasure(measure, timeMS);
        }
    }

    if (direction & Direction::CDC)
    {
        String<> message("%s : %f %s", names[measure.GetName()], measure.GetDouble(), units[measure.GetName()]);

        HCDC::Transmit(message.c_str(), message.Size() + 1);
    }

    Buffer<16> data = CreateMessage(measure); //-V821

    if (direction & Direction::HC12)
    {
        HC12::Transmit(data.Data(), data.Size());
    }

#ifdef GUI

    ClientTCP::Transmit(data.Data(), data.Size()); 

#endif
}
