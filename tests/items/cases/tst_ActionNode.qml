import QtQuick 2.0
import QtTest 1.0
import GtGhost 1.0

TestCase {
    name: "ActionNode"

    // 验证属性正确性
    GhostTree {
        id: tree_0

        ActionNode {
            id: node_0
        }
    }

    function test_properties() {
        compare(node_0.duration, 0)
        node_0.duration = 1
        compare(node_0.duration, 1)
        node_0.duration = 0
        compare(node_0.duration, 0)
        node_0.duration = -1
        compare(node_0.duration, 0)
    }

    // 测试 Success 状态(同步执行)
    GhostTree {
        id: tree_1

        ActionNode {
            id: node_1

            onExecute: setSuccessStatus()
        }
    }

    GhostInspector {
        id: inspector_1
        target: tree_1
    }

    function test_synchronous_1() {
        tree_1.start()

        verify(inspector_1.nextStatus(node_1, Ghost.StandBy))
        verify(inspector_1.nextStatus(tree_1, Ghost.StandBy))
        verify(inspector_1.nextStatus(tree_1, Ghost.Running))
        verify(inspector_1.nextStatus(node_1, Ghost.Running))
        verify(inspector_1.nextStatus(node_1, Ghost.Success))
        verify(inspector_1.nextStatus(tree_1, Ghost.Success))
        verify(inspector_1.done())
    }

    // 测试 Failure 状态(同步执行)
    GhostTree {
        id: tree_2

        ActionNode {
            id: node_2

            onExecute: setFailureStatus()
        }
    }

    GhostInspector {
        id: inspector_2
        target: tree_2
    }

    function test_synchronous_2() {
        tree_2.start()

        verify(inspector_2.nextStatus(node_2, Ghost.StandBy))
        verify(inspector_2.nextStatus(tree_2, Ghost.StandBy))
        verify(inspector_2.nextStatus(tree_2, Ghost.Running))
        verify(inspector_2.nextStatus(node_2, Ghost.Running))
        verify(inspector_2.nextStatus(node_2, Ghost.Failure))
        verify(inspector_2.nextStatus(tree_2, Ghost.Failure))
        verify(inspector_2.done())
    }

    // 测试 Success 状态(异步执行)

    GhostTree {
        id: tree_3

        ActionNode {
            id: node_3
            duration: 100
        }
    }

    GhostInspector {
        id: inspector_3
        target: tree_3
    }

    function test_asynchronous_3() {
        tree_3.start()

        verify(inspector_3.nextStatus(node_3, Ghost.StandBy))
        verify(inspector_3.nextStatus(tree_3, Ghost.StandBy))
        verify(inspector_3.nextStatus(tree_3, Ghost.Running))
        verify(inspector_3.nextStatus(node_3, Ghost.Running))
        verify(inspector_3.done())

        node_3.setSuccessStatus()

        verify(inspector_3.nextStatus(node_3, Ghost.Success))
        verify(inspector_3.nextStatus(tree_3, Ghost.Success))

        verify(inspector_3.done())
    }

    // 测试 Failure 状态(异步执行)

    GhostTree {
        id: tree_4

        ActionNode {
            id: node_4
            duration: 100
        }
    }

    GhostInspector {
        id: inspector_4
        target: tree_4
    }

    function test_asynchronous_4() {
        tree_4.start()

        verify(inspector_4.nextStatus(node_4, Ghost.StandBy))
        verify(inspector_4.nextStatus(tree_4, Ghost.StandBy))
        verify(inspector_4.nextStatus(tree_4, Ghost.Running))
        verify(inspector_4.nextStatus(node_4, Ghost.Running))
        verify(inspector_4.done())

        node_4.setFailureStatus()

        verify(inspector_4.nextStatus(node_4, Ghost.Failure))
        verify(inspector_4.nextStatus(tree_4, Ghost.Failure))

        verify(inspector_4.done())
    }

    // 测试超时的状态
    GhostTree {
        id: tree_5

        ActionNode {
            id: node_5
            duration: 10
        }
    }

    GhostInspector {
        id: inspector_5
        target: tree_5
    }

    function test_asynchronous_5() {
        tree_5.start()

        verify(inspector_5.nextStatus(node_5, Ghost.StandBy))
        verify(inspector_5.nextStatus(tree_5, Ghost.StandBy))
        verify(inspector_5.nextStatus(tree_5, Ghost.Running))
        verify(inspector_5.nextStatus(node_5, Ghost.Running))
        verify(inspector_5.done())

        wait(20)

        verify(inspector_5.nextStatus(node_5, Ghost.Failure))
        verify(inspector_5.nextStatus(tree_5, Ghost.Failure))
        verify(inspector_5.done())
    }

    /// 验证前置条件

    // 测试 bool 前置条件
    GhostTree {
        id: tree_6

        ActionNode {
            id: node_6
            precondition: true
            onExecute: setSuccessStatus()
        }
    }

    GhostInspector {
        id: inspector_6
        target: tree_6
    }

    function test_precondition_6() {
        tree_6.start()

        verify(inspector_6.nextStatus(node_6, Ghost.StandBy))
        verify(inspector_6.nextStatus(tree_6, Ghost.StandBy))
        verify(inspector_6.nextStatus(tree_6, Ghost.Running))
        verify(inspector_6.nextStatus(node_6, Ghost.Running))
        verify(inspector_6.nextStatus(node_6, Ghost.Success))
        verify(inspector_6.nextStatus(tree_6, Ghost.Success))
        verify(inspector_6.done())

        // 动态修改前置条件
        node_6.precondition = false

        tree_6.start()

        verify(inspector_6.nextStatus(tree_6, Ghost.Running))
        verify(inspector_6.nextStatus(tree_6, Ghost.Failure))

        verify(inspector_6.done())
    }

    // 测试 function 前置条件
    GhostTree {
        id: tree_7

        ActionNode {
            id: node_7
            precondition: function() {
                return true
            }
            onExecute: setSuccessStatus()
        }
    }

    GhostInspector {
        id: inspector_7
        target: tree_7
    }

    function test_precondition_7() {
        tree_7.start()

        verify(inspector_7.nextStatus(node_7, Ghost.StandBy))
        verify(inspector_7.nextStatus(tree_7, Ghost.StandBy))
        verify(inspector_7.nextStatus(tree_7, Ghost.Running))
        verify(inspector_7.nextStatus(node_7, Ghost.Running))
        verify(inspector_7.nextStatus(node_7, Ghost.Success))
        verify(inspector_7.nextStatus(tree_7, Ghost.Success))
        verify(inspector_7.done())

        // 动态修改前置条件
        node_7.precondition =  function() { return false }

        tree_7.start()

        verify(inspector_7.nextStatus(tree_7, Ghost.Running))
        verify(inspector_7.nextStatus(tree_7, Ghost.Failure))
        verify(inspector_7.done())
    }

    // 测试 bind 前置条件
    QtObject {
        id: blackboard_8

        property int value: 5
    }

    GhostTree {
        id: tree_8

        ActionNode {
            id: node8
            precondition: blackboard_8.value < 7
            onExecute: setSuccessStatus()
        }
    }

    GhostInspector {
        id: inspector_8
        target: tree_8
    }

    function test_precondition_8() {
        tree_8.start()

        verify(inspector_8.nextStatus(node8, Ghost.StandBy))
        verify(inspector_8.nextStatus(tree_8, Ghost.StandBy))
        verify(inspector_8.nextStatus(tree_8, Ghost.Running))
        verify(inspector_8.nextStatus(node8, Ghost.Running))
        verify(inspector_8.nextStatus(node8, Ghost.Success))
        verify(inspector_8.nextStatus(tree_8, Ghost.Success))
        verify(inspector_8.done())

        // 动态修改前置条件
        blackboard_8.value = 8

        tree_8.start()

        verify(inspector_8.nextStatus(tree_8, Ghost.Running))
        verify(inspector_8.nextStatus(tree_8, Ghost.Failure))
        verify(inspector_8.done())
    }

    /// 验证停止操作

    // 测试停止操作
    GhostTree {
        id: tree_9

        ActionNode {
            id: node_9
            duration: 10
        }
    }

    GhostInspector {
        id: inspector_9
        target: tree_9
    }

    function test_stop_9() {
        tree_9.start()

        verify(inspector_9.nextStatus(node_9, Ghost.StandBy))
        verify(inspector_9.nextStatus(tree_9, Ghost.StandBy))
        verify(inspector_9.nextStatus(tree_9, Ghost.Running))
        verify(inspector_9.nextStatus(node_9, Ghost.Running))
        verify(inspector_9.done())

        tree_9.stop()

        verify(inspector_9.nextStatus(node_9, Ghost.Stopped))
        verify(inspector_9.nextStatus(tree_9, Ghost.Stopped))
        verify(inspector_9.done())
    }
}
