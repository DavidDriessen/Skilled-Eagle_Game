//
// Created by endargon on 1/23/17.
//

#include "FmodApi.hpp"

void FmodApi::stop_song(const char *string) {
    FMOD_Channel_SetPosition(sounds.find(string)->second.first, 0, FMOD_TIMEUNIT_MS);
    FMOD_Channel_SetPaused(sounds.find(string)->second.first, 1);
}

