#include "gghostnode_p.h"
#include "gghostnode_p_p.h"
#include "gghostnode.qdoc"

#include <QtCore/QLoggingCategory>

Q_LOGGING_CATEGORY(qlcGhostNode, "GtGhost.GhostNode")

// class GGhostNode

GGhostNode::GGhostNode(GGhostNodePrivate &dd, QObject *parent)
    : GGhostSourceNode(dd, parent)
{
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
    : masterTree(0)
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
        childptr->extraData = extraData;
        // 开始初始化子节点
        if (childptr->initialize()) {
            childptr->parentSourceNode = q;
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
