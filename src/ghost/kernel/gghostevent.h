#ifndef GGHOSTEVENT_H
#define GGHOSTEVENT_H

#include "gghostnamespace.h"

class GGhostNode;

// class GGhostEvent

class GGhostEvent
{
public:
    enum Type { Execute, Confirm };

protected:
    explicit GGhostEvent(Type type);
public:
    virtual ~GGhostEvent();

public:
    Type type() const;
private:
    Type eventType;
};

inline GGhostEvent::Type GGhostEvent::type() const
{
    return eventType;
}

// class GGhostExecuteEvent

class GGhostExecuteEvent : public GGhostEvent
{
public:
    explicit GGhostExecuteEvent(GGhostNode *target);
    virtual ~GGhostExecuteEvent();

public:
    GGhostNode *target() const;
private:
    GGhostNode *ghostTarget;
};

inline GGhostNode *GGhostExecuteEvent::target() const
{
    return ghostTarget;
}

// class GGhostConfirmEvent

class GGhostConfirmEvent : public GGhostEvent
{
public:
    GGhostConfirmEvent(GGhostNode *source, Ghost::Status status);
    virtual ~GGhostConfirmEvent();

public:
    GGhostNode *source() const;
    Ghost::Status status() const;
private:
    GGhostNode *ghostSource;
    Ghost::Status ghostStatus;
};

inline GGhostNode *GGhostConfirmEvent::source() const
{
    return ghostSource;
}

inline Ghost::Status GGhostConfirmEvent::status() const
{
    return ghostStatus;
}

#endif // GGHOSTEVENT_H
