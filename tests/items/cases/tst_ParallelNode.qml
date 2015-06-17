import QtQuick 2.0
import QtTest 1.0
import GtGhost 1.0

TestCase {
    id: testCase
    name: "ParallelNode"

    GhostTree {
        id: tree_0

        ParallelNode {
            id: para_0_0

            ActionNode {
                id: node_0_0_0
                onExecute: setSuccess()
            }

            ActionNode {
                id: node_0_0_1
                onExecute: setFailure()
            }

            ActionNode {
                id: node_0_0_2
                onExecute: setSuccess()
            }

            ActionNode {
                id: node_0_0_3
                onExecute: setFailure()
            }
        }
    }

    GhostInspector {
        id: inspector_0
        target: tree_0
    }

    function test_statuses_0() {
        verify(inspector_0.nextStatus(node_0_0_3, Ghost.StandBy))
        verify(inspector_0.nextStatus(node_0_0_2, Ghost.StandBy))
        verify(inspector_0.nextStatus(node_0_0_1, Ghost.StandBy))
        verify(inspector_0.nextStatus(node_0_0_0, Ghost.StandBy))
        verify(inspector_0.nextStatus(para_0_0, Ghost.StandBy))
        verify(inspector_0.nextStatus(tree_0, Ghost.StandBy))
        verify(inspector_0.done())

        tree_0.start()

        verify(inspector_0.nextStatus(tree_0, Ghost.Running))
        verify(inspector_0.nextStatus(para_0_0, Ghost.Running))
        verify(inspector_0.nextStatus(node_0_0_0, Ghost.Running))
        verify(inspector_0.nextStatus(node_0_0_0, Ghost.Success))
        verify(inspector_0.nextStatus(node_0_0_1, Ghost.Running))
        verify(inspector_0.nextStatus(node_0_0_1, Ghost.Failure))
        verify(inspector_0.nextStatus(node_0_0_2, Ghost.Running))
        verify(inspector_0.nextStatus(node_0_0_2, Ghost.Success))
        verify(inspector_0.nextStatus(node_0_0_3, Ghost.Running))
        verify(inspector_0.nextStatus(node_0_0_3, Ghost.Failure))
        verify(inspector_0.nextStatus(para_0_0, Ghost.Success))
        verify(inspector_0.nextStatus(tree_0, Ghost.Success))
        verify(inspector_0.done())

        //
        node_0_0_2.precondition = false

        tree_0.start()

        verify(inspector_0.nextStatus(tree_0, Ghost.Running))
        verify(inspector_0.nextStatus(para_0_0, Ghost.Running))
        verify(inspector_0.nextStatus(node_0_0_0, Ghost.Running))
        verify(inspector_0.nextStatus(node_0_0_0, Ghost.Success))
        verify(inspector_0.nextStatus(node_0_0_1, Ghost.Running))
        verify(inspector_0.nextStatus(node_0_0_1, Ghost.Failure))
        verify(inspector_0.nextStatus(node_0_0_3, Ghost.Running))
        verify(inspector_0.nextStatus(node_0_0_3, Ghost.Failure))
        verify(inspector_0.nextStatus(para_0_0, Ghost.Success))
        verify(inspector_0.nextStatus(tree_0, Ghost.Success))
        verify(inspector_0.done())

        //
        node_0_0_0.precondition = false
        node_0_0_1.precondition = false
        node_0_0_3.precondition = false

        tree_0.start()

        verify(inspector_0.nextStatus(tree_0, Ghost.Running))
        verify(inspector_0.nextStatus(para_0_0, Ghost.Running))
        verify(inspector_0.nextStatus(para_0_0, Ghost.Failure))
        verify(inspector_0.nextStatus(tree_0, Ghost.Failure))
        verify(inspector_0.done())
    }

    //
    GhostTree {
        id: tree_1

        ParallelNode {
            id: para_1_0

            ActionNode {
                id: node_1_0_0
                duration: 40
            }

            ActionNode {
                id: node_1_0_1
                duration: 20
            }

            ActionNode {
                id: node_1_0_2
                duration: 30
            }

            ActionNode {
                id: node_1_0_3
                duration: 10
            }
        }
    }

    GhostInspector {
        id: inspector_1
        target: tree_1
    }

    function test_statuses_1() {
        verify(inspector_1.nextStatus(node_1_0_3, Ghost.StandBy))
        verify(inspector_1.nextStatus(node_1_0_2, Ghost.StandBy))
        verify(inspector_1.nextStatus(node_1_0_1, Ghost.StandBy))
        verify(inspector_1.nextStatus(node_1_0_0, Ghost.StandBy))
        verify(inspector_1.nextStatus(para_1_0, Ghost.StandBy))
        verify(inspector_1.nextStatus(tree_1, Ghost.StandBy))
        verify(inspector_1.done())

        tree_1.start()

        verify(inspector_1.nextStatus(tree_1, Ghost.Running))
        verify(inspector_1.nextStatus(para_1_0, Ghost.Running))
        verify(inspector_1.nextStatus(node_1_0_0, Ghost.Running))
        verify(inspector_1.nextStatus(node_1_0_1, Ghost.Running))
        verify(inspector_1.nextStatus(node_1_0_2, Ghost.Running))
        verify(inspector_1.nextStatus(node_1_0_3, Ghost.Running))
        verify(inspector_1.done())

        testCase.wait(100)

        verify(inspector_1.nextStatus(node_1_0_3, Ghost.Failure))
        verify(inspector_1.nextStatus(node_1_0_1, Ghost.Failure))
        verify(inspector_1.nextStatus(node_1_0_2, Ghost.Failure))
        verify(inspector_1.nextStatus(node_1_0_0, Ghost.Failure))
        verify(inspector_1.nextStatus(para_1_0, Ghost.Success))
        verify(inspector_1.nextStatus(tree_1, Ghost.Success))
        verify(inspector_1.done())

        //
        node_1_0_2.precondition = false

        tree_1.start()

        verify(inspector_1.nextStatus(tree_1, Ghost.Running))
        verify(inspector_1.nextStatus(para_1_0, Ghost.Running))
        verify(inspector_1.nextStatus(node_1_0_0, Ghost.Running))
        verify(inspector_1.nextStatus(node_1_0_1, Ghost.Running))
        verify(inspector_1.nextStatus(node_1_0_3, Ghost.Running))
        verify(inspector_1.done())

        testCase.wait(100)

        verify(inspector_1.nextStatus(node_1_0_3, Ghost.Failure))
        verify(inspector_1.nextStatus(node_1_0_1, Ghost.Failure))
        verify(inspector_1.nextStatus(node_1_0_0, Ghost.Failure))
        verify(inspector_1.nextStatus(para_1_0, Ghost.Success))
        verify(inspector_1.nextStatus(tree_1, Ghost.Success))
        verify(inspector_1.done())
    }
}
