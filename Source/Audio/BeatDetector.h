#ifndef BEATDETECTOR_H
#define BEATDETECTOR_H

#include <vector>
#include "SoundManager.h"
#include "BeatListener.hpp"

class BeatDetector {
public:
    BeatDetector(SoundManager *snd_mgr, SOUND_TYPES t);

    ~BeatDetector();

    void audio_process();

    float *get_energie1024();

    float *get_energie44100();

    float *get_energie_peak();

    float *get_conv();

    float *get_beat();

    int get_tempo();

    std::vector<std::pair<int, BeatListener *>> listeners;

    void add_listener(BeatListener *l);

    void remove_listener(int id);

    void update(void);

    bool getLoading();

private:
    SoundManager *snd_mgr;
    SOUNDS *sound;
    int length;    // en PCM
    float *energie1024; // energie of 1024 samples computed every 1024 pcm
    float *energie44100; // energie of 44100 samples computed every 1024 pcm
    float *energie_peak; // les beat probables
    float *conv; // la convolution avec un train d'impulsions
    float *beat; // la beat line
    int tempo; // le tempo en BPMs

    int energie(int *data, int offset,
                int window); // calcul l'energie du signal a une position et sur une largeur donn�e
    void normalize(float *signal, int size,
                   float max_val); // reajuste les valeurs d'un signal � la valeur max souhait�e
    int search_max(float *signal, int pos, int fenetre_half_size); // recherche d'un max dans les parages de pos

    bool loading = false;
};

#endif // BEATDETECTOR_H
