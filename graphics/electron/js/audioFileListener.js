document.addEventListener("DOMContentLoaded", function() {
    var fileInput = document.getElementById("audio-clip"); // reference to the input component
    unHandleFile();

    fileInput.addEventListener("change", function(event) {
        const file = event.target.files[0];

        if(isValidFile(file)) {
            handleFile(file);
        } else {
            alert('Invalid file type. Please choose a valid file (.wav, .flac, .mp3).')
        }
    });
});

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

// what the page should do when a file isn't there or was removed
function unHandleFile() {
    
}

// what the page should do when a file has been selected
function handleFile(file) {
    // do something with the file when it is determined to be valid
}