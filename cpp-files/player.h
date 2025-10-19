#ifndef AUDIO_PLAYER_H
#define AUDIO_PLAYER_H

#include "miniaudio.h"
#include <string>
/*
* AudioPlayer class, a high-level interface for the GUI to use when doing audio stuff
*
*  AudioPlayer() - constructor
* ~AudioPlayer() - deconstructor

*  ma_result play(filename) tries to playback a file at native, will fallback to engine if not able
*  void stop()              stop playback and release engine/decoder&device
*  void pause()             pauses playback
*  void resume()            resumes playback
*  all functions handle differently depending on playback capabilities
*  has private instances for how the audioplayer is set up & initialized
*/
class AudioPlayer {
public:
    AudioPlayer();
    ~AudioPlayer();

    // Main controls
    ma_result play(const std::string& filename);
    void stop();
    void pause();
    void resume();

    // Volume control (0.0 = silent, 1.0 = normal)
    void setVolume(float volume);
    float getVolume() const { return m_volume; }

    bool isUsingEngine() const { return m_usingEngine; }

private:
    // Static callback for native playback
    static void data_callback(ma_device* pDevice, void* pOutput, const void* pInput, ma_uint32 frameCount);

    ma_decoder m_decoder{};
    ma_device m_device{};
    ma_engine m_engine{};
    ma_sound m_sound{};

    bool m_deviceInitialized = false;
    bool m_engineInitialized = false;
    bool m_usingEngine = false;

    float m_volume = 0.5f; // current playback volume (default is 50%)
};

#endif // AUDIO_PLAYER_H
