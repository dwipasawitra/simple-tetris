#include "music.h"

music::music()
{
    // Load all kind of music file
    this->midi[MUSIC_NUM_1] = load_midi("music.mid");

}

void music::playMusic(int musicNum)
{
    play_midi(midi[musicNum], 1);
}

void music::stopMusic(int stopMusic)
{
    // Not implemented yet
}
