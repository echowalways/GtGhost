#include "gblackboard_p.h"
#include "gblackboard_p_p.h"

#include "gghosttree_p.h"
#include "gghostnode_p.h"

typedef QHash<QQmlEngine *, QPointer<GBlackboard> > GlobalBlackboards;
Q_GLOBAL_STATIC(GlobalBlackboards, theGlobalBlackboards)

// class GBlackboard

GBlackboard::GBlackboard(QObject *parent)
    : QObject(*new GBlackboardPrivate(), parent)
{
    Q_D(GBlackboard);

    d->targetNode = qobject_cast<GGhostNode *>(parent);
    if (d->targetNode) {
        connect(d->targetNode, &GGhostNode::statusChanged,
                [this](Ghost::Status status) {
            if (Ghost::StandBy == status) {
                this->clear();
            }
        });

        d->masterTree = d->targetNode->masterTree();
    } else {
        d->masterTree = qobject_cast<GGhostTree *>(parent);
        if (d->masterTree) {
            connect(d->masterTree, &GGhostTree::statusChanged,
                    [this](Ghost::Status status) {
                if (Ghost::StandBy == status) {
                    this->clear();
                }
            });
        }
    }
}

GBlackboard *GBlackboard::qmlAttachedProperties(QObject *target)
{
    return new GBlackboard(target);
}

GBlackboard *GBlackboard::globalBlackboard() const
{
    Q_D(const GBlackboard);

    if (d->globalBlackboard) {
        return d->globalBlackboard;
    }

    QQmlContext *context = qmlContext(d->parent);
    if (nullptr == context) {
        Q_CHECK_PTR(context);
        return nullptr;
    }

    QQmlEngine *engine = context->engine();
    if (nullptr == engine) {
        Q_CHECK_PTR(engine);
        return nullptr;
    }

    QPointer<GBlackboard> blackboard = theGlobalBlackboards()->value(engine);
    if (blackboard.isNull()) {
        blackboard = new GBlackboard(engine);
        theGlobalBlackboards()->insert(engine, blackboard);
    }

    GBlackboardPrivate *_this = const_cast<GBlackboardPrivate *>(d);
    _this->globalBlackboard = blackboard.data();
    return d->globalBlackboard;
}

GBlackboard *GBlackboard::sharedBlackboard() const
{
    Q_D(const GBlackboard);

    if (d->sharedBlackboard) {
        return d->sharedBlackboard;
    }

    if (!d->masterTree) {
        qWarning("GtGhost : Master tree is null.");
        return nullptr;
    }

    QObject *attached = qmlAttachedPropertiesObject<GBlackboard>(d->masterTree);
    if (attached) {
        GBlackboardPrivate *_this = const_cast<GBlackboardPrivate *>(d);
        _this->sharedBlackboard = qobject_cast<GBlackboard *>(attached);
    }

    return d->sharedBlackboard;
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

void GBlackboard::unset(const QString &key)
{
    Q_D(GBlackboard);
    d->datas.remove(key);
}

void GBlackboard::clear()
{
    Q_D(GBlackboard);
    d->datas.clear();
}

// class GBlackboardPrivate

GBlackboardPrivate::GBlackboardPrivate()
    : masterTree(nullptr)
    , targetNode(nullptr)
    , globalBlackboard(nullptr)
    , sharedBlackboard(nullptr)
{
}

GBlackboardPrivate::~GBlackboardPrivate()
{
}
