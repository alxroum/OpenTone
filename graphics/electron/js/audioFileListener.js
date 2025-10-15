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

function unHandleFile() {
    document.getElementById("file-import").style="display:block"
    document.getElementById("loaded-file").style="display:none"
}

function handleFile(file) {
    // do something with the file when it is determined to be valid
    document.getElementById("file-import").style="display:none"
    var lf = document.getElementById("loaded-file");
    lf.style="display:inline"
    lf.innerHTML = file.name;
}