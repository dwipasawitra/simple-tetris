#include "main.h"

// Game music interface
class music
{
private:
    MIDI *midi[MUSIC_TOTAL_NUM];

public:
    music();
    ~music();
    void playMusic(int selectedMidi);
    void stopMusic();
    void pauseMusic();
    void resumeMusic();
};
