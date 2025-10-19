
#include "player.h"
#include <cstdio>
#include <cmath>

// --- Static callback for native (strict) playback ---
void AudioPlayer::data_callback(ma_device* pDevice, void* pOutput, const void* pInput, ma_uint32 frameCount) {
    ma_decoder* pDecoder = (ma_decoder*)pDevice->pUserData;
    ma_result result = ma_decoder_read_pcm_frames(pDecoder, pOutput, frameCount, NULL);
    (void)result;
    (void)pInput;

    // Apply software volume control if needed
    AudioPlayer* pThis = (AudioPlayer*)pDecoder->pUserData; // set below during play()
    if (pThis && pThis->m_volume != 1.0f) {

        // Scale samples depending on format
        if (pDecoder->outputFormat == ma_format_f32) {
            float* samples = (float*)pOutput;
            size_t total = frameCount * pDecoder->outputChannels;
            for (size_t i = 0; i < total; ++i)
                samples[i] *= pThis->m_volume;
        }
        else if (pDecoder->outputFormat == ma_format_s16) {
            short* samples = (short*)pOutput;
            size_t total = frameCount * pDecoder->outputChannels;
            for (size_t i = 0; i < total; ++i) {
                int scaled = (int)(samples[i] * pThis->m_volume);
                if (scaled > 32767) scaled = 32767;
                else if (scaled < -32768) scaled = -32768;
                samples[i] = (short)scaled;
            }
        }
    }
}
/*
* default constructor
*/
AudioPlayer::AudioPlayer() = default;

/*
* deconstructor
*/
AudioPlayer::~AudioPlayer() {
    stop();
}

/*
* main playback function, determines if the audio engine needs to decode the file into a format supported by the playback device
* 
*/
ma_result AudioPlayer::play(const std::string& filename) {
    stop(); // reset any existing playback
    m_usingEngine = false;
    m_volume = 1.0f;

    printf("Loading: %s\n", filename.c_str());

    // Initialize decoder
    ma_result result = ma_decoder_init_file(filename.c_str(), NULL, &m_decoder);
    if (result != MA_SUCCESS) {
        printf("Failed to load file.\n");
        return result;
    }

    // Attach self pointer for callback volume control
    m_decoder.pUserData = this;

    // Try strict/native playback
    ma_device_config devConfig = ma_device_config_init(ma_device_type_playback);
    devConfig.playback.format   = m_decoder.outputFormat;
    devConfig.playback.channels = m_decoder.outputChannels;
    devConfig.sampleRate        = m_decoder.outputSampleRate;
    devConfig.dataCallback      = data_callback;
    devConfig.pUserData         = &m_decoder;

    result = ma_device_init(NULL, &devConfig, &m_device);
    if (result == MA_SUCCESS) {
        printf("Native playback active: %u ch @ %u Hz\n",
               m_decoder.outputChannels, m_decoder.outputSampleRate);

        m_deviceInitialized = true;
        ma_device_start(&m_device);
        return MA_SUCCESS;
    }

    // Fallback to engine
    printf("Native format unsupported. Falling back to engine.\n");

    result = ma_engine_init(NULL, &m_engine);
    if (result != MA_SUCCESS) {
        printf("Engine initialization failed.\n");
        ma_decoder_uninit(&m_decoder);
        return result;
    }
    m_engineInitialized = true;
    m_usingEngine = true;

    //test loading file with engine
    result = ma_sound_init_from_file(&m_engine, filename.c_str(), 0, NULL, NULL, &m_sound);
    if (result != MA_SUCCESS) {
        printf("Could not load file into engine.\n");
        ma_engine_uninit(&m_engine);
        ma_decoder_uninit(&m_decoder);
        return result;
    }
    //set volume based on default & begin play
    ma_sound_set_volume(&m_sound, m_volume);
    ma_sound_start(&m_sound);


    printf("🎶 Playing via engine fallback.\n");
    return MA_SUCCESS;
}
/*
* pause playback
*/
void AudioPlayer::pause() {
    if (m_usingEngine && m_engineInitialized) {
        ma_sound_stop(&m_sound);
        printf("Paused (engine).\n");
    } else if (m_deviceInitialized) {
        ma_device_stop(&m_device);
        printf("Paused (native).\n");
    }
}
/*
*resume playback
*/
void AudioPlayer::resume() {
    if (m_usingEngine && m_engineInitialized) {
        ma_sound_start(&m_sound);
        printf("Resumed (engine).\n");
    } else if (m_deviceInitialized) {
        ma_device_start(&m_device);
        printf("Resumed (native).\n");
    }
}

/*
*   change the volume, takes in a float
*/
void AudioPlayer::setVolume(float volume) {
    if (volume < 0.0f) volume = 0.0f;
    if (volume > 1.0f) volume = 1.0f;
    m_volume = volume;

    if (m_usingEngine && m_engineInitialized) {
        ma_sound_set_volume(&m_sound, m_volume);
    }

    printf("Volume set to %.2f\n", m_volume);
}


/*
* stop playback if user stops listening to music
*/
void AudioPlayer::stop() {
    if (m_deviceInitialized) {
        ma_device_uninit(&m_device);
        m_deviceInitialized = false;
    }

    if (m_engineInitialized) {
        ma_sound_uninit(&m_sound);
        ma_engine_uninit(&m_engine);
        m_engineInitialized = false;
    }

    ma_decoder_uninit(&m_decoder);
}
