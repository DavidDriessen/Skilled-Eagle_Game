//
// Created by robbie on 17-1-2017.
//

#ifndef MENU_H
#define MENU_H
#include <iostream>
#include "IState.h"

class MenuState : public IState {
private:

public:
    MenuState();
    void update();
    void draw();
};


#endif //CDOJO_MENU_H
