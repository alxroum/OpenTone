#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <winapifamily.h>
// Windows Audio Session API
#include <audioclient.h>
#include <audiopolicy.h>
#include "headers/miniaudio.h"
#include <mmdeviceapi.h>


#define REFTIMES_PER_SEC  10000000
#define REFTIMES_PER_MILLISEC  10000

#define EXIT_ON_ERROR(hres)  \
              if (FAILED(hres)) { goto Exit; }
#define SAFE_RELEASE(punk)  \
              if ((punk) != NULL)  \
                { (punk)->Release(); (punk) = NULL; }

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
        AudioPlayer(/* args */) { // constructor
            
        }
        ~AudioPlayer() { // deconstructor (unallocate memory)

        }

        const CLSID CLSID_MMDeviceEnumerator = __uuidof(MMDeviceEnumerator);
        const IID IID_IMMDeviceEnumerator = __uuidof(IMMDeviceEnumerator);
        const IID IID_IAudioClient = __uuidof(IAudioClient);
        const IID IID_IAudioRenderClient = __uuidof(IAudioRenderClient);

        HRESULT PlayAudioStream(MyAudioSource *pMySource)
        {
            HRESULT hr;
            REFERENCE_TIME hnsRequestedDuration = REFTIMES_PER_SEC;
            REFERENCE_TIME hnsActualDuration;
            IMMDeviceEnumerator *pEnumerator = NULL;
            IMMDevice *pDevice = NULL;
            IAudioClient *pAudioClient = NULL;
            IAudioRenderClient *pRenderClient = NULL;
            WAVEFORMATEX *pwfx = NULL;
            UINT32 bufferFrameCount;
            UINT32 numFramesAvailable;
            UINT32 numFramesPadding;
            BYTE *pData;
            DWORD flags = 0;

            hr = CoCreateInstance(
                CLSID_MMDeviceEnumerator, NULL,
                CLSCTX_ALL, IID_IMMDeviceEnumerator,
                (void**)&pEnumerator);
            EXIT_ON_ERROR(hr)

            hr = pEnumerator->GetDefaultAudioEndpoint(
                                eRender, eConsole, &pDevice);
            EXIT_ON_ERROR(hr)

            hr = pDevice->Activate(
                            IID_IAudioClient, CLSCTX_ALL,
                            NULL, (void**)&pAudioClient);
            EXIT_ON_ERROR(hr)

            hr = pAudioClient->GetMixFormat(&pwfx);
            EXIT_ON_ERROR(hr)

            hr = pAudioClient->Initialize(
                                AUDCLNT_SHAREMODE_SHARED,
                                0,
                                hnsRequestedDuration,
                                0,
                                pwfx,
                                NULL);
            EXIT_ON_ERROR(hr)

            // Tell the audio source which format to use.
            hr = pMySource->SetFormat(pwfx);
            EXIT_ON_ERROR(hr)

            // Get the actual size of the allocated buffer.
            hr = pAudioClient->GetBufferSize(&bufferFrameCount);
            EXIT_ON_ERROR(hr)

            hr = pAudioClient->GetService(
                                IID_IAudioRenderClient,
                                (void**)&pRenderClient);
            EXIT_ON_ERROR(hr)

            // Grab the entire buffer for the initial fill operation.
            hr = pRenderClient->GetBuffer(bufferFrameCount, &pData);
            EXIT_ON_ERROR(hr)

            // Load the initial data into the shared buffer.
            hr = pMySource->LoadData(bufferFrameCount, pData, &flags);
            EXIT_ON_ERROR(hr)

            hr = pRenderClient->ReleaseBuffer(bufferFrameCount, flags);
            EXIT_ON_ERROR(hr)

            // Calculate the actual duration of the allocated buffer.
            hnsActualDuration = (double)REFTIMES_PER_SEC *
                                bufferFrameCount / pwfx->nSamplesPerSec;

            hr = pAudioClient->Start();  // Start playing.
            EXIT_ON_ERROR(hr)

            // Each loop fills about half of the shared buffer.
            while (flags != AUDCLNT_BUFFERFLAGS_SILENT)
            {
                // Sleep for half the buffer duration.
                Sleep((DWORD)(hnsActualDuration/REFTIMES_PER_MILLISEC/2));

                // See how much buffer space is available.
                hr = pAudioClient->GetCurrentPadding(&numFramesPadding);
                EXIT_ON_ERROR(hr)

                numFramesAvailable = bufferFrameCount - numFramesPadding;

                // Grab all the available space in the shared buffer.
                hr = pRenderClient->GetBuffer(numFramesAvailable, &pData);
                EXIT_ON_ERROR(hr)

                // Get next 1/2-second of data from the audio source.
                hr = pMySource->LoadData(numFramesAvailable, pData, &flags);
                EXIT_ON_ERROR(hr)

                hr = pRenderClient->ReleaseBuffer(numFramesAvailable, flags);
                EXIT_ON_ERROR(hr)
            }

            // Wait for last data in buffer to play before stopping.
            Sleep((DWORD)(hnsActualDuration/REFTIMES_PER_MILLISEC/2));

            hr = pAudioClient->Stop();  // Stop playing.
            EXIT_ON_ERROR(hr)

        Exit:
            CoTaskMemFree(pwfx);
            SAFE_RELEASE(pEnumerator)
            SAFE_RELEASE(pDevice)
            SAFE_RELEASE(pAudioClient)
            SAFE_RELEASE(pRenderClient)

            return hr;
        }
};


class MyAudioSource {

    private:


    public:

        HRESULT LoadData(unsigned int uint32, unsigned char *byte, DWORD *dword) {

        }

        HRESULT SetFormat(WAVEFORMATEX *wav) {

        }
};

int main(int argc, char const *argv[])
{
    
    cout << "Hello, World!" << endl;
    return 0;
}
