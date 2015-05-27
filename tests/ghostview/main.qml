import QtQuick 2.2
import QtQuick.Window 2.1
import QtQuick.Controls 1.2
import GtGhost 1.0

Window {
    x: 0
    y: 0
    width: 1280
    height: 768

    visible: true

    property int itemWidth: 280
    property int itemHeight: 150

    property int itemWidthSpacing: 10
    property int itemHeightSpacing: 10

    //    Rectangle {
    //        anchors.fill: parent

    //        color: "white"
    //    }



    Flickable {
        id: flickable

        anchors.fill: parent

        //        contentWidth: ghostView.width
        //        contentHeight: ghostView.height

        // interactive: false

        GhostView {
            id: ghostView

            width: 3780
            height: 920

            anchors.fill: parent

            target: ghostTree

            itemDelegate: VisibleGhostItem {}
        }

        Component.onCompleted: {
            contentWidth = 3780
            contentHeight = 920

            console.debug(contentWidth)
        }
    }

    Row {
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

    GhostTree {
        id: ghostTree
        SequenceItem {
            ActionItem {
                summarize: "test"
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
                IdleActionItem {
                    duration: 1000
                }
                SequenceItem {
                    ActionItem {
                        onExecute: setSuccessStatus()
                    }
                    ActionItem {
                        onExecute: setSuccessStatus()
                    }
                    InverterItem {
                        IdleActionItem {
                            duration: 1000
                        }
                    }
                    SequenceItem {
                        ActionItem {
                            onExecute: setSuccessStatus()
                        }
                        ActionItem {
                            onExecute: setSuccessStatus()
                        }
                        IdleActionItem {
                            duration: 1000
                        }
                    }
                }
            }

            IdleActionItem {
                duration: 1000
            }

            SequenceItem {
                ActionItem {
                    onExecute: setSuccessStatus()
                }
                ActionItem {
                    onExecute: setSuccessStatus()
                }
                IdleActionItem {
                    duration: 1000
                }
                SequenceItem {
                    ActionItem {
                        onExecute: setSuccessStatus()
                    }
                    ActionItem {
                        onExecute: setSuccessStatus()
                    }
                    IdleActionItem {
                        duration: 1000
                    }
                    SequenceItem {
                        ActionItem {
                            onExecute: setSuccessStatus()
                        }
                        ActionItem {
                            onExecute: setSuccessStatus()
                        }
                        IdleActionItem {
                            duration: 1000
                        }
                    }
                }
            }
        }
    }
}
