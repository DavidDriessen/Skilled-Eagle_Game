//
// Created by david on 11/16/2016.
//

#include <SFML/Graphics.hpp>
#include "Game.h"
#include <fmod.hpp>
#include <stdlib.h>
#include <fmod_errors.h>

void fmod_error(FMOD_RESULT res) {
    if (res != FMOD_OK) {
        printf("FMOD error! (%d) %s\n", res, FMOD_ErrorString(res));
        exit(-1);
    }
}

int main() {
    sf::RenderWindow window(sf::VideoMode(640, 480), "WaveForms");
    // Game application class
    window.setFramerateLimit(60);
    FMOD_RESULT result;
    FMOD::System *system = NULL;
    FMOD::Sound *sound;
    FMOD::Channel *channel;
    fmod_error(FMOD::System_Create(&system));
    fmod_error(system->init(512, FMOD_INIT_NORMAL, 0));
    system->createStream("./assets/sounds/test.mp3", FMOD_DEFAULT, 0, &sound);
    system->playSound(sound, 0, false, &channel);

    FMOD::DSP *dsp;
    system->createDSPByType(FMOD_DSP_TYPE::FMOD_DSP_TYPE_FFT, &dsp);
    dsp->setActive(true);
    system->playSound(sound, 0, false, &channel);
    channel->addDSP(FMOD_CHANNELCONTROL_DSP_HEAD, dsp);
    sf::RectangleShape shape;
    shape.setSize({20, 20});
    shape.setFillColor(sf::Color::Red);
    shape.setScale({1, 1});
    shape.setPosition({window.getSize().x/2, window.getSize().y/2});

    while (1) {
        FMOD_DSP_PARAMETER_FFT *fft;
        float samples[2048];
        system->update();
        dsp->getParameterData(FMOD_DSP_FFT_SPECTRUMDATA, (void **) &fft, 0, 0, 0);
        for (int bin = 0; bin < fft->length; bin++) {
            samples[bin] = fft->spectrum[0][bin];
        }
        auto maxIterator = std::max_element(&samples[0], &samples[2048]);
        int maxVol = *maxIterator*1000;
        if(maxVol > 0) {
            int height = ((float)window.getSize().y/(float)100)*(float)maxVol/((float)400/(float)100);
            shape.setSize({window.getSize().x, height});
            shape.setPosition({0, window.getSize().y - shape.getSize().y});
        }
        window.clear();
        window.draw(shape);
        window.display();

//        std::cout << std::to_string(fft->spectrum[0][0]) << "\n";

    }
//    Game waveForms(window);
    return 0;
}