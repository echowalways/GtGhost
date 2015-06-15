#include "gblackboard_p.h"
#include "gblackboard_p_p.h"

#include <QtCore/QLoggingCategory>

#include "gghosttree_p.h"
#include "gghostnode_p.h"

Q_LOGGING_CATEGORY(qlcBlackboard, "GtGhost.Blackboard")

typedef QHash<QQmlEngine *, QPointer<GBlackboardAttached> > GlobalBlackboard;
Q_GLOBAL_STATIC(GlobalBlackboard, theGlobalBlackboard2)

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

void GBlackboard::remove(const QString &key)
{
    Q_D(GBlackboard);
    d->datas.remove(key);
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
    Q_D(GBlackboardAttached);

    GBlackboardAttached *blackboard = d->sharedBlackboard(false);
    if (blackboard) {
        blackboard->clear();
    }
}

bool GBlackboardAttached::hasg(const QString &key) const
{
    Q_D(const GBlackboardAttached);

    GBlackboardAttached *blackboard = d->sharedBlackboard(false);
    if (blackboard) {
        return blackboard->has(key);
    }

    return false;
}

void GBlackboardAttached::setg(const QString &key, const QJSValue &value)
{
    Q_D(const GBlackboardAttached);

    GBlackboardAttached *blackboard = d->sharedBlackboard();
    if (blackboard) {
        blackboard->set(key, value);
    }
}

QJSValue GBlackboardAttached::getg(const QString &key) const
{
    Q_D(const GBlackboardAttached);

    GBlackboardAttached *blackboard = d->sharedBlackboard(false);
    if (blackboard) {
        return blackboard->get(key);
    }

    return QJSValue();
}

void GBlackboardAttached::removeg(const QString &key)
{
    Q_D(GBlackboardAttached);

    GBlackboardAttached *blackboard = d->sharedBlackboard(false);
    if (blackboard) {
        return blackboard->remove(key);
    }
}

void GBlackboardAttached::cleart()
{
    Q_D(GBlackboardAttached);

    GBlackboardAttached *blackboard = d->scopedBlackboard(false);
    if (blackboard) {
        blackboard->clear();
    }
}

bool GBlackboardAttached::hast(const QString &key) const
{
    Q_D(const GBlackboardAttached);

    GBlackboardAttached *blackboard = d->scopedBlackboard(false);
    if (blackboard) {
        return blackboard->has(key);
    }

    return false;
}

void GBlackboardAttached::sett(const QString &key, const QJSValue &value)
{
    Q_D(const GBlackboardAttached);

    GBlackboardAttached *blackboard = d->scopedBlackboard();
    if (blackboard) {
        blackboard->set(key, value);
    }
}

QJSValue GBlackboardAttached::gett(const QString &key) const
{
    Q_D(const GBlackboardAttached);

    GBlackboardAttached *blackboard = d->scopedBlackboard(false);
    if (blackboard) {
        return blackboard->get(key);
    }

    return QJSValue();
}

void GBlackboardAttached::removet(const QString &key)
{
    Q_D(GBlackboardAttached);

    GBlackboardAttached *blackboard = d->scopedBlackboard();
    if (blackboard) {
        blackboard->remove(key);
    }
}

// class GBlackboardAttachedPrivate

GBlackboardAttachedPrivate::GBlackboardAttachedPrivate()
    : masterTree(nullptr)
    , targetNode(nullptr)
    , sharedBlackboardAttached(nullptr)
    , scopedBlackboardAttached(nullptr)
{
}

GBlackboardAttachedPrivate::~GBlackboardAttachedPrivate()
{
}

GBlackboardAttached *GBlackboardAttachedPrivate::sharedBlackboard(bool create) const
{
    if (sharedBlackboardAttached) {
        return sharedBlackboardAttached;
    }

    QQmlContext *context = qmlContext(parent);
    if (!context) {
        Q_CHECK_PTR(context);
        return nullptr;
    }

    QQmlEngine *engine = context->engine();
    if (!engine) {
        Q_CHECK_PTR(engine);
        return nullptr;
    }

    QPointer<GBlackboardAttached> blackboard = theGlobalBlackboard2()->value(engine);
    if (blackboard.isNull() && create) {
        blackboard = new GBlackboardAttached(engine);
        theGlobalBlackboard2()->insert(engine, blackboard);
    }

    GBlackboardAttachedPrivate *_this = const_cast<GBlackboardAttachedPrivate *>(this);
    _this->sharedBlackboardAttached = blackboard.data();
    return sharedBlackboardAttached;
}

GBlackboardAttached *GBlackboardAttachedPrivate::scopedBlackboard(bool create) const
{
    if (scopedBlackboardAttached) {
        return scopedBlackboardAttached;
    }

    if (!masterTree) {
        qCWarning(qlcBlackboard)
                << "Master tree is null.";
        return nullptr;
    }

    QObject *attached = qmlAttachedPropertiesObject<GBlackboard>(masterTree, create);
    if (attached) {
        GBlackboardAttachedPrivate *_this = const_cast<GBlackboardAttachedPrivate *>(this);
        _this->scopedBlackboardAttached = qobject_cast<GBlackboardAttached *>(attached);
    }
    return scopedBlackboardAttached;
}
