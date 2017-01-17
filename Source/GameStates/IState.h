//
// Created by robbie on 17-1-2017.
//

#ifndef CDOJO_ISTATE_H
#define CDOJO_ISTATE_H
#include <iostream>
// Game use state pattern. Each state of the game requires update and draw method.
class IState {
public:
    virtual void update() = 0;
    virtual void draw() = 0;
};


#endif //CDOJO_ISTATE_H
