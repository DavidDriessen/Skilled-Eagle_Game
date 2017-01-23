//
// Created by david on 11/16/2016.
//

#include <SFML/Graphics.hpp>
#include "Game.h"
#include <stdlib.h>

int main() {
    sf::RenderWindow window(sf::VideoMode(640, 480), "WaveForms");
    // Game application class
    window.setFramerateLimit(60);
    Game waveForms(window);

//    FMOD_RESULT result;
//    FMOD::System *system = NULL;
//    FMOD::Sound *sound;
//    FMOD::Channel *channel;
//    fmod_error(FMOD::System_Create(&system));
//    fmod_error(system->init(512, FMOD_INIT_NORMAL, 0));
//    system->createStream("./assets/sounds/song.mp3", FMOD_DEFAULT, 0, &sound);
//    system->playSound(sound, 0, false, &channel);
//
//    FMOD::DSP *dsp;
//    system->createDSPByType(FMOD_DSP_TYPE::FMOD_DSP_TYPE_FFT, &dsp);
//    dsp->setActive(true);
//    system->playSound(sound, 0, false, &channel);
//    channel->addDSP(FMOD_CHANNELCONTROL_DSP_HEAD, dsp);
//    sf::RectangleShape shape;
//    shape.setSize({20, 20});
//    shape.setFillColor(sf::Color::Red);
//    shape.setScale({1, 1});
//    shape.setPosition({window.getSize().x/2, window.getSize().y/2});
//    while (1) {

//
////        std::cout << std::to_string(fft->spectrum[0][0]) << "\n";
//
//    }
//    Game waveForms(window);
    return 0;
}