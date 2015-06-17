import QtQuick 2.0
import QtTest 1.0
import GtGhost 1.0

TestCase {
    id: testCase
    name: "DecoratorNode"

    // 验证属性正确性
    GhostTree {
        id: tree_0

        RepeaterNode {
            id: repe_0_0

            ActionNode {
                id: node_0_0_0
            }
        }
    }

    function test_properties() {
        compare(repe_0_0.brokenStatus, Ghost.Failure)
        repe_0_0.brokenStatus = Ghost.Success
        compare(repe_0_0.brokenStatus, Ghost.Success)
        repe_0_0.brokenStatus = Ghost.Invalid
        compare(repe_0_0.brokenStatus, Ghost.Success)
        repe_0_0.brokenStatus = Ghost.StandBy
        compare(repe_0_0.brokenStatus, Ghost.Success)
        repe_0_0.brokenStatus = Ghost.Running
        compare(repe_0_0.brokenStatus, Ghost.Success)
        repe_0_0.brokenStatus = Ghost.Stopped
        compare(repe_0_0.brokenStatus, Ghost.Success)
        repe_0_0.brokenStatus = Ghost.Failure
        compare(repe_0_0.brokenStatus, Ghost.Failure)
    }
}

