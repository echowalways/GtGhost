#include "gghostevent.h"

// class GGhostEvent

GGhostEvent::GGhostEvent(Type type)
    : eventType(type)
{
}

GGhostEvent::~GGhostEvent()
{
}

// class GGhostExecuteEvent

GGhostExecuteEvent::GGhostExecuteEvent(GGhostNode *target)
    : GGhostEvent(Execute)
    , ghostTarget(target)
{
}

GGhostExecuteEvent::~GGhostExecuteEvent()
{
}

// class GGhostConfirmEvent

GGhostConfirmEvent::GGhostConfirmEvent(GGhostNode *source, Ghost::Status status)
    : GGhostEvent(Confirm)
    , ghostSource(source)
    , ghostStatus(status)
{
}

GGhostConfirmEvent::~GGhostConfirmEvent()
{
}
