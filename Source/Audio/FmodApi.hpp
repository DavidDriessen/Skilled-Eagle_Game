//
// Created by endargon on 1/23/17.
//

#ifndef SKILLED_EAGLE_GAME_FMODAPI_HPP
#define SKILLED_EAGLE_GAME_FMODAPI_HPP

#include <fmod.hpp>
#include <cstdio>
#include <stdlib.h>
#include <fmod_errors.h>
#include <map>
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <malloc.h>

class FmodApi {
private:
    FMOD::System *system = NULL;
    FMOD::Channel *channel = NULL;
    FMOD::DSP *dsp = NULL;
    float samples[2048];
    int peak = 0;
    std::map<std::string, std::pair<FMOD::Channel*, FMOD::Sound*>> sounds;
public:
    FmodApi() {
        has_error(FMOD::System_Create(&system));
        has_error(system->init(512, FMOD_INIT_NORMAL, 0));
        system->createDSPByType(FMOD_DSP_TYPE::FMOD_DSP_TYPE_FFT, &dsp);
        dsp->setActive(true);
    }

    void has_error(FMOD_RESULT res) {
        if (res != FMOD_OK) {
            printf("FMOD error! (%d) %s\n", res, FMOD_ErrorString(res));
            exit(-1);
        }
    }

    void add_song(const char * name, const char * path) {
        FMOD::Sound *t;
        FMOD::Channel *c;
        sounds.insert({name, {c, t}});
        system->createStream(path, FMOD_DEFAULT, 0, &sounds.find(name)->second.second);
        system->playSound(sounds.find(name)->second.second, 0, true, &sounds.find(name)->second.first);
    }

    void play_song(const char *name) {
        bool paused = NULL;
        bool playing = NULL;
        sounds.find(name)->second.first->getPaused(&paused);
        sounds.find(name)->second.first->isPlaying(&playing);
        if(!playing) {
            system->playSound(sounds.find(name)->second.second, 0, false, &sounds.find(name)->second.first);
        }
        else if(paused) {
            sounds.find(name)->second.first->setPaused(0);
        } else {
            system->playSound(sounds.find(name)->second.second, 0, false, &sounds.find(name)->second.first);
        }
        sounds.find(name)->second.first->addDSP(FMOD_CHANNELCONTROL_DSP_HEAD, dsp);
    }


    void pause_song(const char *name) {
        sounds.find(name)->second.first->setPaused(true);
    }

    void toggle_play(const char *name) {
        bool paused = NULL;
        sounds.find(name)->second.first->getPaused(&paused);
        if(paused) {
            play_song(name);
        } else {
            pause_song(name);
        }
    }

    void update() {
        system->update();
        FMOD_DSP_PARAMETER_FFT *fft;
        dsp->getParameterData(FMOD_DSP_FFT_SPECTRUMDATA, (void **) &fft, 0, 0, 0);
        for (int bin = 0; bin < fft->length; bin++) {
            samples[bin] = fft->spectrum[0][bin];
        }
        auto maxIterator = std::max_element(&samples[0], &samples[2048]);
        set_peak(*maxIterator*10000);
    }

    void set_peak(int peak) {
        this->peak = peak;
    }


    int get_current_peak() {
        return peak;
    }

    void stop_song(const char *string);
};
#endif //SKILLED_EAGLE_GAME_FMODAPI_HPP
