#include "gghostsourcenode_p.h"
#include "gghostsourcenode_p_p.h"

#include <QtCore/QLoggingCategory>

Q_LOGGING_CATEGORY(qlcGhostSourceNode, "GtGhost.GhostSourceNode")

// class GGhostSourceNode

GGhostSourceNode::GGhostSourceNode(GGhostSourceNodePrivate &dd, QObject *parent)
    : QObject(dd, parent)
{
}

Ghost::Status GGhostSourceNode::status() const
{
    Q_D(const GGhostSourceNode);
    return d->status;
}

void GGhostSourceNode::setSummary(const QString &value)
{
    Q_D(GGhostSourceNode);

    if (value != d->summary) {
        d->summary = value;
        emit summaryChanged(value);
    }
}

QString GGhostSourceNode::summary() const
{
    Q_D(const GGhostSourceNode);
    return d->summary;
}

// class GGhostSourceNodePrivate

GGhostSourceNodePrivate::GGhostSourceNodePrivate()
    : parentSourceNode(0)
    , status(Ghost::Invalid)
{
}

GGhostSourceNodePrivate::~GGhostSourceNodePrivate()
{
}

const char *GGhostSourceNodePrivate::toString(Ghost::Status status)
{
    static const char s_invalid[] = "Invalid";
    static const char s_standBy[] = "StandBy";
    static const char s_running[] = "Running";
    static const char s_success[] = "Success";
    static const char s_failure[] = "Failure";
    static const char s_stopped[] = "Stopped";

    switch (status) {
    case Ghost::Invalid:
        return s_invalid;
        break;
    case Ghost::StandBy:
        return s_standBy;
        break;
    case Ghost::Running:
        return s_running;
        break;
    case Ghost::Success:
        return s_success;
        break;
    case Ghost::Failure:
        return s_failure;
        break;
    case Ghost::Stopped:
        return s_stopped;
        break;
    }

    Q_UNREACHABLE();
    return 0;
}

void GGhostSourceNodePrivate::setStatus(Ghost::Status status)
{
    Q_Q(GGhostSourceNode);

#if !defined(QT_NO_DEBUG)

    switch (this->status) {
    case Ghost::Invalid:
        switch (status) {
        case Ghost::StandBy:
            break;
        default:
            Q_UNREACHABLE();
        }
        break;
    case Ghost::StandBy:
        switch (status) {
        case Ghost::Running:
            break;
        default:
            Q_UNREACHABLE();
        }
        break;
    case Ghost::Running:
        switch (status) {
        case Ghost::Success:
        case Ghost::Failure:
        case Ghost::Stopped:
            break;
        default:
            Q_UNREACHABLE();
        }
        break;
    case Ghost::Success:
        switch (status) {
        case Ghost::StandBy:
        case Ghost::Running:
            break;
        default:
            Q_UNREACHABLE();
        }
        break;
    case Ghost::Failure:
        switch (status) {
        case Ghost::StandBy:
        case Ghost::Running:
            break;
        default:
            Q_UNREACHABLE();
        }
        break;
    case Ghost::Stopped:
        switch (status) {
        case Ghost::StandBy:
        case Ghost::Running:
            break;
        default:
            Q_UNREACHABLE();
        }
        break;
    }

    if (summary.isEmpty()) {
        qCDebug(qlcGhostSourceNode,
                "Status: '%s' ==> '%s' : %s %s(%p)",
                toString(this->status), toString(status),
                ((Ghost::Running == status) ? "-->" : "<--"),
                q->metaObject()->className(), q);
    } else {
        qCDebug(qlcGhostSourceNode).nospace()
                << "Status: '" << toString(this->status)
                << "' ==> '" << toString(status)
                << "' :" << ((Ghost::Running == status) ? " --> " : " <-- ")
                << summary.toUtf8().constData();
    }

#endif // QT_NO_DEBUG

    if (status != this->status) {
        this->status = status;
        emit q->statusChanged(status);

        if (parentSourceNode) {
            cast(parentSourceNode)->onChildStatusChanged(q);
        }
    }
}

void GGhostSourceNodePrivate::onChildStatusChanged(GGhostSourceNode *childNode)
{
    Q_UNUSED(childNode);
}
