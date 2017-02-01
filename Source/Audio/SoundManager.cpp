#include "SoundManager.h"

#include <cmath>
#include <stdio.h>

using namespace std;

SoundManager::SoundManager() {
    FMOD_System_Create(&system);
    FMOD_System_Init(system, 1, FMOD_INIT_NORMAL, NULL);
    pitch = 1.f;
}

SoundManager::~SoundManager() {
    FMOD_System_Release(system);
}

void SoundManager::play(SOUND_TYPES s) {
    FMOD_System_PlaySound(system, get_sound(s)->sound, 0, 0, NULL);
    FMOD_System_GetChannel(system, 0, &get_sound(s)->channel);
    FMOD_Channel_SetFrequency(get_sound(s)->channel, 44100.f * get_sound(s)->pitch);
    FMOD_Channel_SetVolume(get_sound(s)->channel, masterVolume);
}

void SoundManager::pause(SOUND_TYPES s) {
    FMOD_BOOL etat;
    FMOD_Channel_GetPaused(get_sound(s)->channel, &etat);
    FMOD_Channel_SetFrequency(get_sound(s)->channel, 44100.f * get_sound(s)->pitch);
    if (etat == 1) // Si la chanson est en pause
        FMOD_Channel_SetPaused(get_sound(s)->channel, 0); // On enl�ve la pause
    else // Sinon, elle est en cours de lecture
        FMOD_Channel_SetPaused(get_sound(s)->channel, 1); // On met en pause
}

void SoundManager::reset(SOUND_TYPES s) {
    FMOD_Channel_SetPosition(get_sound(s)->channel, 0, FMOD_TIMEUNIT_PCM);
    FMOD_Channel_SetPaused(get_sound(s)->channel, 1); // On met en pause
}

int *SoundManager::get_left_data() {
    return data_left_channel;
}

int *SoundManager::get_right_data() {
    return data_right_channel;
}

unsigned int SoundManager::get_length() {
    return length;
}

int SoundManager::get_current_time_PCM(SOUND_TYPES s) {
    unsigned int pos = 0;
    FMOD_Channel_GetPosition(get_sound(s)->channel, &pos, FMOD_TIMEUNIT_PCM);
    return pos;
}

int SoundManager::get_current_time_MS(SOUND_TYPES s) {
    unsigned int pos = 0;
    FMOD_Channel_GetPosition(get_sound(s)->channel, &pos, FMOD_TIMEUNIT_MS);
    return pos;
}

void SoundManager::set_current_time(int PCM, SOUND_TYPES s) {
    FMOD_Channel_SetPosition(get_sound(s)->channel, PCM, FMOD_TIMEUNIT_PCM);
}

void SoundManager::change_pitch(float val, SOUND_TYPES t) {
    pause(t);
    get_sound(t)->pitch += val;
    pause(t);
}

float SoundManager::get_pitch(SOUND_TYPES s) {
    return get_sound(s)->pitch;
}

void SoundManager::toggle_play(SOUND_TYPES s) {
    FMOD_BOOL isPlaying = false;
    FMOD_Channel_IsPlaying(get_sound(s)->channel, &isPlaying);
    if (isPlaying) {
        pause(s);
    } else {
        play(s);
    }
}

void SoundManager::reload_sound(SOUNDS *s) {
    s->length = 0;
    s->left = 0;
    s->pitch = 1;
    s->sound = nullptr;
    s->channel = 0;
    loading = true;
    loadedSoundName = s->path;
    unsigned int length;
    /* On ouvre la gamePlayMusic */
    FMOD_System_CreateSound(system, s->path.c_str(), FMOD_2D, 0, &s->sound);

    /* On active la repetition de la gamePlayMusic l'infini */
    FMOD_Sound_SetLoopCount(s->sound, -1);
    FMOD_Sound_GetLength(s->sound, &s->length, FMOD_TIMEUNIT_PCM);
    FMOD_Sound_GetLength(s->sound, &s->lengthMS, FMOD_TIMEUNIT_MS);
    /* on rempli les tableau data_left et data_right avec les donn�es du buffer */
    void *ptr1 = nullptr;
    void *ptr2 = nullptr;             // ???
    unsigned int length1 = 0;   // ???
    unsigned int length2 = 0;   // ???
    s->left = new int[s->length];
    FMOD_Sound_Lock(s->sound, 0, s->length, &ptr1, &ptr2, &length1, &length2);
    for (int i = 0; i < s->length; i++) {
        s->left[i] = ((int *) ptr1)[i] >> 16;
    }
    FMOD_Sound_Unlock(s->sound, ptr1, ptr2, s->length, length2);
    loading = false;
}

void SoundManager::insert_sound(SOUND_TYPES t, std::string path) {
    SOUNDS *sound = get_sound(t);
    if (sound->type != SOUND_TYPES::NONE) {
        sound->path = path;
        reload_sound(sound);
    } else {
        FMOD_CHANNEL *c = 0;
        FMOD_SOUND *s = nullptr;
        sounds.push_back({t, c, s, path, 0, 0});
        reload_sound(get_sound(t));
    }
}

SOUNDS *SoundManager::get_sound(SOUND_TYPES t) {
    for (auto &s: sounds) {
        if (s.type == t) {
            return &s;
        }
    }
    return &notFound;

}

bool SoundManager::getloading() {
    return loading;
}

void SoundManager::set_volume(float volume) {
    masterVolume = volume;
    for (auto &s: sounds) {
        FMOD_Channel_SetVolume(s.channel, volume);
    }
}
