#Change this if you need to target a specific CMake version
cmake_minimum_required(VERSION 2.6)


# Enable debug symbols by default
# must be done before project() statement
if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug CACHE STRING "Choose the type of build (Debug or Release)" FORCE)
endif ()
# (you can also set it on the command line: -D CMAKE_BUILD_TYPE=Release)

project(Skilled_Eagle-Game)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")
set(SFML_ROOT ${PROJECT_SOURCE_DIR}"SFML")

# Set version information in a config.h fil
include_directories("${PROJECT_BINARY_DIR}")

# Define sources and executable
set(EXECUTABLE_NAME ${PROJECT_NAME})
add_executable(${EXECUTABLE_NAME}
        Source/main.cpp
        Source/GameStates/IState.h
        Source/GameStates/PlayState.cpp
        Source/GameStates/PlayState.h
        Source/GameStates/MenuState.cpp
        Source/GameStates/MenuState.h
        Source/GameStates/SettingsState.cpp
        Source/GameStates/SettingsState.h
        Source/Game.cpp
        Source/Game.h
        Source/Level.cpp
        Source/Level.h
        Source/ScreenObjects/ScreenObject.cpp
        Source/ScreenObjects/ScreenObject.h
        Source/ScreenObjects/Block.cpp
        Source/ScreenObjects/Block.h
        Source/Menu.cpp
        Source/Menu.hpp
        Source/GameStates/SplashState.cpp
        Source/GameStates/SplashState.hpp
        Source/Audio/FmodApi.cpp
        Source/Audio/FmodApi.hpp
        Source/GameStates/SoundTestState.cpp
        Source/GameStates/SoundTestState.hpp
        Source/GameStates/ControllesState.cpp
        Source/GameStates/ControllesState.hpp
        Source/Character.cpp
        Source/Character.hpp
        Source/GameStates/ControlsState.cpp
        Source/GameStates/ControlsState.hpp
        Source/ScreenObjects/items/rangedWeapon.cpp
        Source/ScreenObjects/items/rangedWeapon.hpp
        Source/ScreenObjects/items/weapon.hpp
        Source/ScreenObjects/bullet.cpp
        Source/ScreenObjects/bullet.hpp
        Source/Audio/BeatDetector.h
        Source/Audio/BeatDetector.cpp
        Source/Audio/SoundManager.h
        Source/Audio/SoundManager.cpp
        Source/GameStates/PauseState.cpp
        Source/GameStates/PauseState.hpp
        )

# Detect and add SFML
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})
#Find any version 2.X of SFML
#See the FindSFML.cmake file for additional details and instructions
find_package(SFML 2 REQUIRED system window graphics network audio)
if (SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
    target_link_libraries(${EXECUTABLE_NAME} ${SFML_LIBRARIES})
endif ()

set(FMOD_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/FMOD/inc)
IF (UNIX)
    set(FMOD_LIBRARY ${PROJECT_SOURCE_DIR}/FMOD/lib/x86_64/libfmod.so)
ELSE (UNIX)
    set(FMOD_LIBRARY ${PROJECT_SOURCE_DIR}/FMOD/lib/fmod.dll)
ENDIF (UNIX)
find_package(FMOD)
if (FMOD_FOUND)
    include_directories(${FMOD_INCLUDE_DIR})
    target_link_libraries(${EXECUTABLE_NAME} ${FMOD_LIBRARIES})
endif ()

