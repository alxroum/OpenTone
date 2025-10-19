// includes event listeners for the main page

// handles the function calls when a file is selected in the 'active file' box
document.addEventListener("DOMContentLoaded", function() {
    var fileInput = document.getElementById("audio-clip"); // reference to the input component

    fileInput.addEventListener("change", function(event) {
        const file = event.target.files[0];

        if(isValidFile(file)) {
            handleFile(file);
        } else {
            alert('Invalid file type. Please choose a valid file (.wav, .flac, .mp3).')
            unHandleFile();
        }
    });
});