#include "SoundManager.h"

#include <cmath>
#include <stdio.h>

using namespace std;

SoundManager::SoundManager()
{
	FMOD_System_Create(&system);
	FMOD_System_Init(system, 1, FMOD_INIT_NORMAL, NULL);
    channel = NULL;
    pitch=1.f;
}

SoundManager::~SoundManager()
{
    FMOD_System_Release(system);
}

int SoundManager::load_song(char *argv)
{
    loadedSoundName = argv;
    /* On ouvre la gamePlayMusic */
	FMOD_System_CreateSound(system, argv, FMOD_2D , 0, &gamePlayMusic);

	/* On active la r�p�tition de la gamePlayMusic � l'infini */
	FMOD_Sound_SetLoopCount(gamePlayMusic, -1);
	FMOD_Sound_GetLength(gamePlayMusic, &length, FMOD_TIMEUNIT_PCM);

	/* on rempli les tableau data_left et data_right avec les donn�es du buffer */
    void* ptr1;
    void* ptr2;             // ???
    unsigned int length1;   // ???
    unsigned int length2;   // ???
    data_left_channel = new int[length];
    data_right_channel = new int[length];
    FMOD_Sound_Lock(gamePlayMusic, 0, length, &ptr1, &ptr2, &length1, &length2);
    for (int i=0 ; i<length ; i++)
    {
        data_left_channel[i] = ((int*)ptr1)[i]>>16;
        data_right_channel[i] = (((int*)ptr1)[i]<<16)>>16;
    }
    FMOD_Sound_Unlock(gamePlayMusic, ptr1, ptr2, length, length2);
    return 0;
}

void SoundManager::play(void)
{
    FMOD_System_PlaySound(system, gamePlayMusic, 0 , 0, NULL);
	FMOD_System_GetChannel(system, 0, &channel);
}

void SoundManager::pause(void)
{
        FMOD_BOOL etat;
        FMOD_Channel_GetPaused(channel, &etat);
        FMOD_Channel_SetFrequency(channel, 44100.f*pitch);
        if (etat == 1) // Si la chanson est en pause
            FMOD_Channel_SetPaused(channel, 0); // On enl�ve la pause
        else // Sinon, elle est en cours de lecture
            FMOD_Channel_SetPaused(channel, 1); // On met en pause
}

void SoundManager::reset(void)
{
    FMOD_Channel_SetPosition(channel, 0, FMOD_TIMEUNIT_PCM);
    FMOD_Channel_SetPaused(channel, 1); // On met en pause
}

int* SoundManager::get_left_data()
{
    return data_left_channel;
}

int* SoundManager::get_right_data()
{
    return data_right_channel;
}

unsigned int SoundManager::get_length()
{
    return length;
}

int SoundManager::get_current_time_PCM()
{
    unsigned int pos=0;
    FMOD_Channel_GetPosition(channel,&pos,FMOD_TIMEUNIT_PCM);
    return pos;
}

int SoundManager::get_current_time_MS()
{
    unsigned int pos=0;
    FMOD_Channel_GetPosition(channel,&pos,FMOD_TIMEUNIT_MS);
    return pos;
}

void SoundManager::set_current_time(int PCM)
{
    FMOD_Channel_SetPosition(channel,PCM,FMOD_TIMEUNIT_PCM);
}

void SoundManager::change_pitch(float val)
{
    pause();
    pitch+=val;
    pause();
}

float SoundManager::get_pitch()
{
    return pitch;
}

void SoundManager::toggle_play() {
    FMOD_BOOL isPlaying = false;
    FMOD_Channel_IsPlaying(channel, &isPlaying);
    if(isPlaying) {
        pause();
    } else {
        play();
    }
}