import QtQuick 2.0
import QtTest 1.0
import GtGhost 1.0

TestCase {
    id: testCase
    name: "tst_GhostNode"

    GhostTree {
        id: tree_0

        SequenceNode {
            id: sequ_0_0

            ActionNode {
                id: node_0_0_0
            }

            ActionNode {
                id: node_0_0_1
            }
        }
    }

    GhostInspector {
        id: inspector_0
        target: tree_0
    }

    function func_precondition() {
        return true
    }

    function func_weight() {
        return 1
    }

    function test_ghostnode_0() {
        verify(tree_0.status === Ghost.StandBy)

        verify(inspector_0.nextStatus(node_0_0_1, Ghost.StandBy))
        verify(inspector_0.nextStatus(node_0_0_0, Ghost.StandBy))
        verify(inspector_0.nextStatus(sequ_0_0, Ghost.StandBy))
        verify(inspector_0.nextStatus(tree_0, Ghost.StandBy))
        verify(inspector_0.done())

        // 主体树
        verify(sequ_0_0.masterTree === tree_0)
        verify(node_0_0_0.masterTree === tree_0)
        verify(node_0_0_1.masterTree === tree_0)

        // 父节点
        verify(sequ_0_0.parentNode === null)
        verify(node_0_0_0.parentNode === sequ_0_0)
        verify(node_0_0_1.parentNode === sequ_0_0)

        // 子节点
        verify(sequ_0_0.childNodes.length === 2)
        verify(sequ_0_0.childNodes[0] === node_0_0_0)
        verify(sequ_0_0.childNodes[1] === node_0_0_1)
        verify(node_0_0_0.childNodes.length === 0)
        verify(node_0_0_1.childNodes.length === 0)

        // 注释
        verify(sequ_0_0.comment === "")
        sequ_0_0.comment = "5"
        verify(sequ_0_0.comment === "5")
        sequ_0_0.comment = ""
        verify(sequ_0_0.comment === "")

        // 前置条件
        verify(sequ_0_0.precondition === undefined)
        sequ_0_0.precondition = false
        verify(sequ_0_0.precondition === false)
        sequ_0_0.precondition = undefined
        verify(sequ_0_0.precondition === undefined)

        verify(sequ_0_0.precondition === undefined)
        sequ_0_0.precondition = func_precondition
        verify(sequ_0_0.precondition === func_precondition)
        sequ_0_0.precondition = undefined
        verify(sequ_0_0.precondition === undefined)

        // 权重
        verify(sequ_0_0.weight === undefined)
        sequ_0_0.weight = 5
        verify(sequ_0_0.weight === 5)
        sequ_0_0.weight = undefined
        verify(sequ_0_0.weight === undefined)

        verify(sequ_0_0.weight === undefined)
        sequ_0_0.weight = func_weight
        verify(sequ_0_0.weight === func_weight)
        sequ_0_0.weight = undefined
        verify(sequ_0_0.weight === undefined)
    }
}
