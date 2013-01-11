#include "main.h"

// Game music interface
class music
{
private:
    MIDI *midi[MUSIC_TOTAL_NUM];

public:
    music();
    void playMusic(int musicNum);
    void stopMusic(int musicNum);
};
