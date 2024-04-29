import QtQuick 2.0

Item {
    property int orientationLock: 0

    id: appWindow
    width: 360
    height: 360

    onOrientationLockChanged: {
            viewer.setOrientation(orientationLock)
    }

    // Loaders for the main application and the splash screen.
    Loader {
        id: mainAppLoader
        width: appWindow.width
        height: appWindow.height
        onLoaded: {
            focus = true
            console.debug("Main application loaded.");
        }
        focus: true
         Keys.onPressed: {
             console.log("Loaded item captured:", event.text);
             event.accepted = true;
         }
    }
    Loader {
        id: splashScreenLoader
        source: Qt.resolvedUrl("SplashScreen.qml");
        anchors.fill: appWindow
    }

    // Timers for starting to load the main application and eventually deleting
    // the splash screen.
    Timer {
        id: firstPhaseTimer
        property int phase: 0
        interval: 500
        running: true
        repeat: false

        onTriggered: {
            if (!mainAppLoader.Loading) {
                console.debug("Starting to load the main application.");
                mainAppLoader.source = Qt.resolvedUrl("Main.qml");
                secondPhaseTimer.start();
            }
        }
    }
    Timer {
        id: secondPhaseTimer
        property int phase: 0
        interval: 200
        running: false
        repeat: true

        onTriggered: {
            if (phase == 0) {
                if (mainAppLoader.Loading) {
                    console.debug("The main application is not loaded yet.");
                    return;
                }

                console.debug("Finishing the splash screen progress bar.");

                if (splashScreenLoader.item) {
                    splashScreenLoader.item.loadingProgress = 1;
                }

                // Set the phase for deletion.
                phase += 1;
            }
            else if (phase == 1) {
                // Hide the splash screen.
                console.debug("Hiding the splash screen.");

                if (splashScreenLoader.item) {
                    splashScreenLoader.item.opacity = 0;
                }

                phase += 1;
            }
            else {
                // Delete the splash screen.
                console.debug("Deleting the splash screen.");

                // By setting the source property to an empty string destroys
                // the loaded item.
                splashScreenLoader.source = "";

                secondPhaseTimer.stop();
            }
        }
    }
}
