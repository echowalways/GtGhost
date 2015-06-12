#ifndef GGHOSTGLOBAL_H
#define GGHOSTGLOBAL_H

#include <QtCore>
#include <QtQml>

class Ghost : public QObject
{
    Q_OBJECT
    Q_ENUMS(Status)
    Q_ENUMS(BaseType)
    Q_ENUMS(NodeType)
    Q_ENUMS(UpdateMode)
    Q_ENUMS(RandomMode)

public:
    // 节点状态
    enum Status {
        Invalid,
        StandBy,
        Running,
        Success,
        Failure,
        Stopped
    };

    // 节点基本类型
    enum BaseType {
        CompositeNode,
        DecoratorNode,
        LeafNode
    };

    // 节点类型
    enum NodeType {
        SequenceNode,
        SelectorNode,
        ParallelNode,
        PrioritySequenceNode,
        PrioritySelectorNode,
        RandomSequenceNode,
        RandomSelectorNode,
        ParallelSequenceNode,
        ParallelSelectorNode,

        InverterNode,
        RepeaterNode,
        ForceSuccessNode,
        ForceFailureNode,
        RepeatUntilSuccessNode,
        RepeatUntilFailureNode,

        ActionNode,
        ConditionNode,
        FreezeNode
    };

    // 子节点更新模式
    enum UpdateMode {
        ResetOnly,
        Everytime
    };

    // 子节点随机模式
    enum RandomMode {
        Parity,
        Weight
    };

public:
    static const char *toString(Ghost::Status status);
};

// 基本类型的前置定义

class GGhostTree;
class GGhostNode;
class GGhostData;

typedef QList<GGhostNode *> GGhostNodeList;

#endif // GGHOSTGLOBAL_H
