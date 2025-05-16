#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <winapifamily.h>

using namespace std;

class AudioPlayer
{
private:
    FILE audioFile;
    FILE configFile;
    // audio output device
    // volume
    // playback speed
    // playing/paused
    // 
public:
    AudioPlayer(/* args */) { // constructor
        
    }
    ~AudioPlayer() { // deconstructor (unallocate memory)

    }

    void PlayAudio(int startFrame) {

    }
};

int main(int argc, char const *argv[])
{
    
    cout << "Hello, World!" << endl;
    return 0;
}
