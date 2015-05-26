import QtQuick 2.2
import GtGhost 1.0

Item {
    id: item

    property var ghostItem: null

//    Rectangle {
//        anchors.fill: parent

//        color: "transparent"

//        border.width: 3
//        border.color: "black"
//    }

    Rectangle {
        id: statusFrameItem

        width: 140
        height: 80

        anchors.horizontalCenter: item.horizontalCenter
        anchors.top: item.top

        color: "#7A7A7A"
        radius: 10

        Rectangle {
            id: statusItem

            anchors.centerIn: parent

            width: parent.width - 20
            height: parent.height - 20
        }

        Text {
            anchors.centerIn: statusFrameItem
            text: ghostItem.comment
            color: "white"
        }
    }

    state: "invalid"

    states: [
        State {
            name: "invalid"

            PropertyChanges { target: statusItem; color: "gray" }
        },
        State {
            name: "standby"

            PropertyChanges { target: statusItem; color: "yellow" }
        },
        State {
            name: "running"

            PropertyChanges { target: statusItem; color: "green" }
        },
        State {
            name: "success"

            PropertyChanges { target: statusItem; color: "blue" }
        },
        State {
            name: "failure"

            PropertyChanges { target: statusItem; color: "red" }
        },
        State {
            name: "stopped"

            PropertyChanges { target: statusItem; color: "black" }
        }
    ]

    Connections {
        target: ghostItem

        onStatusChanged: {
            switch (ghostItem.status) {
            case Ghost.StandBy:
                item.state = "standby"
                break;
            case Ghost.Running:
                item.state = "running"
                break;
            case Ghost.Success:
                item.state = "success"
                break;
            case Ghost.Failure:
                item.state = "failure"
                break
            case Ghost.Stopped:
                item.state = "stopped"
                break
            }
        }
    }
}
