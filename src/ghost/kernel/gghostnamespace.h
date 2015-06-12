#ifndef GGHOSTNAMESPACE_H
#define GGHOSTNAMESPACE_H

#include <QtCore/QObject>

class Ghost : public QObject
{
    Q_OBJECT
    Q_ENUMS(Status)
    Q_ENUMS(UpdateMode)
    Q_ENUMS(RandomMode)
    Q_ENUMS(BaseType)
    Q_ENUMS(NodeType)

public:
    enum Status {
        Invalid,
        StandBy,
        Running,
        Success,
        Failure,
        Stopped
    };

    enum UpdateMode {
        ResetOnly,
        Everytime
    };

    enum RandomMode {
        Parity,
        Weight
    };

    enum BaseType {
        CompositeNode,
        DecoratorNode,
        LeafNode
    };

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
};

class GGhostNode;
typedef QList<GGhostNode *> GGhostNodeList;
class GGhostTree;

class GGhostData;

#endif // GGHOSTNAMESPACE_H
