// convert a given audio file of (wav, flac, mp3) types into any one of the other types

// lamejs

async function wav_to_mp3(infile) {

    const audioContext = new (window.AudioContext || window.webkitAudioContext)();
    const arrayBuffer = await wavFile.arrayBuffer();
    const audioBuffer = await audioContext.decodeAudioData(arrayBuffer);

    // Prepare data for Lame.js (e.g., convert to Lame.js compatible format)
    const samples = audioBuffer.getChannelData(0); // assuming mono

    const mp3Encoder = new Lame.Mp3Encoder({
        samplerate: audioContext.sampleRate,
        channels: 1, // or 2 for stereo
        bitrate: 128 // adjust as needed
    });

    const mp3Data = [];
    const blockSize = 1152; // Typical block size for LAME
    for (let i = 0; i < samples.length; i += blockSize) {
        const block = samples.slice(i, i + blockSize);
        const encoded = mp3Encoder.encode(block);
        if (encoded.length > 0) {
            mp3Data.push(encoded);
        }
    }
    const finalMp3 = mp3Encoder.flush();
    if (finalMp3.length > 0) {
        mp3Data.push(finalMp3);
    }

    const mp3Blob = new Blob(mp3Data, { type: 'audio/mp3' });
    return mp3Blob;
}