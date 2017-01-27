#ifndef SOUNDMANAGER_H
#define SOUNDMANAGER_H

#include "fmod.h"
#include "iostream"

class SoundManager {
public:
    SoundManager();

    ~SoundManager();

    int load_song(char *argv);

    void play();

    void pause();

    void reset();

    float *get_spectre(int nb_freq); // entry_hz = (44100 / 2) / nb_freq
    int *get_left_data();

    int *get_right_data();

    unsigned int get_length();

    int get_current_time_PCM(); // renvoi le temps en nombre de samples
    void set_current_time(int PCM);

    void change_pitch(float val); // change la vitesse de lecture
    float get_pitch();
    void toggle_play();

    std::string getSoundName() {
        return loadedSoundName;
    }
private:
    FMOD_SYSTEM *system;
    FMOD_SOUND *backgroundMusic;
    FMOD_SOUND *gamePlayMusic;
    FMOD_CHANNEL *channel;

    int *data_left_channel;     // 16 premiers bits
    int *data_right_channel;    // 16 derniers bits
    float *spectre;
    unsigned int length;
    float pitch;
    std::string loadedSoundName;

};

#endif // SOUNDMANAGER_H
