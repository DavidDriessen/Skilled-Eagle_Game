#ifndef SOUNDMANAGER_H
#define SOUNDMANAGER_H

#include <vector>
#include <functional>
#include "fmod.h"
#include "iostream"

enum SOUND_TYPES {
    BACKGROUND,
    GAME_SOUND,
    NONE,
    SPLASH,
    SHOT,
};

struct SOUNDS {
    SOUND_TYPES type;
    FMOD_CHANNEL *channel = nullptr;
    FMOD_SOUND *sound = nullptr;
    std::string path;
    unsigned int length = 0;
    int *left = 0;
    int *right = 0;
    float pitch= 1.f;
};

class SoundManager {
public:
    SoundManager();

    ~SoundManager();


    float *get_spectre(int nb_freq); // entry_hz = (44100 / 2) / nb_freq
    int *get_left_data();

    int *get_right_data();

    unsigned int get_length();


    void change_pitch(float val, SOUND_TYPES t); // change la vitesse de lecture
    float get_pitch(SOUND_TYPES s);

    std::string getSoundName() {
        return loadedSoundName;
    }

    int get_current_time_MS();

    int get_current_time_PCM(SOUND_TYPES s);

    void toggle_play(SOUND_TYPES s);

    void set_current_time(int PCM, SOUND_TYPES s);

    int get_current_time_MS(SOUND_TYPES s);

    void pause(SOUND_TYPES s);

    void reset(SOUND_TYPES s);

    void play(SOUND_TYPES s);

    SOUNDS * get_sound(SOUND_TYPES t);


    void insert_sound(SOUND_TYPES t, std::string path);

    void reload_sound(SOUNDS *s);

    bool getloading();


private:
    FMOD_SYSTEM *system;
    bool loading = false;
    int *data_left_channel;     // 16 premiers bits
    int *data_right_channel;    // 16 derniers bits
    float *spectre;
    unsigned int length;
    float pitch;
    std::vector<SOUNDS> sounds;
    std::string loadedSoundName;
    SOUNDS notFound = {SOUND_TYPES::NONE};

};

#endif // SOUNDMANAGER_H
