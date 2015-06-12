#include "gghostnode_p.h"
#include "gghostnode_p_p.h"

#include <QtCore/QLoggingCategory>

#include "gghostevent.h"
#include "gghosttree_p.h"
#include "gghosttree_p_p.h"

Q_LOGGING_CATEGORY(qlcGhostNode, "GtGhost.GhostNode")

// class GGhostNode

GGhostNode::GGhostNode(GGhostNodePrivate &dd, QObject *parent)
    : QObject(dd, parent)
{
}

Ghost::Status GGhostNode::status() const
{
    Q_D(const GGhostNode);
    return d->status;
}

GGhostTree *GGhostNode::masterTree() const
{
    Q_D(const GGhostNode);
    return d->masterTree;
}

GGhostNode *GGhostNode::parentNode() const
{
    Q_D(const GGhostNode);
    return d->parentNode;
}

Ghost::BaseType GGhostNode::baseType() const
{
    Q_D(const GGhostNode);
    return d->baseType;
}

Ghost::NodeType GGhostNode::nodeType() const
{
    Q_D(const GGhostNode);
    return d->nodeType;
}

GGhostNodeList GGhostNode::childNodes() const
{
    Q_D(const GGhostNode);
    return d->childNodes;
}

void GGhostNode::setPrecondition(const QJSValue &value)
{
    Q_D(GGhostNode);

    if (!d->precondition.equals(value)) {
        d->precondition = value;
        emit preconditionChanged(value);
    }
}

void GGhostNode::setWeight(const QJSValue &value)
{
    Q_D(GGhostNode);

    if (!d->weight.equals(value)) {
        d->weight = value;
        emit weightChanged(value);
    }
}

QJSValue GGhostNode::precondition() const
{
    Q_D(const GGhostNode);
    return d->precondition;
}

QJSValue GGhostNode::weight() const
{
    Q_D(const GGhostNode);
    return d->weight;
}

void GGhostNode::classBegin()
{
}

void GGhostNode::componentComplete()
{
}

// class GGhostNodePrivate

GGhostNodePrivate::GGhostNodePrivate(Ghost::BaseType baseType, Ghost::NodeType nodeType)
    : status(Ghost::Invalid)
    , masterTree(0)
    , parentNode(0)
    , baseType(baseType)
    , nodeType(nodeType)
    , extraData(0)
    , sortIndex(0)
{
}

GGhostNodePrivate::~GGhostNodePrivate()
{
}

GGhostTreePrivate *GGhostNodePrivate::cast(GGhostTree *tree)
{
    return GGhostTreePrivate::cast(tree);
}

const GGhostTreePrivate *GGhostNodePrivate::cast(const GGhostTree *tree)
{
    return GGhostTreePrivate::cast(tree);
}

void GGhostNodePrivate::postExecuteEvent(GGhostNode *target)
{
    if (!masterTree) {
        cast(masterTree)->postExecuteEvent(target);
    }
}

void GGhostNodePrivate::postConfirmEvent(GGhostNode *source)
{
    if (!masterTree) {
        cast(masterTree)->postConfirmEvent(source);
    }
}

void GGhostNodePrivate::executeEvent(GGhostExecuteEvent *event)
{
    Q_UNUSED(event);

    execute();
}

void GGhostNodePrivate::confirmEvent(GGhostConfirmEvent *event)
{
    Q_UNUSED(event);
}

bool GGhostNodePrivate::initialize()
{
    bool r = initialize(childNodes);
    if (r) {
        setStatus(Ghost::StandBy);
    }
    return r;
}

const char *GGhostNodePrivate::toString(Ghost::Status status)
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

void GGhostNodePrivate::setStatus(Ghost::Status status)
{
    Q_Q(GGhostNode);

    if (this->status == status) {
        qCDebug(qlcGhostNode, "Same Status %s %s", toString(status), q->metaObject()->className());
        return;
    }

#if !defined(QT_NO_DEBUG)

    qCDebug(qlcGhostNode,
            "Status: '%s' ==> '%s' : %s %s(%p)",
            toString(this->status), toString(status),
            ((Ghost::Running == status) ? "-->" : "<--"),
            q->metaObject()->className(), q);

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



    //    if (summary.isEmpty()) {
    //        qCDebug(qlcGhostNode,
    //                "Status: '%s' ==> '%s' : %s %s(%p)",
    //                toString(this->status), toString(status),
    //                ((Ghost::Running == status) ? "-->" : "<--"),
    //                q->metaObject()->className(), q);
    //    } else {
    //        qCDebug(qlcGhostNode).nospace()
    //                << "Status: '" << toString(this->status)
    //                << "' ==> '" << toString(status)
    //                << "' :" << ((Ghost::Running == status) ? " --> " : " <-- ")
    //                << summary.toUtf8().constData();
    //    }

#endif // QT_NO_DEBUG

    if (status != this->status) {
        this->status = status;
        emit q->statusChanged(status);

        if (parentNode && masterTree) {
            GGhostTreePrivate::cast(masterTree)->postConfirmEvent(q);
        }
    }
}

bool GGhostNodePrivate::initialize(const GGhostNodeList &childNodes)
{
    Q_Q(GGhostNode);

    bool hasError = false;

    foreach (GGhostNode *childNode, childNodes) {
        GGhostNodePrivate *childptr = cast(childNode);
        // 初始化子节点数据
        childptr->masterTree = masterTree;
        childptr->parentNode = q;
        childptr->extraData = extraData;
        // 开始初始化子节点
        if (childptr->initialize()) {
            // childptr->parentNode = 0;
        } else {
            hasError = true;
        }
    }

    if (Ghost::CompositeNode == baseType) {
        if (childNodes.isEmpty()) {
            qCWarning(qlcGhostNode)
                    << "Must have at least one child item.";
            hasError = true;
        }
    } else if (Ghost::DecoratorNode == baseType) {
        if (childNodes.count() != 1) {
            qCWarning(qlcGhostNode)
                    << "Allows only one child node.";
            hasError = true;
        }
    } else if (Ghost::LeafNode == baseType) {
        if (!childNodes.isEmpty()) {
            qCWarning(qlcGhostNode)
                    << "Does not allow any child items.";
            hasError = true;
        }
    } else {
        Q_UNREACHABLE();
    }

    if (!hasError) {
        emit q->initialized();
    }

    return !hasError;
}

bool GGhostNodePrivate::callPrecondition()
{
    if (precondition.isUndefined()) {
        return true;
    }

    QJSValue value = precondition;

    if (precondition.isCallable()) {
        value = precondition.call();
    }

    if (value.isBool()) {
        return value.toBool();
    } else if (value.isError()) {
        // error
    }

    return false;
}

uint GGhostNodePrivate::callWeight()
{
    if (weight.isUndefined()) {
        return 1u;
    }

    QJSValue value = weight;

    if (weight.isCallable()) {
        value = weight.call();
    }

    if (value.isNumber()) {
        return qMax(value.toUInt(), 1u);
    } else if (value.isError()) {
        // error
    }

    return 1u;
}

bool GGhostNodePrivate::greatThan(GGhostNode *leftChildNode, GGhostNode *rightChildNode)
{
    return cast(leftChildNode)->sortIndex > cast(rightChildNode)->sortIndex;
}

void GGhostNodePrivate::sort(GGhostNodeList &childNodes)
{
    std::sort(childNodes.begin(), childNodes.end(), &GGhostNodePrivate::greatThan);
}

// moc_gghostnode_p.cpp
#include "moc_gghostnode_p.cpp"
