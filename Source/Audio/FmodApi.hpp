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
#include <SFML/System/Clock.hpp>
#include <queue>

class FmodApi {
private:
    FMOD_SYSTEM *system = NULL;
    FMOD_CHANNEL *channel = NULL;
    FMOD_DSP *dsp = NULL;
    float samples[2][2048];
    float spec[2048];
    int peak = 0;
    sf::Clock time;
    std::map<std::string, std::pair<FMOD_CHANNEL *, FMOD_SOUND *>> sounds;

    sf::Clock tick;
    float beatThresholdVolume = 0.3f;    // The threshold over which to recognize a beat
    int beatThresholdBar = 0;            // The bar in the volume distribution to examine
    unsigned int beatPostIgnore = 250;   // Number of ms to ignore track for after a beat is recognized
    int beatLastTick = 0;                // Time when last beat occurred
    // List of how many milliseconds ago the last beats were
    std::queue<int> beatTimes;

    // The number of milliseconds of previous beats to keep in the list
    unsigned int beatTrackCutoff = 10000;
    int beatSustain;
    int beatIgnoreLastTick;
    bool beat = false;
    sf::Clock test;
public:
    FmodApi() {
        FMOD_System_Create(&system);
        FMOD_System_Init(system, 32, FMOD_INIT_NORMAL, 0);
        FMOD_System_CreateDSPByType(system, FMOD_DSP_TYPE::FMOD_DSP_TYPE_FFT, &dsp);
        FMOD_DSP_SetActive(dsp, true);
        beatThresholdVolume = 0.3f;
        beatThresholdBar = 0;
        beatSustain = 150;
        beatPostIgnore = 250;
        beatTrackCutoff = 10000;
        beatLastTick = 0;
        beatIgnoreLastTick = 0;
    }

    bool isBeat() const {
        return beat;
    }

    void has_error(FMOD_RESULT res) {
        if (res != FMOD_OK) {
            printf("FMOD error! (%d) %s\n", res, FMOD_ErrorString(res));
            exit(-1);
        }
    }

    void add_song(const char *name, const char *path) {
        FMOD_SOUND *t;
        FMOD_CHANNEL *c;
        sounds.insert({name, {c, t}});
        FMOD_System_CreateStream(system, path, FMOD_DEFAULT, 0, &sounds.find(name)->second.second);
        FMOD_System_PlaySound(system, sounds.find(name)->second.second, 0, true, &sounds.find(name)->second.first);
//        FMOD_Channel_SetPitch(sounds.find(name)->second.first, 0.8);
    }

    void play_song(const char *name) {
        FMOD_BOOL paused = false;
        FMOD_BOOL playing = false;
        FMOD_Channel_GetPaused(sounds.find(name)->second.first, &paused);
        FMOD_Channel_IsPlaying(sounds.find(name)->second.first, &playing);
        if (!playing) {
            FMOD_System_PlaySound(system, sounds.find(name)->second.second, 0, false, &sounds.find(name)->second.first);
        }
        else if (paused) {
            FMOD_Channel_SetPaused(sounds.find(name)->second.first, false);
        } else {
            FMOD_System_PlaySound(system, sounds.find(name)->second.second, 0, false, &sounds.find(name)->second.first);
        }
        FMOD_Channel_AddDSP(sounds.find(name)->second.first, FMOD_CHANNELCONTROL_DSP_HEAD, dsp);
        time.restart();
    }


    void pause_song(const char *name) {
        FMOD_Channel_SetPaused(sounds.find(name)->second.first, true);
    }

    void toggle_play(const char *name) {
        FMOD_BOOL paused = false;
        FMOD_Channel_GetPaused(sounds.find(name)->second.first, &paused);
        if (paused) {
            play_song(name);
        } else {
            pause_song(name);
        }
    }

    void update() {
        FMOD_System_Update(system);
        bool beatDetected = false;
        FMOD_DSP_PARAMETER_FFT *fft;
//        FMOD_DSP_SetParameterFloat(dsp, FMOD_DSP_FFT_WINDOW_HAMMING, 64);
        FMOD_DSP_GetParameterData(dsp, FMOD_DSP_FFT_SPECTRUMDATA, (void **) &fft, 0, 0, 0);
        for (int i = 0; i < 2; i++) {
            for (int bin = 0; bin < fft->length; bin++) {
                samples[i][bin] = fft->spectrum[i][bin];
            }
        }
        for (int i = 0; i < 64; i++) {
            spec[i] = (samples[0][i] + samples[1][i]) / 2;
        }
        // Find max volume
        auto maxIterator = std::max_element(&spec[0], &spec[64]);
        float maxVol = *maxIterator;
        // Normalize
        if (maxVol != 0)
            std::transform(&spec[0], &spec[64], &spec[0], [maxVol](float dB) -> float { return dB / maxVol; });
        set_peak(*maxIterator * 10000);
        float hzRange = (44100 / 2) / int(64);
        // Detect beat if normalization disabled1
        if (spec[beatThresholdBar] >= beatThresholdVolume && beatLastTick == 0 && beatIgnoreLastTick == 0) {
            beatLastTick = tick.getElapsedTime().asMilliseconds();
            beatTimes.push(beatLastTick);

            while (tick.getElapsedTime().asMilliseconds() - beatTimes.front() > beatTrackCutoff) {
                beatTimes.pop();
                if (beatTimes.size() == 0)
                    break;
            }
        }

        if (tick.getElapsedTime().asMilliseconds() - beatLastTick < beatSustain) {
            beat = true;
        }


        else if (beatIgnoreLastTick == 0 && beatLastTick != 0) {
            beatLastTick = 0;
            beatIgnoreLastTick = tick.getElapsedTime().asMilliseconds();
        }

        if (tick.getElapsedTime().asMilliseconds() - beatIgnoreLastTick >= beatPostIgnore) {
            beatIgnoreLastTick = 0;
        }

        // Predict BPM
        float msPerBeat, bpmEstimate;

        if (beatTimes.size() >= 2) {
            msPerBeat = (beatTimes.back() - beatTimes.front()) / static_cast<float>(beatTimes.size() - 1);
            bpmEstimate = 60000 / msPerBeat;
        }
        else {
            bpmEstimate = 0;
        }
        std::cout << "BPM: " << bpmEstimate << "\t" << "1: " << spec[0] << "\t 2: " << spec[1] << "\t3: " << spec[2] << "\n";
        if (test.getElapsedTime().asMilliseconds() > 250) {
            beat = false;
            test.restart();
        }
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
