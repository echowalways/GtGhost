#include "gblackboard_p.h"
#include "gblackboard_p_p.h"

#include <QtCore/QLoggingCategory>

#include "gghosttree_p.h"
#include "gghostnode_p.h"

Q_LOGGING_CATEGORY(qlcBlackboard, "GtGhost.Blackboard")

// class GBlackboard

GBlackboard::GBlackboard(QObject *parent)
    : QObject(*new GBlackboardPrivate(), parent)
{
}

GBlackboard::GBlackboard(GBlackboardPrivate &dd, QObject *parent)
    : QObject(dd, parent)
{
}

void GBlackboard::clear()
{
    Q_D(GBlackboard);
    d->datas.clear();
}

bool GBlackboard::has(const QString &key) const
{
    Q_D(const GBlackboard);
    return d->datas.contains(key);
}

void GBlackboard::set(const QString &key, const QJSValue &value)
{
    Q_D(GBlackboard);

    if (value.isUndefined()) {
        d->datas.remove(key);
    } else {
        d->datas.insert(key, value);
    }
}

QJSValue GBlackboard::get(const QString &key) const
{
    Q_D(const GBlackboard);
    return d->datas.value(key);
}

GBlackboardAttached *GBlackboard::qmlAttachedProperties(QObject *target)
{
    return new GBlackboardAttached(target);
}

// class GBlackboardPrivate

GBlackboardPrivate::GBlackboardPrivate()
{
}

GBlackboardPrivate::~GBlackboardPrivate()
{
}

// class GBlackboardAttached

GBlackboardAttached::GBlackboardAttached(QObject *parent)
    : GBlackboard(*new GBlackboardAttachedPrivate(), parent)
{
    Q_D(GBlackboardAttached);

    d->targetNode = qobject_cast<GGhostNode *>(parent);
    if (d->targetNode) {
        connect(d->targetNode, &GGhostNode::statusChanged,
                [this](Ghost::Status status) {
            if (Ghost::StandBy == status) {
                clear();
            }
        });

        d->masterTree = d->targetNode->masterTree();
    } else {
        d->masterTree = qobject_cast<GGhostTree *>(parent);
        if (d->masterTree) {
            connect(d->masterTree, &GGhostTree::statusChanged,
                    [this](Ghost::Status status) {
                if (Ghost::StandBy == status) {
                    clear();
                }
            });
        }
    }
}

void GBlackboardAttached::clearg()
{
}

bool GBlackboardAttached::hasg(const QString &key) const
{
    Q_UNUSED(key);
    Q_UNREACHABLE();
    return false;
}

void GBlackboardAttached::setg(const QString &key, const QJSValue &value)
{
    Q_UNUSED(key);
    Q_UNUSED(value);
    Q_UNREACHABLE();
}

QJSValue GBlackboardAttached::getg(const QString &key) const
{
    Q_UNUSED(key);
    Q_UNREACHABLE();
    return QJSValue();
}

void GBlackboardAttached::cleart()
{
    Q_D(GBlackboardAttached);

    if (!d->masterTree) {
        qCWarning(qlcBlackboard)
                << "Master tree is empty.";
        return;
    }

    QObject *attached = qmlAttachedPropertiesObject<GBlackboard>(d->masterTree, false);
    if (attached) {
        GBlackboardAttached *blackboard
                = qobject_cast<GBlackboardAttached *>(attached);
        if (blackboard) {
            blackboard->clear();
        }
    }
}

bool GBlackboardAttached::hast(const QString &key) const
{
    Q_D(const GBlackboardAttached);

    if (!d->masterTree) {
        qCWarning(qlcBlackboard)
                << "Master tree is empty.";
        return false;
    }

    QObject *attached = qmlAttachedPropertiesObject<GBlackboard>(d->masterTree, false);
    if (attached) {
        GBlackboardAttached *blackboard
                = qobject_cast<GBlackboardAttached *>(attached);
        if (blackboard) {
            return blackboard->has(key);
        }
    }

    return false;
}

void GBlackboardAttached::sett(const QString &key, const QJSValue &value)
{
    Q_D(const GBlackboardAttached);

    if (!d->masterTree) {
        qCWarning(qlcBlackboard)
                << "Master tree is empty.";
        return;
    }

    QObject *attached = qmlAttachedPropertiesObject<GBlackboard>(d->masterTree);
    if (attached) {
        GBlackboardAttached *blackboard
                = qobject_cast<GBlackboardAttached *>(attached);
        if (blackboard) {
            blackboard->set(key, value);
        }
    }
}

QJSValue GBlackboardAttached::gett(const QString &key) const
{
    Q_D(const GBlackboardAttached);

    if (!d->masterTree) {
        qCWarning(qlcBlackboard)
                << "Master tree is empty.";
        return QJSValue();
    }

    QObject *attached = qmlAttachedPropertiesObject<GBlackboard>(d->masterTree, false);
    if (attached) {
        GBlackboardAttached *blackboard
                = qobject_cast<GBlackboardAttached *>(attached);
        if (blackboard) {
            return blackboard->get(key);
        }
    }

    return QJSValue();
}

// class GBlackboardAttachedPrivate

GBlackboardAttachedPrivate::GBlackboardAttachedPrivate()
    : masterTree(0)
    , targetNode(0)
{
}

GBlackboardAttachedPrivate::~GBlackboardAttachedPrivate()
{
}
