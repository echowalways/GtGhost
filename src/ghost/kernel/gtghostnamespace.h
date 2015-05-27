#ifndef GTGHOSTNAMESPACE_H
#define GTGHOSTNAMESPACE_H

#include <QtCore/QObject>

class Ghost : public QObject
{
    Q_OBJECT
    Q_ENUMS(Status)
    Q_ENUMS(UpdateMode)
    Q_ENUMS(RandomMode)
    Q_ENUMS(NodeType)
    Q_ENUMS(ItemType)

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

    enum NodeType {
        CompositeNode,
        DecoratorNode,
        ConditionNode,
        ActionNode
    };

    enum ItemType {
        LinearSequenceItem,
        LinearSelectorItem,
        WeightSequenceItem,
        WeightSelectorItem,
        RandomSequenceItem,
        RandomSelectorItem,

        InverterItem,
        RepeaterItem,
        RepeatUntilSuccessItem,
        RepeatUntilFailureItem,
        AlwaysSuccessItem,
        AlwaysFailureItem,

        ConditionItem,

        ActionItem,
        IdleActionItem
    };
};

#endif // GTGHOSTNAMESPACE_H

