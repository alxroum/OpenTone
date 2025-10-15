const { app, BrowserWindow } = require('electron/main')
const path = require('node:path')

function createWindow () {

  const iconPath = path.join(__dirname, 'graphics/img/openToneIcon.png');

  const win = new BrowserWindow({
    width: 800,
    height: 600,
    icon: iconPath,
    webPreferences: {
      preload: path.join(__dirname, 'preload.js'),
      nodeIntegration: true
    }
  })

  win.loadFile('./graphics/electron/html/index.html')
}

app.whenReady().then(() => {
  createWindow()

  app.on('activate', () => {
    if (BrowserWindow.getAllWindows().length === 0) {
      createWindow()
    }
  })
})

// not working right now, but the goal is to prompt the user before closing
app.on('close', async (event) => {
  if (process.platform !== 'darwin') {
    event.preventDefault();
    const response = await dialog.showMessageBox(mainWindow, {
      type: 'question',
      buttons: ['Leave', 'Stay'],
      title: 'Confirm',
      message: 'Are you sure you want to quit? Unsaved data may be lost.',
    });
    if (response.response === 0) { // 'Leave' button is at index 0
      app.destroy(); // Properly destroy the window
    }
  }
});

app.on('window-all-closed', () => {
  if (process.platform !== 'darwin') {
    app.quit();
  }
});