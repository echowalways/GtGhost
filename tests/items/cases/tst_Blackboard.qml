import QtQuick 2.0
import QtTest 1.0
import GtGhost 1.0

TestCase {
    id: testCase
    name: "Blackboard"
    property int counter: 0

    GhostTree {
        id: tree0

        SequenceNode {
            ActionNode {
                id: node0_0

                onExecute: {
                    verify(!Blackboard.has("1"))
                    verify(Blackboard.get("1") === undefined)
                    Blackboard.set("1", 5)
                    verify(Blackboard.has("1"))
                    verify(Blackboard.get("1") === 5)
                    Blackboard.set("1", undefined)
                    verify(!Blackboard.has("1"))

                    // shared blackboard
                    verify(!Blackboard.shared.has("1"))
                    verify(Blackboard.shared.get("1") === undefined)
                    Blackboard.shared.set("1", 5)
                    verify(Blackboard.shared.has("1"))
                    verify(Blackboard.shared.get("1") === 5)

                    setSuccessStatus()
                }
            }

            ActionNode {
                id: node0_1

                onExecute: {
                    verify(!Blackboard.has("1"))
                    verify(Blackboard.get("1") === undefined)
                    Blackboard.set("1", 5)
                    verify(Blackboard.has("1"))
                    verify(Blackboard.get("1") === 5)

                    // ghost tree blackboard
                    verify(Blackboard.shared.has("1"))
                    verify(Blackboard.shared.get("1") === 5)
                    Blackboard.shared.set("1", undefined)
                    verify(!Blackboard.shared.has("1"))
                    verify(Blackboard.shared.get("1") === undefined)

                    // global blackboard
                    if (testCase.counter === 0) {
                        verify(!Blackboard.global.has("1"))
                        verify(Blackboard.global.get("1") === undefined)
                        Blackboard.global.set("1", 5)
                        verify(Blackboard.global.has("1"))
                        verify(Blackboard.global.get("1") === 5)
                    } else if (testCase.counter === 1) {
                        verify(!Blackboard.global.has("1"))
                        verify(Blackboard.global.get("1") === undefined)
                    }
                    ++testCase.counter

                    setSuccessStatus()
                }
            }
        }
    }

    GhostTree {
        id: tree1

        SequenceNode {
            ActionNode {
                id: node1_0

                onExecute: {
                    verify(!Blackboard.has("1"))
                    verify(Blackboard.get("1") === undefined)
                    Blackboard.set("1", 5)
                    verify(Blackboard.has("1"))
                    verify(Blackboard.get("1") === 5)

                    // shared blackboard
                    verify(!Blackboard.shared.has("1"))
                    verify(Blackboard.shared.get("1") === undefined)
                    Blackboard.shared.set("1", 5)
                    verify(Blackboard.shared.has("1"))
                    verify(Blackboard.shared.get("1") === 5)

                    setSuccessStatus()
                }
            }

            ActionNode {
                id: node1_1

                onExecute: {
                    verify(!Blackboard.has("1"))
                    verify(Blackboard.get("1") === undefined)
                    Blackboard.set("1", 5)
                    verify(Blackboard.has("1"))
                    verify(Blackboard.get("1") === 5)

                    // shared blackboard
                    verify(Blackboard.shared.has("1"))
                    verify(Blackboard.shared.get("1") === 5)
                    Blackboard.shared.set("1", undefined)
                    verify(!Blackboard.shared.has("1"))
                    verify(Blackboard.shared.get("1") === undefined)

                    // global blackboard
                    verify(Blackboard.global.has("1"))
                    verify(Blackboard.global.get("1") === 5)
                    Blackboard.global.set("1", undefined)
                    verify(!Blackboard.global.has("1"))
                    verify(Blackboard.global.get("1") === undefined)

                    setSuccessStatus()
                }
            }
        }
    }

    function test_blackboard_0() {
        tree0.start()
        tree1.start()
        tree0.reset()
        tree0.start()
    }
}
