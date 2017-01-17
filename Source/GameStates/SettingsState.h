//
// Created by robbie on 17-1-2017.
//

#ifndef CDOJO_SETTINGSSTATE_H
#define CDOJO_SETTINGSSTATE_H
#include "IState.h"
class SettingsState : public IState {
private:

public:
    SettingsState();
    void update();
    void draw();
};


#endif //CDOJO_SETTINGSSTATE_H
