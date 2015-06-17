#include "gghosttree_p.h"
#include "gghosttree_p_p.h"

#include "gghostevent.h"
#include "gghoststack_p.h"
#include "gghostnode_p.h"
#include "gghostnode_p_p.h"

Q_LOGGING_CATEGORY(qlcGhostTree, "GtGhost.GhostTree")

// class GGhostTree

GGhostTree::GGhostTree(QObject *parent)
    : QObject(*new GGhostTreePrivate(), parent)
{
    qsrand(QDateTime::currentMSecsSinceEpoch());

    connect(this, &GGhostTree::statusChanged,
            [this](Ghost::Status status) {
        switch (status) {
        case Ghost::Invalid:
        case Ghost::StandBy:
            break;
        case Ghost::Running:
            emit started();
            break;
        case Ghost::Success:
        case Ghost::Failure:
            emit finished();
            // pass through
        case Ghost::Stopped:
            emit stopped();
            break;
        }
    });
}

Ghost::Status GGhostTree::status() const
{
    Q_D(const GGhostTree);
    return d->status;
}

GGhostNodeList GGhostTree::childNodes() const
{
    Q_D(const GGhostTree);
    return d->childNodes;
}

void GGhostTree::start()
{
    Q_D(GGhostTree);

    if ((Ghost::Invalid == d->status)
            || (Ghost::Running == d->status)) {
        return;
    }

    d->setStatus(Ghost::Running);

    GGhostNodePrivate *rootptr = d->cast(d->childNodes[0]);
    if (rootptr->callPrecondition()) {
        d->postExecuteEvent(d->childNodes[0]);
    } else {
        d->setStatus(Ghost::Failure);
    }
}

void GGhostTree::stop()
{
    Q_D(GGhostTree);

    if (Ghost::Running != d->status) {
        return;
    }

    QStack<GGhostNode *> ghostNodes;
    QSet<GGhostNode *> visitedGhostNodes;

    // 加载树的一级子节点
    QListIterator<GGhostNode *> i(d->childNodes);
    while (i.hasNext()) {
        GGhostNode *node = i.next();
        if (Ghost::Running == node->status()) {
            ghostNodes.push(node);
        }
    }

    bool hasError = false;

    // 处理子节点状态
    while (!ghostNodes.isEmpty()) {
        GGhostNode *node = ghostNodes.pop();
        GGhostNodePrivate *nodedptr = d->cast(node);

        if (visitedGhostNodes.contains(node)
                || nodedptr->childNodes.isEmpty()) {
            if (nodedptr->terminate()) {
                nodedptr->setStatus(Ghost::Stopped);
            } else {
                hasError = true;
                break;
            }
        } else {
            ghostNodes.push(node);
            visitedGhostNodes.insert(node);

            QListIterator<GGhostNode *> i(nodedptr->childNodes);
            while (i.hasNext()) {
                GGhostNode *node = i.next();
                if (Ghost::Running == node->status()) {
                    ghostNodes.push(node);
                }
            }
        }
    }

    if (!hasError) {
        d->setStatus(Ghost::Stopped);
    }
}

void GGhostTree::reset()
{
    Q_D(GGhostTree);

    if ((Ghost::Invalid == d->status)
            || (Ghost::StandBy == d->status)
            || (Ghost::Running == d->status)) {
        return;
    }

    QStack<GGhostNode *> ghostNodes;
    QSet<GGhostNode *> visitedGhostNodes;

    // 加载树的一级子节点
    QListIterator<GGhostNode *> i(d->childNodes);
    while (i.hasNext()) {
        GGhostNode *node = i.next();
        if (Ghost::StandBy != node->status()) {
            ghostNodes.push(node);
        }
    }

    bool hasError = false;

    // 处理子节点状态
    while (!ghostNodes.isEmpty()) {
        GGhostNode *node = ghostNodes.pop();
        GGhostNodePrivate *nodedptr = d->cast(node);

        if (visitedGhostNodes.contains(node)
                || nodedptr->childNodes.isEmpty()) {
            if (nodedptr->reset()) {
                nodedptr->setStatus(Ghost::StandBy);
            } else {
                hasError = true;
                break;
            }
        } else {
            ghostNodes.push(node);
            visitedGhostNodes.insert(node);

            QListIterator<GGhostNode *> i(nodedptr->childNodes);
            while (i.hasNext()) {
                GGhostNode *node = i.next();
                if (Ghost::StandBy != node->status()) {
                    ghostNodes.push(node);
                }
            }
        }
    }

    if (!hasError) {
        d->setStatus(Ghost::StandBy);
    }
}

void GGhostTree::classBegin()
{
    theGhostStack->push(this);
}

void GGhostTree::componentComplete()
{
    Q_D(GGhostTree);

    bool hasError = false;

    foreach (GGhostNode *childNode, d->childNodes) {
        if (Ghost::Invalid == childNode->status()) {
            hasError = true;
        }
    }

    if (d->childNodes.count() != 1) {
        qCWarning(qlcGhostTree)
                << "Allows only one child node.";
        hasError = true;
    }

    if (!hasError) {
        d->setStatus(Ghost::StandBy);
    }

    theGhostStack->pop(this);
}

// class GGhostTreePrivate

GGhostTreePrivate::GGhostTreePrivate()
    : status(Ghost::Invalid)
    , eventsProcessing(false)
{
}

GGhostTreePrivate::~GGhostTreePrivate()
{
}

GGhostNodePrivate *GGhostTreePrivate::cast(GGhostNode *node)
{
    return GGhostNodePrivate::cast(node);
}

const GGhostNodePrivate *GGhostTreePrivate::cast(const GGhostNode *node)
{
    return GGhostNodePrivate::cast(node);
}

void GGhostTreePrivate::postEvent(GGhostEvent *event)
{
    eventQueue.enqueue(event);

    if (!eventsProcessing) {
        _q_processEvents();
    }
}

void GGhostTreePrivate::_q_processEvents()
{
    eventsProcessing = true;
    while (!eventQueue.isEmpty()) {
        GGhostEvent *event = eventQueue.dequeue();
        if (event->type() == GGhostEvent::Execute) {
            processExecuteEvent(static_cast<GGhostExecuteEvent *>(event));
        } else if (event->type() == GGhostEvent::Confirm) {
            processConfirmEvent(static_cast<GGhostConfirmEvent *>(event));
        } else {
            Q_UNREACHABLE();
        }
    }
    eventsProcessing = false;
}

void GGhostTreePrivate::postExecuteEvent(GGhostNode *target)
{
    Q_CHECK_PTR(target);
    if (target) {
        postEvent(new GGhostExecuteEvent(target));
    }
}

void GGhostTreePrivate::postConfirmEvent(GGhostNode *source)
{
    Q_CHECK_PTR(source);
    if (source) {
        postEvent(new GGhostConfirmEvent(source, source->status()));
    }
}

void GGhostTreePrivate::processExecuteEvent(GGhostExecuteEvent *event)
{
    Q_CHECK_PTR(event->target());
    cast(event->target())->executeEvent(event);
}

void GGhostTreePrivate::processConfirmEvent(GGhostConfirmEvent *event)
{
    Q_ASSERT(Ghost::Invalid != event->status());
    Q_ASSERT(Ghost::StandBy != event->status());
    Q_ASSERT(Ghost::Running != event->status());

    Q_CHECK_PTR(event->source());
    GGhostNode *sourceNode = event->source();
    GGhostNode *parentNode = sourceNode->parentNode();

    if (parentNode) {
        cast(parentNode)->confirmEvent(event);
    } else {
        setStatus(event->status());
    }
}

void GGhostTreePrivate::setStatus(Ghost::Status status)
{
    Q_Q(GGhostTree);

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

    qCDebug(qlcGhostTree,
            "Status: '%s' ==> '%s' : %s %s(%p)",
            Ghost::toString(this->status), Ghost::toString(status),
            ((Ghost::Running == status) ? "-->" : "<--"),
            q->metaObject()->className(), q);

#endif // QT_NO_DEBUG

    if (status != this->status) {
        this->status = status;
        emit q->statusChanged(status);
    }
}

// moc_gghosttree_p.cpp
#include "moc_gghosttree_p.cpp"
