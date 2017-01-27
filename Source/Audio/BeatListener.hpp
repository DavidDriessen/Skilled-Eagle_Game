//
// Created by endargon on 1/25/17.
//

#ifndef SKILLED_EAGLE_GAME_BEATLISTENER_HPP
#define SKILLED_EAGLE_GAME_BEATLISTENER_HPP
class BeatListener {
public:
    virtual void onBeat() = 0;
    virtual void onPeak(float peak) = 0;
};
#endif //SKILLED_EAGLE_GAME_BEATLISTENER_HPP
