import os;
import io;
import sys;
import soundfile as sf

# acceptable file formats
# - wav
# - flac
# - mp3

# for later
# - alac

class File:

    def __init__(self, path: str):
        self.path = path

    def read(self) -> str:
        with open(self.path, 'r') as file:
            return file.read()
        
    def write(self, content: str) -> None:
        with open(self.path, 'w') as file:
            file.write(content)

    def get_path(self) -> str:
        return self.path
    
    def set_path(self, new_path: str) -> None:
        self.path = new_path
        

def convert(file:File, output_file_path:str, format:str) -> File:
    
    try:
        # Read the audio data and sample rate from the WAV file
        in_path = file.get_path()
        print(in_path)
        data, samplerate = sf.read(in_path)

        print("Data: ", data)
        print("SampleRate: ", samplerate)

        # Write the audio data to a new FLAC file
        sf.write(output_file_path, data, samplerate, format=format)

        print(f"Successfully converted '{in_path}' to '{output_file_path}'")
    except Exception as e:
        print(f"Error converting file: {e}")

def main():

    print("Hello, World!");
    file = File("files/testFile.wav")
    convert(file, "files/testFile.mp3", 'MP3')

main()
    