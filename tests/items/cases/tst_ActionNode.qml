import QtQuick 2.0
import QtTest 1.0
import GtGhost 1.0

TestCase {
    name: "ActionNode"

    GhostTree {
        id: ghostTree

        RepeaterNode {
            loopCount: 5
            ActionNode {
                onExecute: setSuccessStatus()
            }
        }
    }

    function test_1() {
    }

    Component.onCompleted: {
        ghostTree.start()
    }
}
