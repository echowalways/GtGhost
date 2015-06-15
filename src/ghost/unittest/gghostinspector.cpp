#include "gghostinspector_p.h"
#include "gghostinspector_p_p.h"

#include "gghosttree_p.h"
#include "gghostnode_p.h"

// class GGhostInspector

GGhostInspector::GGhostInspector(QObject *parent)
    : QObject(*new GGhostInspectorPrivate(), parent)
{
}

void GGhostInspector::classBegin()
{
}

void GGhostInspector::componentComplete()
{
}

void GGhostInspector::setTarget(GGhostTree *value)
{
    Q_D(GGhostInspector);

    if (value != d->target) {
        d->target = value;
        d->connectObjects();
        emit targetChanged(value);
    }
}

GGhostTree *GGhostInspector::target() const
{
    Q_D(const GGhostInspector);
    return d->target.data();
}

void GGhostInspector::reset()
{
    Q_D(GGhostInspector);

    d->seek = -1;
}

int GGhostInspector::count() const
{
    Q_D(const GGhostInspector);
    return d->statuses.count();
}

void GGhostInspector::clear()
{
    Q_D(GGhostInspector);

    d->statuses.clear();
    d->seek = -1;
}

bool GGhostInspector::done() const
{
    Q_D(const GGhostInspector);

    for (int i = d->seek + 1; i < d->statuses.count(); ++i) {
        ObjectStatus objStatus = d->statuses.at(i);
        qDebug("Step(%d): %s.status === Ghost.%s", i,
               objStatus.first->metaObject()->className(),
               Ghost::toString(objStatus.second));
    }
    return ((d->seek + 1) == d->statuses.count());
}

void GGhostInspector::onObjectStatusChanged(Ghost::Status status)
{
    Q_D(GGhostInspector);

    ObjectStatus objStatus(QObject::sender(), status);
    d->statuses.append(objStatus);
}

bool GGhostInspector::nextStatus(QObject *object, Ghost::Status status)
{
    Q_D(GGhostInspector);

    if ((d->seek + 1) >= d->statuses.count()) {
        return false;
    }

    ObjectStatus objStatus = d->statuses.at(++d->seek);
    if ((objStatus.first != object)
            || (objStatus.second != status)) {
        return false;
    }

    return true;
}

// class GGhostInspectorPrivate

GGhostInspectorPrivate::GGhostInspectorPrivate()
    : seek(-1)
{
}

GGhostInspectorPrivate::~GGhostInspectorPrivate()
{
}

void GGhostInspectorPrivate::connectObjects()
{
    Q_Q(GGhostInspector);

    // QObject::disconnect(this);

    if (!target) {
        return;
    }

    // 连接灵魂树的信号
    QObject::connect(target.data(), &GGhostTree::statusChanged,
                     q, &GGhostInspector::onObjectStatusChanged);

    // 连接灵魂节点的信号
    QStack<GGhostNode *> nodes;

    foreach (GGhostNode *childNode, target->childNodes()) {
        nodes.push(childNode);
    }

    while (!nodes.isEmpty()) {
        GGhostNode *node = nodes.pop();
        QObject::connect(node, &GGhostNode::statusChanged,
                         q, &GGhostInspector::onObjectStatusChanged);

        foreach (GGhostNode *childNode, node->childNodes()) {
            nodes.push(childNode);
        }
    }
}
