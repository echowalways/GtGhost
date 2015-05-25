import QtQuick 2.4
import GtGhost 1.0

TestFrame {

    GhostUnitTest {

        GhostTree {
            id: ghostTree1

            ActionItem {
                id: action1

                onExecute: setSuccessStatus()
            }

            onStarted: {
                console.debug("started")
            }

            onFinished: {
                console.debug("finished")
            }

            onStopped: {
                console.debug("stopped")
            }
        }

        Component.onCompleted: {
            addStatus(ghostTree1, Ghost.Running)
            addStatus(action1, Ghost.Running)
            addStatus(action1, Ghost.Success)
            addStatus(ghostTree1, Ghost.Success)

            ghostTree1.start()
        }
    }

    GhostUnitTest {

        GhostTree {
            id: ghostTree2

            ActionItem {
                id: action2

                onExecute: setFailureStatus()
            }

            onStarted: {
                console.debug("started")
            }

            onFinished: {
                console.debug("finished")
            }

            onStopped: {
                console.debug("stopped")
            }
        }

        Component.onCompleted: {
            addStatus(ghostTree2, Ghost.Running)
            addStatus(action2, Ghost.Running)
            addStatus(action2, Ghost.Failure)
            addStatus(ghostTree2, Ghost.Failure)

            ghostTree2.start()
        }
    }

    Timer {
        id: stopTimer
        interval: 100

        onTriggered: {
            ghostTree3.stop()
        }
    }

    GhostUnitTest {

        GhostTree {
            id: ghostTree3

            ActionItem {
                id: action3

                onTerminate: setStoppedStatus()
            }

            onStarted: {
                console.debug("started")
            }

            onFinished: {
                console.debug("finished")
            }

            onStopped: {
                console.debug("stopped")
            }
        }

        Component.onCompleted: {
            addStatus(ghostTree3, Ghost.Running)
            addStatus(action3, Ghost.Running)
            addStatus(action3, Ghost.Stopped)
            addStatus(ghostTree3, Ghost.Stopped)

            ghostTree3.start()
            stopTimer.start()
        }
    }
}

