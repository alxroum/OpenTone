// manages active file in the 

var file_status = document.getElementById("file-status");
file_status.innerHTML = "test";

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
    console.log("removing file");
}