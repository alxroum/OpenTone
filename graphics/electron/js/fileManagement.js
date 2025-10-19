// manages active audio file in the app
const fs = require('fs');
const path = require('path');

var file_status = document.getElementById("file-status");
file_status.innerHTML = "test";

// should happen on page reload to clear the tmp
// tmp will contain the converted file exports and should be cleared
function clearTemp() {
    const directory = 'files/tmp';
}

// check if the input file is one of the valid formats
function isValidFile(infile) {
    const allowedTypes = ['.wav', '.flac', '.mp3'];
    const name = infile.name;
    const extension = "." + name.split('.')[1];

    // Check file type
    if (!allowedTypes.includes(extension)) {
        return false;
    }

    return true;
}

// makes sure file is removed from <input> and decides what the page 
// should do when a file isn't there or was removed
function unHandleFile() {
    removeActiveFile();
}

// what the page should do when a file has been selected
function handleFile(file) {
    // do something with the file when it is determined to be valid
    console.log(file.name);
}

function removeActiveFile() {
    var activeFile = document.getElementById("audio-clip");
    activeFile.value = ''; // clear file in the <input> tag
    console.log("removing file");
}