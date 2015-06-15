import QtQuick 2.0
import QtTest 1.0
import GtGhost 1.0

TestCase {
    name: "Blackboard"

    GhostTree {
        id: tree0

        SequenceNode {
            ActionNode {
                id: node0_0

                onExecute: {
                    verify(Blackboard.get("1") === undefined)
                    Blackboard.set("1", 5)
                    verify(Blackboard.get("1") === 5)

                    verify(Blackboard.gett("1") === undefined)
                    Blackboard.sett("1", 5)
                    verify(Blackboard.gett("1") === 5)

                    setSuccessStatus()
                }
            }

            ActionNode {
                id: node0_1

                onExecute: {
                    verify(Blackboard.get("1") === undefined)
                    Blackboard.set("1", 5)
                    verify(Blackboard.get("1") === 5)

                    verify(Blackboard.gett("1") === 5)
                    Blackboard.sett("1", undefined)
                    verify(!Blackboard.hast("1"))

                    setSuccessStatus()
                }
            }
        }
    }

    function test_blackboard_0() {
        tree0.start()

        wait(100)

        tree0.reset()
        tree0.start()

        wait(100)
    }
}
