import QtQuick 2.0
import QtTest 1.0
import GtGhost 1.0

TestCase {
    name: "ActionNode"

    // 验证属性正确性
    GhostTree {
        id: tree0

        ActionNode {
            id: node0
        }
    }

    function test_properties() {
        compare(node0.precondition, undefined)
        node0.precondition = true
        compare(node0.precondition, true)
        node0.precondition = undefined
        compare(node0.precondition, undefined)

        compare(node0.weight, undefined)
        node0.weight = 5
        compare(node0.weight, 5)
        node0.weight = undefined
        compare(node0.weight, undefined)

        compare(node0.duration, 0)
        node0.duration = 1
        compare(node0.duration, 1)
        node0.duration = 0
        compare(node0.duration, 0)
        node0.duration = -1
        compare(node0.duration, 0)
    }

    /// 验证同步执行

    // 测试 Success 状态
    GhostTree {
        id: tree1

        ActionNode {
            id: node1

            onExecute: setSuccessStatus()
        }
    }

    GhostInspector {
        id: inspector1
        target: tree1
    }

    function test_synchronous_1() {
        tree1.start()

        wait(100)

        verify(inspector1.nextStatus(node1, Ghost.StandBy))
        verify(inspector1.nextStatus(tree1, Ghost.StandBy))
        verify(inspector1.nextStatus(tree1, Ghost.Running))
        verify(inspector1.nextStatus(node1, Ghost.Running))
        verify(inspector1.nextStatus(node1, Ghost.Success))
        verify(inspector1.nextStatus(tree1, Ghost.Success))

        verify(inspector1.done())
    }

    // 测试 Failure 状态
    GhostTree {
        id: tree2

        ActionNode {
            id: node2

            onExecute: setFailureStatus()
        }
    }

    GhostInspector {
        id: inspector2
        target: tree2
    }

    function test_synchronous_2() {
        tree2.start()

        wait(100)

        verify(inspector2.nextStatus(node2, Ghost.StandBy))
        verify(inspector2.nextStatus(tree2, Ghost.StandBy))
        verify(inspector2.nextStatus(tree2, Ghost.Running))
        verify(inspector2.nextStatus(node2, Ghost.Running))
        verify(inspector2.nextStatus(node2, Ghost.Failure))
        verify(inspector2.nextStatus(tree2, Ghost.Failure))

        verify(inspector2.done())
    }

    // 测试 Stopped 状态
//    GhostTree {
//        id: tree3

//        ActionNode {
//            id: node3

//            onExecute: setStoppedStatus()
//        }
//    }

//    GhostInspector {
//        id: inspector3
//        target: tree3
//    }

//    function test_synchronous_3() {
//        tree3.start()

//        wait(100)

//        verify(inspector3.nextStatus(node3, Ghost.StandBy))
//        verify(inspector3.nextStatus(tree3, Ghost.StandBy))
//        verify(inspector3.nextStatus(tree3, Ghost.Running))
//        verify(inspector3.nextStatus(node3, Ghost.Running))
//        verify(inspector3.nextStatus(node3, Ghost.Stopped))
//        verify(inspector3.nextStatus(tree3, Ghost.Stopped))

//        verify(inspector3.done())
//    }

    /// 验证异步执行

    // 测试成功的异步
    Timer {
        id: timer4
        interval: 150
        repeat: false

        onTriggered: node4.setSuccessStatus()
    }

    GhostTree {
        id: tree4

        ActionNode {
            id: node4

            onExecute: timer4.start()
        }
    }

    GhostInspector {
        id: inspector4
        target: tree4
    }

    function test_asynchronous_4() {
        tree4.start()

        wait(100)

        verify(inspector4.nextStatus(node4, Ghost.StandBy))
        verify(inspector4.nextStatus(tree4, Ghost.StandBy))
        verify(inspector4.nextStatus(tree4, Ghost.Running))
        verify(inspector4.nextStatus(node4, Ghost.Running))

        verify(inspector4.done())

        wait(100)

        verify(inspector4.nextStatus(node4, Ghost.Success))
        verify(inspector4.nextStatus(tree4, Ghost.Success))

        verify(inspector4.done())
    }

    // 测试超时的异步
    GhostTree {
        id: tree5

        ActionNode {
            id: node5
            duration: 150

            onExecute: {
                // nothing to do.

                Blackboard.set("fff", "33")
            }
        }
    }

    GhostInspector {
        id: inspector5
        target: tree5
    }

    function test_asynchronous_5() {
        tree5.start()

        wait(100)

        verify(inspector5.nextStatus(node5, Ghost.StandBy))
        verify(inspector5.nextStatus(tree5, Ghost.StandBy))
        verify(inspector5.nextStatus(tree5, Ghost.Running))
        verify(inspector5.nextStatus(node5, Ghost.Running))

        verify(inspector5.done())

        wait(100)

        verify(inspector5.nextStatus(node5, Ghost.Failure))
        verify(inspector5.nextStatus(tree5, Ghost.Failure))

        verify(inspector5.done())
    }

    /// 验证前置条件

    // 测试 bool 前置条件
    GhostTree {
        id: tree6

        ActionNode {
            id: node6
            precondition: true

            onExecute: setSuccessStatus()
        }
    }

    GhostInspector {
        id: inspector6
        target: tree6
    }

    function test_precondition_6() {
        tree6.start()

        wait(100)

        verify(inspector6.nextStatus(node6, Ghost.StandBy))
        verify(inspector6.nextStatus(tree6, Ghost.StandBy))
        verify(inspector6.nextStatus(tree6, Ghost.Running))
        verify(inspector6.nextStatus(node6, Ghost.Running))
        verify(inspector6.nextStatus(node6, Ghost.Success))
        verify(inspector6.nextStatus(tree6, Ghost.Success))

        verify(inspector6.done())

        // 动态修改前置条件
        inspector6.clear();
        node6.precondition = false

        tree6.start()

        wait(100)

        verify(inspector6.nextStatus(tree6, Ghost.Running))
        verify(inspector6.nextStatus(tree6, Ghost.Failure))

        verify(inspector6.done())
    }

    // 测试 function 前置条件
    GhostTree {
        id: tree7

        ActionNode {
            id: node7
            precondition: function() { return true }

            onExecute: setSuccessStatus()
        }
    }

    GhostInspector {
        id: inspector7
        target: tree7
    }

    function test_precondition_7() {
        tree7.start()

        wait(100)

        verify(inspector7.nextStatus(node7, Ghost.StandBy))
        verify(inspector7.nextStatus(tree7, Ghost.StandBy))
        verify(inspector7.nextStatus(tree7, Ghost.Running))
        verify(inspector7.nextStatus(node7, Ghost.Running))
        verify(inspector7.nextStatus(node7, Ghost.Success))
        verify(inspector7.nextStatus(tree7, Ghost.Success))

        verify(inspector7.done())

        // 动态修改前置条件
        inspector7.clear();
        node7.precondition =  function() { return false }

        tree7.start()

        wait(100)

        verify(inspector7.nextStatus(tree7, Ghost.Running))
        verify(inspector7.nextStatus(tree7, Ghost.Failure))

        verify(inspector7.done())
    }

    // 测试 bind 前置条件
    QtObject {
        id: blackboard8

        property int value: 5
    }

    GhostTree {
        id: tree8

        ActionNode {
            id: node8
            precondition: blackboard8.value < 7

            onExecute: setSuccessStatus()
        }
    }

    GhostInspector {
        id: inspector8
        target: tree8
    }

    function test_precondition_8() {
        tree8.start()

        wait(100)

        verify(inspector8.nextStatus(node8, Ghost.StandBy))
        verify(inspector8.nextStatus(tree8, Ghost.StandBy))
        verify(inspector8.nextStatus(tree8, Ghost.Running))
        verify(inspector8.nextStatus(node8, Ghost.Running))
        verify(inspector8.nextStatus(node8, Ghost.Success))
        verify(inspector8.nextStatus(tree8, Ghost.Success))

        verify(inspector8.done())

        // 动态修改前置条件
        inspector8.clear();
        blackboard8.value = 8

        tree8.start()

        wait(100)

        verify(inspector8.nextStatus(tree8, Ghost.Running))
        verify(inspector8.nextStatus(tree8, Ghost.Failure))

        verify(inspector8.done())
    }

    /// 验证停止操作

    // 测试停止操作
    GhostTree {
        id: tree9

        ActionNode {
            id: node9
            duration: 150

            onExecute: { }
        }
    }

    GhostInspector {
        id: inspector9
        target: tree9
    }

    function test_stop_9() {
        tree9.start()

        wait(100)

        verify(inspector9.nextStatus(node9, Ghost.StandBy))
        verify(inspector9.nextStatus(tree9, Ghost.StandBy))
        verify(inspector9.nextStatus(tree9, Ghost.Running))
        verify(inspector9.nextStatus(node9, Ghost.Running))

        verify(inspector9.done())

        tree9.stop()

        wait(100)

        verify(inspector9.nextStatus(node9, Ghost.Stopped))
        verify(inspector9.nextStatus(tree9, Ghost.Stopped))

        verify(inspector9.done())
    }
}
