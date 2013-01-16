#include "main.h"

class sound
{
private:
    SAMPLE *soundSample[GAME_SOUND_NUMBER];

public:
    void playSound(int whatSound);

    sound();
    ~sound();

};
