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

void GGhostNode::setComment(const QString &value)
{
    Q_D(GGhostNode);

    if (value != d->comment) {
        d->comment = value;
        emit commentChanged(value);
    }
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

QString GGhostNode::comment() const
{
    Q_D(const GGhostNode);
    return d->comment;
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

void GGhostNodePrivate::setStatus(Ghost::Status status)
{
    Q_Q(GGhostNode);

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

    if (comment.isEmpty()) {
        qCDebug(qlcGhostNode,
                "Status: '%s' ==> '%s' : %s %s(%p)",
                Ghost::toString(this->status), Ghost::toString(status),
                ((Ghost::Running == status) ? "-->" : "<--"),
                q->metaObject()->className(), q);
    } else {
        qCDebug(qlcGhostNode).nospace()
                << "Status: '" << Ghost::toString(this->status)
                << "' ==> '" << Ghost::toString(status)
                << "' :" << ((Ghost::Running == status) ? " --> " : " <-- ")
                << comment.toUtf8().constData();
    }

#endif // QT_NO_DEBUG

    if (status != this->status) {
        this->status = status;
        emit q->statusChanged(status);

        if (masterTree
                && (Ghost::Invalid != status)
                && (Ghost::StandBy != status)
                && (Ghost::Running != status)) {
            cast(masterTree)->postConfirmEvent(q);
        }
    }
}

void GGhostNodePrivate::postExecuteEvent(GGhostNode *target)
{
    if (masterTree) {
        cast(masterTree)->postExecuteEvent(target);
    }
}

void GGhostNodePrivate::postConfirmEvent(GGhostNode *source)
{
    if (masterTree) {
        cast(masterTree)->postConfirmEvent(source);
    }
}

void GGhostNodePrivate::executeEvent(GGhostExecuteEvent *event)
{
    Q_UNUSED(event);

    this->execute();
}

void GGhostNodePrivate::confirmEvent(GGhostConfirmEvent *event)
{
    Q_UNUSED(event);
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

bool GGhostNodePrivate::initialize()
{
    bool r = initialize(childNodes);
    if (r) {
        setStatus(Ghost::StandBy);
    }
    return r;
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
        // 开始初始化子节点
        if (!childptr->initialize()) {
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

// moc_gghostnode_p.cpp
#include "moc_gghostnode_p.cpp"
