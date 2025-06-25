#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <winapifamily.h>
// Windows Audio Session API
#include <audioclient.h>
#include <audiopolicy.h>
#include "headers/miniaudio.h"
#include <mmdeviceapi.h>

using namespace std;

class AudioPlayer {

    private:

        FILE *audioFile;
        FILE *configFile;
        // audio output device


        float volume;
        int playbackSpeed; // 0 - 7, (0.25 0.5 0.75 1, 1.25, 1.5 1.75 2)
        bool isPlaying = false;

    public:

        AudioPlayer() { // constructor

        }

        ~AudioPlayer() { // deconstructor

        }

        void StartAudio() { // initially starts the playback of an audio file
    
            PlaySound(TEXT("test_audio.wav"), NULL, SND_FILENAME); // https://learn.microsoft.com/en-us/previous-versions/dd743680(v=vs.85)
        }

        void PauseAudio() { // stops the playback of the audio temporarily, saving the stopped position in the file

        }

        void ResumeAudio() { // resumes the audio playback after the clip has been started

        }

};

int main(int argc, char const *argv[])
{
    
    cout << "Playing Sound!" << endl;
    AudioPlayer *ap = new AudioPlayer();
    ap->StartAudio();
    return 0;
}
