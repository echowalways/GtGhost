import QtQuick 2.0
import QtTest 1.0
import GtGhost 1.0

TestCase {
    id: testCase
    name: "CompositeNode"

    // 验证属性正确性
    GhostTree {
        id: tree_0

        SequenceNode {
            id: sequ_0_0

            ActionNode {
                id: node_0_0_0
            }
        }
    }

    function test_properties() {
        compare(sequ_0_0.brokenStatus, Ghost.Failure)
        sequ_0_0.brokenStatus = Ghost.Success
        compare(sequ_0_0.brokenStatus, Ghost.Success)
        sequ_0_0.brokenStatus = Ghost.Invalid
        compare(sequ_0_0.brokenStatus, Ghost.Success)
        sequ_0_0.brokenStatus = Ghost.StandBy
        compare(sequ_0_0.brokenStatus, Ghost.Success)
        sequ_0_0.brokenStatus = Ghost.Running
        compare(sequ_0_0.brokenStatus, Ghost.Success)
        sequ_0_0.brokenStatus = Ghost.Stopped
        compare(sequ_0_0.brokenStatus, Ghost.Success)
        sequ_0_0.brokenStatus = Ghost.Failure
        compare(sequ_0_0.brokenStatus, Ghost.Failure)

        compare(sequ_0_0.unmatchCount, 1)
        sequ_0_0.unmatchCount = 5
        compare(sequ_0_0.unmatchCount, 5)
        sequ_0_0.unmatchCount = 1
        compare(sequ_0_0.unmatchCount, 1)
        sequ_0_0.unmatchCount = 0
        compare(sequ_0_0.unmatchCount, 1)
    }
}

