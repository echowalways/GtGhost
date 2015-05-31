#include "gghosttree_p.h"
#include "gghosttree_p_p.h"

#include <QtCore/QDateTime>
#include <QtCore/QLoggingCategory>

#include "gghostdata_p.h"

Q_LOGGING_CATEGORY(qlcGhostTree, "GtGhost.GhostTree")

// class GGhostTree

GGhostTree::GGhostTree(QObject *parent)
    : GGhostSourceNode(*new GGhostTreePrivate(), parent)
{
    Q_D(GGhostTree);

    d->extraData = new GGhostData(this);
}

GGhostNodeList GGhostTree::childNodes() const
{
    Q_D(const GGhostTree);
    return d->childNodes;
}

void GGhostTree::start()
{
    Q_D(GGhostTree);

    if ((Ghost::Invalid != d->status)
            && (Ghost::Running != d->status)) {
        d->execute();
    }
}

void GGhostTree::stop()
{
    Q_D(GGhostTree);

    if (Ghost::Running == d->status) {
        d->terminate();
    }
}

void GGhostTree::reset()
{
    Q_D(GGhostTree);

    if ((Ghost::Success == d->status)
            || (Ghost::Failure == d->status)
            || (Ghost::Stopped == d->status)) {
        d->reset();
    }
}

void GGhostTree::classBegin()
{
}

void GGhostTree::componentComplete()
{
    Q_D(GGhostTree);

    qsrand(QDateTime::currentMSecsSinceEpoch());

    if (d->initialize()) {
        d->setStatus(Ghost::StandBy);
    }
}

// class GGhostTreePrivate

GGhostTreePrivate::GGhostTreePrivate()
{
}

GGhostTreePrivate::~GGhostTreePrivate()
{
}

void GGhostTreePrivate::onStatusChanged(Ghost::Status status)
{
    Q_Q(GGhostTree);

    switch (status) {
    case Ghost::Invalid:
    case Ghost::StandBy:
        break;
    case Ghost::Running:
        emit q->started();
        break;
    case Ghost::Success:
    case Ghost::Failure:
        emit q->finished();
        // pass through
    case Ghost::Stopped:
        emit q->stopped();
        break;
    }
}

void GGhostTreePrivate::onChildStatusChanged(GGhostSourceNode *childNode)
{
    Q_ASSERT(Ghost::Invalid != status);

    Q_CHECK_PTR(childNodes[0]);
    Q_ASSERT(childNode == childNodes[0]);

    Ghost::Status childStatus = childNode->status();

    if ((Ghost::Success == childStatus)
            || (Ghost::Failure == childStatus)
            || (Ghost::Stopped == childStatus)) {
        setStatus(childStatus);
    }
}

bool GGhostTreePrivate::initialize()
{
    Q_Q(GGhostTree);

    bool hasError = false;

    foreach (GGhostNode *childNode, childNodes) {
        GGhostNodePrivate *childptr = cast(childNode);
        // 初始化子节点数据
        childptr->masterTree = q;
        childptr->extraData = extraData;
        // 开始初始化子节点
        if (childptr->initialize()) {
            childptr->parentSourceNode = q;
        } else {
            hasError = true;
        }
    }

    if (childNodes.count() != 1) {
        qCWarning(qlcGhostTree)
                << "Allows only one child node.";
        hasError = true;
    }

    if (!hasError) {
        emit q->initialized();
    }

    return !hasError;
}

void GGhostTreePrivate::reset()
{
    Q_CHECK_PTR(childNodes[0]);
    Q_ASSERT(Ghost::Invalid != status);
    Q_ASSERT(Ghost::StandBy != status);
    Q_ASSERT(Ghost::Running != status);

    if (extraData) {
        extraData->reset();
    }
    cast(childNodes[0])->reset();

    setStatus(Ghost::StandBy);
}

void GGhostTreePrivate::execute()
{
    Q_CHECK_PTR(childNodes[0]);
    Q_ASSERT(Ghost::Invalid != status);
    Q_ASSERT(Ghost::Running != status);

    setStatus(Ghost::Running);

    GGhostNodePrivate *rootptr = cast(childNodes[0]);
    if (rootptr->callPrecondition()) {
        rootptr->execute();
    } else {
        setStatus(Ghost::Failure);
    }
}

void GGhostTreePrivate::terminate()
{
    Q_CHECK_PTR(childNodes[0]);
    Q_ASSERT(Ghost::Running == status);

    cast(childNodes[0])->terminate();
}

// moc_gghosttree_p.cpp
#include "moc_gghosttree_p.cpp"
