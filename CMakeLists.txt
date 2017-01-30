#Change this if you need to target a specific CMake version
cmake_minimum_required(VERSION 2.6)


# Enable debug symbols by default
# must be done before project() statement
if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug CACHE STRING "Choose the type of build (Debug or Release)" FORCE)
endif ()
# (you can also set it on the command line: -D CMAKE_BUILD_TYPE=Release)

project(Skilled_Eagle-Game)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -lpthread -std=c++14")
set(SFML_ROOT ${PROJECT_SOURCE_DIR}"SFML")

# Set version information in a config.h fil
include_directories("${PROJECT_BINARY_DIR}")

# Define sources and executable
set(EXECUTABLE_NAME ${PROJECT_NAME})
add_executable(${EXECUTABLE_NAME}
        #CORE
        Source/main.cpp
        Source/Game.cpp
        Source/Game.h

        #STATES
        Source/GameStates/IState.h
        Source/GameStates/PlayState.h
        Source/GameStates/PlayState.cpp
        Source/GameStates/MenuState.h
        Source/GameStates/MenuState.cpp
        Source/GameStates/SettingsState.h
        Source/GameStates/SettingsState.cpp
        Source/GameStates/SplashState.hpp
        Source/GameStates/SplashState.cpp
        Source/GameStates/SoundTestState.hpp
        Source/GameStates/SoundTestState.cpp
        Source/GameStates/ControlsState.cpp
        Source/GameStates/ControlsState.hpp
        Source/GameStates/PauseState.cpp
        Source/GameStates/PauseState.hpp
        Source/GameStates/SoonState.cpp
        Source/GameStates/SoonState.hpp
        Source/GameStates/LevelSelectState.cpp
        Source/GameStates/LevelSelectState.hpp

        #Environment
        Source/Level.cpp
        Source/Level.h
        Source/ScreenObjects/ScreenObject.cpp
        Source/ScreenObjects/ScreenObject.h
        Source/ScreenObjects/Block.cpp
        Source/ScreenObjects/Block.h
        Source/ScreenObjects/Finish.cpp
        Source/ScreenObjects/Finish.hpp

        #GUI
        Source/Menu.cpp
        Source/Menu.hpp

        #ITEMS
        Source/ScreenObjects/PowerUp.cpp
        Source/ScreenObjects/PowerUp.hpp
        Source/ScreenObjects/items/MeleeWeapon.cpp
        Source/ScreenObjects/items/MeleeWeapon.hpp

        #CHARACTERS
        Source/Character.cpp
        Source/Character.hpp
        Source/ScreenObjects/enemies/CyberEnforcer.h
        Source/ScreenObjects/enemies/CyberEnforcer.cpp
        Source/ScreenObjects/items/RangedWeapon.cpp
        Source/ScreenObjects/items/RangedWeapon.hpp
        Source/ScreenObjects/items/Weapon.hpp
        Source/ScreenObjects/Bullet.cpp
        Source/ScreenObjects/Bullet.hpp
        Source/ScreenObjects/StatusBar.cpp
        Source/ScreenObjects/StatusBar.hpp

        #AUDIO
        Source/Audio/BeatDetector.h
        Source/Audio/BeatDetector.cpp
        Source/Audio/SoundManager.h
        Source/Audio/SoundManager.cpp
        Source/Audio/BeatListener.hpp
        Source/ScreenObjects/HudDisplay.cpp
        Source/ScreenObjects/HudDisplay.hpp

        #Utility
        Source/Utility/ResourceHolder.hpp
        Source/Utility/ResourceIdentifiers.hpp
        Source/Utility/ResourceHolder.inl
        Source/Utility/DebugOverlay.cpp
        Source/Utility/DebugOverlay.hpp)
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
    IF (CMAKE_SIZEOF_VOID_P EQUAL 8)
        set(FMOD_LIBRARY ${PROJECT_SOURCE_DIR}/FMOD/lib/fmod64.dll)
    ELSE (CMAKE_SIZEOF_VOID_P EQUAL 8)
        set(FMOD_LIBRARY ${PROJECT_SOURCE_DIR}/FMOD/lib/fmod.dll)
    ENDIF (CMAKE_SIZEOF_VOID_P EQUAL 8)
ENDIF (UNIX)
find_package(FMOD)
if (FMOD_FOUND)
    include_directories(${FMOD_INCLUDE_DIR})
    target_link_libraries(${EXECUTABLE_NAME} ${FMOD_LIBRARIES})
endif ()

