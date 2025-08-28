// 2022/04/27 11:48:13 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "defines.h"
#include "Device.h"
#include "Modules/HC12/HC12.h"
#include "Modules/BME280/BME280.h"
#include "Modules/CG-Anem/CG-Anem.h"
#include "Modules/ST7735/ST7735.h"
#include "Hardware/Timer.h"
#include "Hardware/InterCom.h"
#include "Hardware/Keyboard.h"
#include "Hardware/Beeper.h"
#include "Hardware/EnergySwitch.h"
#include "Modules/GY511/GY511.h"
#include "Modules/NEO-M8N/NEO-M8N.h"
#include "Storage/Storage.h"
#include "Menu/Menu.h"
#include "Tests/Tests.h"
#include "SCPI/SCPI.h"


namespace Device
{
    static void ProcessMeasure(const Measure &, uint time);

    void RunTests();
}


void Device::Init()
{
    HAL::Init();

    ST7735::Init();         // Дисплей

    EnergySwitch::Init();

    BME280::Init();         // Температура, давление, влажность, точка росы

    GY511::Init();          // Компас

    HC12::Init();           // Радиомодуль

    Keyboard::Init();

    Beeper::Init();

    InterCom::SetDirection((Direction::E)(Direction::HC12 | Direction::Display));

    HAL_USART2::Init();

    W25Q80DV::Init();

//    W25Q80DV::Test::Run();

    Storage::Init();

//    HAL_IWDG::Init();
}


void Device::Update()
{
//    HAL_IWDG::Update();

    NEO_M8N::Update();

    Measure temp;
    Measure pressure;
    Measure humidity;
    Measure dew_point;
    Measure velocity;
    Measure azimuth;
    Measure latitude;
    Measure longitude;
    Measure altitude;

    uint time = TIME_MS;

    if (BME280::GetMeasures(&temp, &pressure, &humidity, &dew_point))
    {
        ProcessMeasure(temp, time);
        ProcessMeasure(pressure, time);
        ProcessMeasure(humidity, time);
        ProcessMeasure(dew_point, time);
    }

    if (CG_Anem::GetMeasure(&velocity))
    {
        ProcessMeasure(velocity, time);
    }

    if (GY511::GetAzimuth(&azimuth))
    {
        ProcessMeasure(azimuth, time);
    }

    if (NEO_M8N::GetMeasures(&latitude, &longitude, &altitude))
    {
        ProcessMeasure(latitude, time);
        ProcessMeasure(longitude, time);
        ProcessMeasure(altitude, time);
    }

    if (!Menu::IsOpened())
    {
        Beeper::Update();
    }

    Keyboard::Update();

    Display::Update(TIME_MS);

    HAL_ADC::GetVoltage();

    EnergySwitch::Update();

    Storage::SaveMeasures();

    SCPI::Update();
}


void Device::ProcessMeasure(const Measure &measure, uint time)
{
    if (measure.correct)
    {
        InterCom::Send(measure, time);

        Storage::AppendMeasure(measure);
    }
}


void Device::RunTests()
{
    Test::Settings::Run();
}
