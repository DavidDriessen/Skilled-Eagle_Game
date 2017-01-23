//
// Created by endargon on 1/23/17.
//

#include "FmodApi.hpp"

void FmodApi::stop_song(const char *string) {
    sounds.find(string)->second.first->setPosition(0, FMOD_TIMEUNIT_MS);
    sounds.find(string)->second.first->setPaused(1);
}

