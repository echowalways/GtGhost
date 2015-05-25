#ifndef GTGHOSTNAMESPACE_H
#define GTGHOSTNAMESPACE_H

#include <QtCore/QObject>

class Ghost : public QObject
{
    Q_OBJECT
    Q_ENUMS(Status)
    Q_ENUMS(UpdateMode)
    Q_ENUMS(RandomMode)

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
};

#endif // GTGHOSTNAMESPACE_H

