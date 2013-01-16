#include "music.h"

music::music()
{
    // Load all kind of music file
    this->midi[MUSIC_NUM_1] = load_midi("music.mid");

}

void music::playMusic(int selectedMidi)
{
    play_midi(midi[selectedMidi], 1);
}

void music::stopMusic()
{
    stop_midi();
}

void music::pauseMusic()
{
    midi_pause();
}

void music::resumeMusic()
{
    midi_resume();
}

music::~music()
{
    destroy_midi(this->midi[MUSIC_NUM_1]);
}
