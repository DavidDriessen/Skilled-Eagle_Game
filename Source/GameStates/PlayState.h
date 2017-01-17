//
// Created by robbie on 17-1-2017.
//

#ifndef CDOJO_GAME_H
#define CDOJO_GAME_H
#include "IState.h"
#include <iostream>
class PlayState : public IState {
private:

public:
    PlayState();
    void update();
    void draw();
};


#endif //CDOJO_GAME_H
