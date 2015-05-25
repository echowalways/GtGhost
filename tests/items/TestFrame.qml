import QtQuick 2.4

Item {
    Timer {
        id: timer
        interval: 1000

        onTriggered: {
            Qt.quit()
        }
    }

    Component.onCompleted: {
        timer.start()
    }
}
