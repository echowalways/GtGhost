import QtQuick 2.2
import QtQuick.Window 2.1
import QtQuick.Controls 1.2
import GtGhost 1.0

Window {
    width: 360
    height: 360

    visible: true

    property int itemWidth: 140
    property int itemHeight: 80

    property int itemWidthSpacing: 10
    property int itemHeightSpacing: 10

    Rectangle {
        anchors.fill: parent

        color: "white"
    }

    Column {
        Button {
            text: "Start"
            onClicked: {
                ghostTree.start()
            }
        }

        Button {
            text: "Stop"
            onClicked: {
                ghostTree.stop()
            }
        }

        Button {
            text: "Reset"
            onClicked: {
                ghostTree.reset()
            }
        }
    }

    Item {
        id: view

        GhostTree {
            id: ghostTree
            SequenceItem {
                ActionItem {
                    comment: "test"
                    onExecute: setSuccessStatus()
                }
                ActionItem {
                    onExecute: setSuccessStatus()
                }
                SequenceItem {
                    ActionItem {
                        onExecute: setSuccessStatus()
                    }
                    ActionItem {
                        onExecute: setSuccessStatus()
                    }
                    SequenceItem {
                        ActionItem {
                            onExecute: setSuccessStatus()
                        }
                        ActionItem {
                            onExecute: setFailureStatus()
                        }
                        SequenceItem {
                            ActionItem {
                                onExecute: setSuccessStatus()
                            }
                            ActionItem {
                                onExecute: setSuccessStatus()
                            }
                        }
                    }
                }
            }
        }

        Component.onCompleted: {
            var component = Qt.createComponent("qrc:///VisibleGhostItem.qml")
            if (component.status === Component.Ready) {
                var ghostItem = createGhostItems(ghostTree, view, component)
                ghostItem.x = 100
                ghostItem.y = 100
            }
        }

        function createGhostItems(item, parentItem, component) {
            var ghostItem = component.createObject(parentItem, { "ghostItem": item })
            var twidth = 0;
            var theight = 0;
            for (var i = 0; i < item.childItems.length; ++i) {
                var childItem = item.childItems[i]
                var childGhostItem = createGhostItems(childItem, ghostItem, component)
                childGhostItem.x = twidth
                childGhostItem.y = itemHeight + itemHeightSpacing
                twidth += childGhostItem.width + itemWidthSpacing
            }
            if (item.childItems.length > 0) {
                ghostItem.x = 0
                ghostItem.y = itemHeight + itemHeightSpacing

                ghostItem.width = twidth - itemWidthSpacing
                ghostItem.height = itemHeightSpacing + itemHeight * 2
            } else {
                ghostItem.x = 0
                ghostItem.y = 0
                ghostItem.width = itemWidth
                ghostItem.height = itemHeight
            }

            return ghostItem
        }
    }
}
