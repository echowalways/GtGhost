import QtQuick 2.0
import QtTest 1.0
import GtGhost 1.0

TestCase {
    id: testCase
    name: "Blackboard"
    property int counter: 0

    GhostTree {
        id: tree_0

        SequenceNode {
            ActionNode {
                onExecute: {
                    // 验证节点域
                    verify(!Blackboard.has("1"))
                    verify(Blackboard.get("1") === undefined)
                    Blackboard.set("1", 5)
                    verify(Blackboard.has("1"))
                    verify(Blackboard.get("1") === 5)
                    Blackboard.set("1", undefined)
                    verify(!Blackboard.has("1"))
                    Blackboard.set("1", 5)
                    verify(Blackboard.has("1"))
                    Blackboard.unset("1")
                    verify(!Blackboard.has("1"))

                    // 验证共享域
                    verify(!Blackboard.shared.has("1"))
                    verify(Blackboard.shared.get("1") === undefined)
                    Blackboard.shared.set("1", 5)
                    verify(Blackboard.shared.has("1"))
                    verify(Blackboard.shared.get("1") === 5)

                    setSuccess()
                }
            }

            ActionNode {
                onExecute: {
                    // 验证节点域
                    verify(!Blackboard.has("1"))
                    verify(Blackboard.get("1") === undefined)
                    Blackboard.set("1", 5)
                    verify(Blackboard.has("1"))
                    verify(Blackboard.get("1") === 5)
                    Blackboard.set("1", undefined)
                    verify(!Blackboard.has("1"))
                    Blackboard.set("1", 5)
                    verify(Blackboard.has("1"))
                    Blackboard.unset("1")
                    verify(!Blackboard.has("1"))

                    // 验证共享域
                    verify(Blackboard.shared.has("1"))
                    verify(Blackboard.shared.get("1") === 5)
                    Blackboard.shared.set("1", undefined)
                    verify(!Blackboard.shared.has("1"))
                    Blackboard.shared.set("1", 5)
                    verify(Blackboard.shared.has("1"))
                    Blackboard.shared.unset("1")
                    verify(!Blackboard.shared.has("1"))

                    // 验证全局域
                    if (testCase.counter === 0) {
                        verify(!Blackboard.global.has("1"))
                        verify(Blackboard.global.get("1") === undefined)
                        Blackboard.global.set("1", 5)
                        verify(Blackboard.global.has("1"))
                        verify(Blackboard.global.get("1") === 5)
                    } else if (testCase.counter === 1) {
                        verify(!Blackboard.global.has("1"))
                        verify(Blackboard.global.get("1") === undefined)
                        Blackboard.global.set("1", 5)
                        verify(Blackboard.global.has("1"))
                        Blackboard.global.unset("1")
                        verify(!Blackboard.global.has("1"))
                    }
                    ++testCase.counter

                    setSuccess()
                }
            }
        }
    }

    GhostTree {
        id: tree_1

        SequenceNode {
            ActionNode {
                onExecute: {
                    // 验证节点域
                    verify(!Blackboard.has("1"))
                    verify(Blackboard.get("1") === undefined)
                    Blackboard.set("1", 5)
                    verify(Blackboard.has("1"))
                    verify(Blackboard.get("1") === 5)
                    Blackboard.set("1", undefined)
                    verify(!Blackboard.has("1"))
                    Blackboard.set("1", 5)
                    verify(Blackboard.has("1"))
                    Blackboard.unset("1")
                    verify(!Blackboard.has("1"))

                    // 验证共享域
                    verify(!Blackboard.shared.has("1"))
                    verify(Blackboard.shared.get("1") === undefined)
                    Blackboard.shared.set("1", 5)
                    verify(Blackboard.shared.has("1"))
                    verify(Blackboard.shared.get("1") === 5)

                    setSuccess()
                }
            }

            ActionNode {
                onExecute: {
                    // 验证节点域
                    verify(!Blackboard.has("1"))
                    verify(Blackboard.get("1") === undefined)
                    Blackboard.set("1", 5)
                    verify(Blackboard.has("1"))
                    verify(Blackboard.get("1") === 5)
                    Blackboard.set("1", undefined)
                    verify(!Blackboard.has("1"))
                    Blackboard.set("1", 5)
                    verify(Blackboard.has("1"))
                    Blackboard.unset("1")
                    verify(!Blackboard.has("1"))

                    // 验证共享域
                    verify(Blackboard.shared.has("1"))
                    verify(Blackboard.shared.get("1") === 5)
                    Blackboard.shared.set("1", undefined)
                    verify(!Blackboard.shared.has("1"))
                    Blackboard.shared.set("1", 5)
                    verify(Blackboard.shared.has("1"))
                    Blackboard.shared.unset("1")
                    verify(!Blackboard.shared.has("1"))

                    // 验证全局域
                    verify(Blackboard.global.has("1"))
                    verify(Blackboard.global.get("1") === 5)
                    Blackboard.global.set("1", undefined)
                    verify(!Blackboard.global.has("1"))
                    verify(Blackboard.global.get("1") === undefined)

                    setSuccess()
                }
            }
        }
    }

    function test_blackboard_0() {
        tree_0.start()
        tree_1.start()
        tree_0.reset()
        tree_0.start()
    }
}
