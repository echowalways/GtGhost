import QtQuick 2.2
import GtGhost 1.0

GhostViewItem {
    id: item

    width: 200
    height: 120

    property var ghostItem: null

    Rectangle {
        id: statusFrameItem

        anchors.fill: parent

        color: "#4A4849"
        radius: 6

        border.color: "#36234E"
        border.width: 1

        Rectangle {
            id: nodeType

            anchors.centerIn: parent

            width: parent.width - 20
            height: parent.height - 20

            color: "#03785D"
            radius: 3

            border.color: "#36234E"
            border.width: 1

            Rectangle {
                id: statusItem

                x: 5
                y: 5

                width: 30
                height: 30

                color: "#03785D"
                radius: 2

                border.color: "#36234E"
                border.width: 1
            }

            Text {
                id: itemType

                anchors.verticalCenter: statusItem.verticalCenter
                anchors.left: statusItem.right
                anchors.leftMargin: 5

                font.pixelSize: 12

                color: "white"
            }

            Text {
                anchors.top: statusItem.bottom
                anchors.left: statusItem.left
                anchors.right: nodeType.right
                height: 80

                text: item.target.summarize
                color: "white"
            }
        }
    }

    Component.onCompleted: {
        switch (item.target.nodeType) {
        case Ghost.CompositeNode:
            nodeType.color = "#03785D"
            break;
        case Ghost.DecoratorNode:
            nodeType.color = "#083975"
            break;
        case Ghost.ConditionNode:
            nodeType.color = "#4A4849"
            break;
        case Ghost.ActionNode:
            nodeType.color = "#683FAA"
            break;
        }

        switch (target.itemType) {
        case Ghost.LinearSequenceItem:
            itemType.text = "LinearSequenceItem"
            break;
        case Ghost.LinearSelectorItem:
            itemType.text = "LinearSelectorItem"
            break;
        case Ghost.WeightSequenceItem:
            itemType.text = "WeightSequenceItem"
            break;
        case Ghost.WeightSelectorItem:
            itemType.text = "WeightSelectorItem"
            break;
        case Ghost.RandomSequenceItem:
            itemType.text = "RandomSequenceItem"
            break;
        case Ghost.RandomSelectorItem:
            itemType.text = "RandomSelectorItem"
            break;
        case Ghost.InverterItem:
            itemType.text = "InverterItem"
            break;
        case Ghost.RepeaterItem:
            itemType.text = "RepeaterItem"
            break;
        case Ghost.RepeatUntilSuccessItem:
            itemType.text = "RepeatUntilSuccessItem"
            break;
        case Ghost.RepeatUntilFailureItem:
            itemType.text = "RepeatUntilFailureItem"
            break;
        case Ghost.AlwaysSuccessItem:
            itemType.text = "AlwaysSuccessItem"
            break;
        case Ghost.AlwaysFailureItem:
            itemType.text = "AlwaysFailureItem"
            break;
        case Ghost.ConditionItem:
            itemType.text = "ConditionItem"
            break;
        case Ghost.ActionItem:
            itemType.text = "ActionItem"
            break;
        case Ghost.IdleActionItem:
            itemType.text = "IdleActionItem"
            break;
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
        target: item.target

        onStatusChanged: {
            switch (item.target.status) {
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
