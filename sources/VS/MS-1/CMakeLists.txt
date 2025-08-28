# (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by

project (MS-1)

#set(CMAKE_UNITY_BUILD OFF)

set(CMAKE_UNITY_BUILD_BATCH_SIZE 16)


include_directories(
    .
    ../../MS-1/src
    ../../MS-1/src/Hardware/CDC
    ../../MS-1/src/Hardware/HAL
    ../../VS/ThirdParty/wxWidgets/include
    ../../generated/ThirdParty/lib/vc_dll/mswud
    ../../generated/ThirdParty/lib/vc_lib/mswud
    ../../common/_VS_KEIL/CMSIS
    ../../common/_VS_LIBS/STM32F3
    ../../common/STM32Cube_F3/Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc
    ../../common/STM32Cube_F3/Middlewares/ST/STM32_USB_Device_Library/Core/Inc
    ../../common/STM32Cube_F3/Drivers/CMSIS/Device/ST/STM32F3xx/Include
    ../../common/STM32Cube_F3/Drivers/STM32F3xx_HAL_Driver/Inc
)

link_directories(
    ../../generated/ThirdParty/lib/vc_dll
    ../../generated/ThirdParty/lib/vc_lib
)

add_definitions(-DSTM32F303xC -DGUI -DDEVICE)

if(WIN32)
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -MP -Wall")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /SUBSYSTEM:WINDOWS")

    add_compile_options(
        /wd4100    # 'xxx' : unreferenced formal parameter
        /wd4310
        /wd4365    # 'action' : conversion from 'type_1' to 'type_2', signed/unsigned mismatch
        /wd4514    # 'function' : unreferenced inline function has been removed
        /wd4623    # 'derived class' : default constructor was implicitly defined as deleted
        /wd4625    # 'derived class' : copy constructor was implicitly defined as deleted because
                   # a base class copy constructor is inaccessible or deleted
        /wd4626    # 'derived class' : assignment operator was implicitly defined as deleted because
                   # a base class assignment operator is inaccessible or deleted
        /wd4774    # 'string' : format string expected in argument number is not a string literal
        /wd4820    # 'xxx' bytes padding added after construct 'member_name'
        /wd4996    # deprecated
        /wd5026    # 'type': move constructor was implicitly defined as deleted
        /wd5027    # "type": оператор присваивания перемещения неявно определен как удаленный
        /wd5039    # 'xxx': pointer or reference to potentially throwing function passed to extern C
                   # function under -EHc.
        /wd5045    # Compiler will insert Spectre mitigation for memory load if /Qspectre switch specified
        /wd5220    # 'xxx': a non-static data member with a volatile qualified type no longer implies that
                   # compiler generated copy/move constructors and copy/move assignment operators are not trivial
                   # add_compile_options(/wd26812)
        /wd5267
    )

endif()

file(GLOB DOC                       ../../MS-1/doc/*.*)
file(GLOB LIBS_STM32F3              ../../common/_VS_LIBS/STM32f3/*.*)
file(GLOB LIBS_STM32F3_INC          ../../common/STM32Cube_F3/Drivers/STM32F3xx_HAL_Driver/Inc/*.*)
file(GLOB LIBS_USBD                 ../../common/_VS_LIBS/USBD/*.*)
file(GLOB SRC                       *.h *.cpp
                                    ../../MS-1/src/*.*)
file(GLOB DISPLAY                   ../../MS-1/src/Display/*.*)
file(GLOB DISPLAY_FONT              ../../MS-1/src/Display/Font/*.*)
file(GLOB HARDWARE                  ../../MS-1/src/Hardware/*.*)
file(GLOB HARDWARE_CDC              ../../MS-1/src/Hardware/CDC/*.*
                                                    Hardware/CDC/*.*)
file(GLOB HARDWARE_HAL              ../../MS-1/src/Hardware/HAL/*.h
                                    ../../MS-1/src/Hardware/HAL/HAL_ADC.cpp
                                    ../../MS-1/src/Hardware/HAL/HAL_I2C.cpp
                                    ../../MS-1/src/Hardware/HAL/HAL_RTC.cpp
                                    ../../MS-1/src/Hardware/HAL/HAL_SPI1.cpp
                                    ../../MS-1/src/Hardware/HAL/HAL_USART1.cpp
                                    ../../MS-1/src/Hardware/HAL/HAL_USART2.cpp
                                    ../../MS-1/src/Hardware/HAL/HAL_IWDG.cpp
                                    ../../MS-1/src/Hardware/HAL/HAL_PINS.cpp
                                                    Hardware/HAL/*.*)
file(GLOB HARDWARE_LAN                              Hardware/LAN/*.*)
file(GLOB HARDWARE_LAN_LIBNET                       Hardware/LAN/libnet/*.*)
file(GLOB MENU                      ../../MS-1/src/Menu/*.*)
file(GLOB MENU_PAGES                ../../MS-1/src/Menu/Pages/*.*)
file(GLOB MODULES_BME280            ../../MS-1/src/Modules/BME280/*.*)
file(GLOB MODULES_CG_ANEM           ../../MS-1/src/Modules/CG-Anem/*.*)
file(GLOB MODULES_GY511             ../../MS-1/src/Modules/GY511/*.*)
file(GLOB MODULES_HC12              ../../MS-1/src/Modules/HC12/*.*)
file(GLOB MODULES_NEO_M8N           ../../MS-1/src/Modules/NEO-M8N/*.*)
file(GLOB MODULES_HIH4000           ../../MS-1/src/Modules/HIH4000/*.*)
file(GLOB MODULES_ST7735            ../../MS-1/src/Modules/ST7735/*.*)
file(GLOB MODULES_W25Q80DV          ../../MS-1/src/Modules/W25Q80DV/*.h
                                                   Modules/W25Q80DV/*.cpp)
file(GLOB SCPI                      ../../MS-1/src/SCPI/*.*)
file(GLOB SETTINGS                  ../../MS-1/src/Settings/*.*)
file(GLOB STORAGE                   ../../MS-1/src/Storage/*.*)
file(GLOB TESTS                     ../../MS-1/src/Tests/*.*)
file(GLOB UTILS                     ../../MS-1/src/Utils/*.*)
file(GLOB UTILS_TEXT                ../../MS-1/src/Utils/Text/*.*)

source_group(doc                    FILES ${DOC})
source_group(libs/STM32F3           FILES ${LIBS_STM32F3})
source_group(libs/STM32F3/Inc       FILES ${LIBS_STM32F3_INC})
source_group(libs/USBD              FILES ${LIBS_USBD})
source_group(src                    FILES ${SRC})
source_group(Display                FILES ${DISPLAY})
source_group(Display/Font           FILES ${DISPLAY_FONT})
source_group(Hardware               FILES ${HARDWARE})
source_group(Hardware/CDC           FILES ${HARDWARE_CDC})
source_group(Hardware/HAL           FILES ${HARDWARE_HAL})
source_group(Hardware/LAN           FILES ${HARDWARE_LAN})
source_group(Hardware/LAN/libnet    FILES ${HARDWARE_LAN_LIBNET})
source_group(Menu                   FILES ${MENU})
source_group(Menu/Pages             FILES ${MENU_PAGES})
source_group(Modules/BME280         FILES ${MODULES_BME280})
source_group(Modules/CG-Anem        FILES ${MODULES_CG_ANEM})
source_group(Modules/GY511          FILES ${MODULES_GY511})
source_group(Modules/HC12           FILES ${MODULES_HC12})
source_group(Modules/NEO-M8N        FILES ${MODULES_NEO_M8N})
source_group(Modules/HIH4000        FILES ${MODULES_HIH4000})
source_group(Modules/ST7735         FILES ${MODULES_ST7735})
source_group(Modules/W25Q80DV       FILES ${MODULES_W25Q80DV})
source_group(SCPI                   FILES ${SCPI})
source_group(Settings               FILES ${SETTINGS})
source_group(Storage                FILES ${STORAGE})
source_group(Tests                  FILES ${TESTS})
source_group(Utils                  FILES ${UTILS})
source_group(Utils/Text             FILES ${UTILS_TEXT})


set_source_files_properties(
    Hardware/LAN/libnet/netserver.cpp
    Hardware/LAN/libnet/netbase.cpp
    Hardware/LAN/libnet/netclient.cpp
    Hardware/LAN/libnet/netpacket.cpp
    Hardware/LAN/ClientTCP.cpp
    Application.cpp
    Frame.cpp
    main_win.cpp
    ../../MS-1/src/Storage/Measure.cpp
    ../../MS-1/src/Storage/MemoryStorage.cpp
    PROPERTIES SKIP_UNITY_BUILD_INCLUSION ON
)


set_source_files_properties(
    ../../MS-1/src/Hardware/CDC/usbd_conf.c
    ../../MS-1/src/Hardware/CDC/usbd_desc.c
    PROPERTIES HEADER_FILE_ONLY TRUE
)

add_executable( ${PROJECT_NAME}
    ${DOC}
    ${LIBS_STM32F3}
    ${LIBS_STM32F3_INC}
    ${LIBS_USBD}
    ${SRC}
    ${DISPLAY}
    ${DISPLAY_FONT}
    ${HARDWARE}
    ${HARDWARE_CDC}
    ${HARDWARE_HAL}
    ${HARDWARE_LAN}
    ${HARDWARE_LAN_LIBNET}
    ${MENU}
    ${MENU_PAGES}
    ${MODULES_BME280}
    ${MODULES_CG_ANEM}
    ${MODULES_GY511}
    ${MODULES_HC12}
    ${MODULES_NEO_M8N}
    ${MODULES_HIH4000}
    ${MODULES_ST7735}
    ${MODULES_W25Q80DV}
    ${SCPI}
    ${SETTINGS}
    ${STORAGE}
    ${TESTS}
    ${UTILS}
    ${UTILS_TEXT}
)

target_link_libraries(${PROJECT_NAME}
    wxbase32ud wxmsw32ud_core wxpngd wxzlibd
    Ws2_32 Comctl32 Rpcrt4
)
