import QtQuick 2.0
import QtTest 1.0
import GtGhost 1.0

TestCase {
    id: testCase
    name: "tst_GhostTree"

    /*
        Case 0: 没有子节点的灵魂树是无效的
     */

    GhostTree {
        id: tree_0
    }

    GhostInspector {
        id: inspector_0
        target: tree_0
    }

    function test_case_0() {
        verify(tree_0.status === Ghost.Invalid)

        tree_0.start()
        tree_0.stop()
        tree_0.reset()
        verify(inspector_0.done())

        verify(tree_0.childNodes.length === 0)
    }

    /*
        Case 1: 多个子节点的灵魂树是无效的
     */

    GhostTree {
        id: tree_1

        SequenceNode {
            id: sequ_1_0

            ActionNode {
                id: node_1_0_0
            }

            ActionNode {
                id: node_1_0_1
            }
        }

        SequenceNode {
            id: sequ_1_1

            ActionNode {
                id: node_1_1_0
            }

            ActionNode {
                id: node_1_1_1
            }
        }
    }

    GhostInspector {
        id: inspector_1
        target: tree_1
    }

    function test_case_1() {
        verify(tree_1.status === Ghost.Invalid)

        tree_1.start()
        tree_1.stop()
        tree_1.reset()
        verify(inspector_1.nextStatus(node_1_1_1, Ghost.StandBy))
        verify(inspector_1.nextStatus(node_1_1_0, Ghost.StandBy))
        verify(inspector_1.nextStatus(sequ_1_1, Ghost.StandBy))
        verify(inspector_1.nextStatus(node_1_0_1, Ghost.StandBy))
        verify(inspector_1.nextStatus(node_1_0_0, Ghost.StandBy))
        verify(inspector_1.nextStatus(sequ_1_0, Ghost.StandBy))
        verify(inspector_1.done())

        verify(tree_1.childNodes.length === 2)
        verify(tree_1.childNodes[0] === sequ_1_0)
        verify(tree_1.childNodes[1] === sequ_1_1)
    }

    /*
        Case 2: 测试行为树逻辑(同步测试:成功)
     */

    GhostTree {
        id: tree_2

        SequenceNode {
            id: sequ_2_0

            ActionNode {
                id: node_2_0_0

                onExecute: setSuccess()
            }

            ActionNode {
                id: node_2_0_1

                onExecute: setSuccess()
            }
        }
    }

    GhostInspector {
        id: inspector_2
        target: tree_2
    }

    SignalSpy {
        id: spy_2_started
        target: tree_2
        signalName: "started"
    }

    SignalSpy {
        id: spy_2_finished
        target: tree_2
        signalName: "finished"
    }

    SignalSpy {
        id: spy_2_stopped
        target: tree_2
        signalName: "stopped"
    }

    function test_case_2() {
        verify(tree_2.status === Ghost.StandBy)

        verify(inspector_2.nextStatus(node_2_0_1, Ghost.StandBy))
        verify(inspector_2.nextStatus(node_2_0_0, Ghost.StandBy))
        verify(inspector_2.nextStatus(sequ_2_0, Ghost.StandBy))
        verify(inspector_2.nextStatus(tree_2, Ghost.StandBy))
        verify(inspector_2.done())

        verify(tree_2.childNodes.length === 1)
        verify(tree_2.childNodes[0] === sequ_2_0)

        verify(spy_2_started.count === 0)
        verify(spy_2_finished.count === 0)
        verify(spy_2_stopped.count === 0)

        // 测试
        tree_2.start()

        verify(spy_2_started.count === 1)
        verify(spy_2_finished.count === 1)
        verify(spy_2_stopped.count === 1)

        verify(inspector_2.nextStatus(tree_2, Ghost.Running))
        verify(inspector_2.nextStatus(sequ_2_0, Ghost.Running))
        verify(inspector_2.nextStatus(node_2_0_0, Ghost.Running))
        verify(inspector_2.nextStatus(node_2_0_0, Ghost.Success))
        verify(inspector_2.nextStatus(node_2_0_1, Ghost.Running))
        verify(inspector_2.nextStatus(node_2_0_1, Ghost.Success))
        verify(inspector_2.nextStatus(sequ_2_0, Ghost.Success))
        verify(inspector_2.nextStatus(tree_2, Ghost.Success))
        verify(inspector_2.done())

        // 重置测试
        tree_2.reset()

        verify(inspector_2.nextStatus(node_2_0_1, Ghost.StandBy))
        verify(inspector_2.nextStatus(node_2_0_0, Ghost.StandBy))
        verify(inspector_2.nextStatus(sequ_2_0, Ghost.StandBy))
        verify(inspector_2.nextStatus(tree_2, Ghost.StandBy))
        verify(inspector_2.done())
    }

    /*
        Case 3: 测试行为树逻辑(同步测试:失败)
     */

    GhostTree {
        id: tree_3

        SequenceNode {
            id: sequ_3_0

            ActionNode {
                id: node_3_0_0

                onExecute: setSuccess()
            }

            ActionNode {
                id: node_3_0_1

                onExecute: setSuccess()
            }
        }
    }

    GhostInspector {
        id: inspector_3
        target: tree_3
    }

    SignalSpy {
        id: spy_3_started
        target: tree_3
        signalName: "started"
    }

    SignalSpy {
        id: spy_3_finished
        target: tree_3
        signalName: "finished"
    }

    SignalSpy {
        id: spy_3_stopped
        target: tree_3
        signalName: "stopped"
    }

    function test_case_3() {
        verify(tree_3.status === Ghost.StandBy)

        verify(inspector_3.nextStatus(node_3_0_1, Ghost.StandBy))
        verify(inspector_3.nextStatus(node_3_0_0, Ghost.StandBy))
        verify(inspector_3.nextStatus(sequ_3_0, Ghost.StandBy))
        verify(inspector_3.nextStatus(tree_3, Ghost.StandBy))
        verify(inspector_3.done())

        verify(tree_3.childNodes.length === 1)
        verify(tree_3.childNodes[0] === sequ_3_0)

        verify(spy_3_started.count === 0)
        verify(spy_3_finished.count === 0)
        verify(spy_3_stopped.count === 0)

        // 测试
        tree_3.start()

        verify(spy_3_started.count === 1)
        verify(spy_3_finished.count === 1)
        verify(spy_3_stopped.count === 1)

        verify(inspector_3.nextStatus(tree_3, Ghost.Running))
        verify(inspector_3.nextStatus(sequ_3_0, Ghost.Running))
        verify(inspector_3.nextStatus(node_3_0_0, Ghost.Running))
        verify(inspector_3.nextStatus(node_3_0_0, Ghost.Success))
        verify(inspector_3.nextStatus(node_3_0_1, Ghost.Running))
        verify(inspector_3.nextStatus(node_3_0_1, Ghost.Success))
        verify(inspector_3.nextStatus(sequ_3_0, Ghost.Success))
        verify(inspector_3.nextStatus(tree_3, Ghost.Success))
        verify(inspector_3.done())

        // 重置测试
        tree_3.reset()

        verify(inspector_3.nextStatus(node_3_0_1, Ghost.StandBy))
        verify(inspector_3.nextStatus(node_3_0_0, Ghost.StandBy))
        verify(inspector_3.nextStatus(sequ_3_0, Ghost.StandBy))
        verify(inspector_3.nextStatus(tree_3, Ghost.StandBy))
        verify(inspector_3.done())

        /////////*/////////*/////////*/////////*

        // 测试前置条件不符合
        sequ_3_0.precondition = false

        spy_3_started.clear()
        spy_3_finished.clear()
        spy_3_stopped.clear()

        tree_3.start()

        verify(spy_3_started.count === 1)
        verify(spy_3_finished.count === 1)
        verify(spy_3_stopped.count === 1)

        verify(inspector_3.nextStatus(tree_3, Ghost.Running))
        verify(inspector_3.nextStatus(tree_3, Ghost.Failure))
        verify(inspector_3.done())
    }

    /*
        Case 4: 测试行为树逻辑(异步测试)
     */

    GhostTree {
        id: tree_4

        SequenceNode {
            id: sequ_4_0

            ActionNode {
                id: node_4_0_0
                duration: 100
            }

            ActionNode {
                id: node_4_0_1
                duration: 100
            }
        }
    }

    GhostInspector {
        id: inspector_4
        target: tree_4
    }

    SignalSpy {
        id: spy_4_started
        target: tree_4
        signalName: "started"
    }

    SignalSpy {
        id: spy_4_finished
        target: tree_4
        signalName: "finished"
    }

    SignalSpy {
        id: spy_4_stopped
        target: tree_4
        signalName: "stopped"
    }

    function test_case_4() {
        verify(tree_4.status === Ghost.StandBy)

        verify(inspector_4.nextStatus(node_4_0_1, Ghost.StandBy))
        verify(inspector_4.nextStatus(node_4_0_0, Ghost.StandBy))
        verify(inspector_4.nextStatus(sequ_4_0, Ghost.StandBy))
        verify(inspector_4.nextStatus(tree_4, Ghost.StandBy))
        verify(inspector_4.done())

        verify(tree_4.childNodes.length === 1)
        verify(tree_4.childNodes[0] === sequ_4_0)

        verify(spy_4_started.count === 0)
        verify(spy_4_finished.count === 0)
        verify(spy_4_stopped.count === 0)

        // 测试:成功
        spy_4_started.clear()
        spy_4_finished.clear()
        spy_4_stopped.clear()

        tree_4.start()

        verify(spy_4_started.count === 1)
        verify(spy_4_finished.count === 0)
        verify(spy_4_stopped.count === 0)

        verify(inspector_4.nextStatus(tree_4, Ghost.Running))
        verify(inspector_4.nextStatus(sequ_4_0, Ghost.Running))
        verify(inspector_4.nextStatus(node_4_0_0, Ghost.Running))
        verify(inspector_4.done())

        node_4_0_0.setSuccess()

        verify(spy_4_started.count === 1)
        verify(spy_4_finished.count === 0)
        verify(spy_4_stopped.count === 0)

        verify(inspector_4.nextStatus(node_4_0_0, Ghost.Success))
        verify(inspector_4.nextStatus(node_4_0_1, Ghost.Running))
        verify(inspector_4.done())

        node_4_0_1.setSuccess()

        verify(spy_4_started.count === 1)
        verify(spy_4_finished.count === 1)
        verify(spy_4_stopped.count === 1)

        verify(inspector_4.nextStatus(node_4_0_1, Ghost.Success))
        verify(inspector_4.nextStatus(sequ_4_0, Ghost.Success))
        verify(inspector_4.nextStatus(tree_4, Ghost.Success))
        verify(inspector_4.done())

        // 重置测试
        tree_4.reset()

        verify(inspector_4.nextStatus(node_4_0_1, Ghost.StandBy))
        verify(inspector_4.nextStatus(node_4_0_0, Ghost.StandBy))
        verify(inspector_4.nextStatus(sequ_4_0, Ghost.StandBy))
        verify(inspector_4.nextStatus(tree_4, Ghost.StandBy))
        verify(inspector_4.done())

        // 测试:失败
        spy_4_started.clear()
        spy_4_finished.clear()
        spy_4_stopped.clear()

        tree_4.start()

        verify(spy_4_started.count === 1)
        verify(spy_4_finished.count === 0)
        verify(spy_4_stopped.count === 0)

        verify(inspector_4.nextStatus(tree_4, Ghost.Running))
        verify(inspector_4.nextStatus(sequ_4_0, Ghost.Running))
        verify(inspector_4.nextStatus(node_4_0_0, Ghost.Running))
        verify(inspector_4.done())

        node_4_0_0.setFailure()

        verify(spy_4_started.count === 1)
        verify(spy_4_finished.count === 1)
        verify(spy_4_stopped.count === 1)

        verify(inspector_4.nextStatus(node_4_0_0, Ghost.Failure))
        verify(inspector_4.nextStatus(sequ_4_0, Ghost.Failure))
        verify(inspector_4.nextStatus(tree_4, Ghost.Failure))
        verify(inspector_4.done())

        // 重置测试
        tree_4.reset()

        verify(inspector_4.nextStatus(node_4_0_0, Ghost.StandBy))
        verify(inspector_4.nextStatus(sequ_4_0, Ghost.StandBy))
        verify(inspector_4.nextStatus(tree_4, Ghost.StandBy))
        verify(inspector_4.done())

        /////////*/////////*/////////*/////////*

        // 测试前置条件不符合
        sequ_4_0.precondition = false

        spy_4_started.clear()
        spy_4_finished.clear()
        spy_4_stopped.clear()

        tree_4.start()

        verify(spy_4_started.count === 1)
        verify(spy_4_finished.count === 1)
        verify(spy_4_stopped.count === 1)

        verify(inspector_4.nextStatus(tree_4, Ghost.Running))
        verify(inspector_4.nextStatus(tree_4, Ghost.Failure))
        verify(inspector_4.done())
    }

    /*
        Case 5: 测试行为树逻辑(异步测试:停止)
     */

    GhostTree {
        id: tree_5

        SequenceNode {
            id: sequ_5_0

            ActionNode {
                id: node_5_0_0
                duration: 100
            }

            ActionNode {
                id: node_5_0_1
                duration: 100
            }
        }
    }

    GhostInspector {
        id: inspector_5
        target: tree_5
    }

    SignalSpy {
        id: spy_5_started
        target: tree_5
        signalName: "started"
    }

    SignalSpy {
        id: spy_5_finished
        target: tree_5
        signalName: "finished"
    }

    SignalSpy {
        id: spy_5_stopped
        target: tree_5
        signalName: "stopped"
    }

    function test_case_5() {
        verify(tree_5.status === Ghost.StandBy)

        verify(inspector_5.nextStatus(node_5_0_1, Ghost.StandBy))
        verify(inspector_5.nextStatus(node_5_0_0, Ghost.StandBy))
        verify(inspector_5.nextStatus(sequ_5_0, Ghost.StandBy))
        verify(inspector_5.nextStatus(tree_5, Ghost.StandBy))
        verify(inspector_5.done())

        verify(tree_5.childNodes.length === 1)
        verify(tree_5.childNodes[0] === sequ_5_0)

        verify(spy_5_started.count === 0)
        verify(spy_5_finished.count === 0)
        verify(spy_5_stopped.count === 0)

        // 测试:成功
        spy_5_started.clear()
        spy_5_finished.clear()
        spy_5_stopped.clear()

        tree_5.start()

        verify(spy_5_started.count === 1)
        verify(spy_5_finished.count === 0)
        verify(spy_5_stopped.count === 0)

        verify(inspector_5.nextStatus(tree_5, Ghost.Running))
        verify(inspector_5.nextStatus(sequ_5_0, Ghost.Running))
        verify(inspector_5.nextStatus(node_5_0_0, Ghost.Running))
        verify(inspector_5.done())

        node_5_0_0.setSuccess()

        verify(spy_5_started.count === 1)
        verify(spy_5_finished.count === 0)
        verify(spy_5_stopped.count === 0)

        verify(inspector_5.nextStatus(node_5_0_0, Ghost.Success))
        verify(inspector_5.nextStatus(node_5_0_1, Ghost.Running))
        verify(inspector_5.done())

        tree_5.stop()

        verify(spy_5_started.count === 1)
        verify(spy_5_finished.count === 0)
        verify(spy_5_stopped.count === 1)

        verify(inspector_5.nextStatus(node_5_0_1, Ghost.Stopped))
        verify(inspector_5.nextStatus(sequ_5_0, Ghost.Stopped))
        verify(inspector_5.nextStatus(tree_5, Ghost.Stopped))
        verify(inspector_5.done())

        // 重置测试
        tree_5.reset()

        verify(inspector_5.nextStatus(node_5_0_1, Ghost.StandBy))
        verify(inspector_5.nextStatus(node_5_0_0, Ghost.StandBy))
        verify(inspector_5.nextStatus(sequ_5_0, Ghost.StandBy))
        verify(inspector_5.nextStatus(tree_5, Ghost.StandBy))
        verify(inspector_5.done())
    }
}
