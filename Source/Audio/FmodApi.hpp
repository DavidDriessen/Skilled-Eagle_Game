//
// Created by endargon on 1/23/17.
//

#ifndef SKILLED_EAGLE_GAME_FMODAPI_HPP
#define SKILLED_EAGLE_GAME_FMODAPI_HPP
#include <fmod.h>
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
    FMOD_SYSTEM *system = NULL;
    FMOD_CHANNEL *channel = NULL;
    FMOD_DSP *dsp = NULL;
    float samples[2][2048];
    float spec[2048];
    int peak = 0;
    std::map<std::string, std::pair<FMOD_CHANNEL*, FMOD_SOUND*>> sounds;
public:
    FmodApi() {
        FMOD_System_Create(&system);
        FMOD_System_Init(system, 32, FMOD_INIT_NORMAL, 0);
        FMOD_System_CreateDSPByType(system, FMOD_DSP_TYPE::FMOD_DSP_TYPE_FFT, &dsp);
        FMOD_DSP_SetActive(dsp, true);
    }

    void has_error(FMOD_RESULT res) {
        if (res != FMOD_OK) {
            printf("FMOD error! (%d) %s\n", res, FMOD_ErrorString(res));
            exit(-1);
        }
    }

    void add_song(const char * name, const char * path) {
        FMOD_SOUND *t;
        FMOD_CHANNEL *c;
        sounds.insert({name, {c, t}});
        FMOD_System_CreateStream(system, path, FMOD_DEFAULT, 0, &sounds.find(name)->second.second);
        FMOD_System_PlaySound(system, sounds.find(name)->second.second, 0, true, &sounds.find(name)->second.first);
    }

    void play_song(const char *name) {
        FMOD_BOOL paused = false;
        FMOD_BOOL playing = false;
        FMOD_Channel_GetPaused(sounds.find(name)->second.first, &paused);
        FMOD_Channel_IsPlaying(sounds.find(name)->second.first, &playing);
        if(!playing) {
            FMOD_System_PlaySound(system, sounds.find(name)->second.second, 0, false, &sounds.find(name)->second.first);
        }
        else if(paused) {
            FMOD_Channel_SetPaused(sounds.find(name)->second.first, false);
        } else {
            FMOD_System_PlaySound(system, sounds.find(name)->second.second, 0, false, &sounds.find(name)->second.first);
        }
        FMOD_Channel_AddDSP(sounds.find(name)->second.first, FMOD_CHANNELCONTROL_DSP_HEAD, dsp);
    }


    void pause_song(const char *name) {
        FMOD_Channel_SetPaused(sounds.find(name)->second.first, true);
    }

    void toggle_play(const char *name) {
        FMOD_BOOL paused = false;
        FMOD_Channel_GetPaused(sounds.find(name)->second.first, &paused);
        if(paused) {
            play_song(name);
        } else {
            pause_song(name);
        }
    }

    void update() {
        FMOD_System_Update(system);
        FMOD_DSP_PARAMETER_FFT *fft;
        FMOD_DSP_GetParameterData(dsp, FMOD_DSP_FFT_SPECTRUMDATA, (void **) &fft, 0, 0, 0);
        for(int i = 0; i < 2; i++) {
            for (int bin = 0; bin < fft->length; bin++) {
                    samples[i][bin] = fft->spectrum[i][bin];
            }
        }
        for (int i = 0; i < 2048; i++) {
            spec[i] = (samples[0][i] + samples[1][i]) / 2;
        }
        // Find max volume
        auto maxIterator = std::max_element(&spec[0], &spec[2048]);
        float maxVol = *maxIterator;
        // Normalize
        if (maxVol != 0)
            std::transform(&spec[0], &spec[2048], &spec[0], [maxVol] (float dB) -> float { return dB / maxVol; });
        set_peak(*maxIterator*10000);

    }

    float *get_spec() {
        return spec;
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
