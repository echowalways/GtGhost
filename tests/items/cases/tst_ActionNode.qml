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
            comment: "node0"
        }
    }

    function test_properties() {
        compare(node0.duration, 0)
        node0.duration = 1
        compare(node0.duration, 1)
        node0.duration = 0
        compare(node0.duration, 0)
        node0.duration = -1
        compare(node0.duration, 0)
    }

    // 验证同步执行

    GhostTree {
        id: tree1

        ActionNode {
            id: node1
            comment: "node1"

            onExecute: setSuccessStatus()
        }
    }

    SignalSpy {
        id: spyTree1
        target: tree1
        signalName: "statusChanged"
    }

    SignalSpy {
        id: spyNode1
        target: node1
        signalName: "statusChanged"
    }

    function test_synchronous() {
        verify(spyTree1.valid)
        verify(spyNode1.valid)

        compare(spyTree1.count, 1)
        compare(spyNode1.count, 1)
        tree1.start()
        spyTree1.wait(100)
    }
}
