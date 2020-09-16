cmake_minimum_required(VERSION 3.15.2)

project(LevitationController)

set(target ${PROJECT_NAME})

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt5 COMPONENTS Widgets SerialPort REQUIRED)

find_package(spdlog REQUIRED)

add_executable(${target}
    ArduinoMega.cpp 
    Transducer.cpp 
    main.cpp 
    MainWindow.cpp 
    phaseCalculator.cpp 
    structureReader.cpp
    MainWindow.ui
)

qt5_use_modules(${target} 
    Widgets     
    SerialPort
)

target_link_libraries(${target}
    ${spdlog_LIBS}
)
