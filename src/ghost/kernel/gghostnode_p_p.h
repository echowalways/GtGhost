#ifndef GGHOSTNODE_P_P_H
#define GGHOSTNODE_P_P_H

#include <QtQml/QQmlListProperty>

#include "gghostsourcenode_p_p.h"
#include "gghostnode_p.h"

class GGhostNodePrivate : public GGhostSourceNodePrivate
{
    Q_DECLARE_PUBLIC(GGhostNode)

public:
    explicit GGhostNodePrivate(Ghost::BaseType baseType, Ghost::NodeType nodeType);
    virtual ~GGhostNodePrivate();

public:
    static GGhostNodePrivate *cast(GGhostNode *node) { return node->d_func(); }
    static const GGhostNodePrivate *cast(const GGhostNode *node) { return node->d_func(); }

public:
    virtual bool initialize() Q_DECL_OVERRIDE;

public:
    bool initialize(const GGhostNodeList &childNodes);

    // core datas
public:
    QQmlListProperty<GGhostNode> _q_childNodes();
public:
    GGhostTree *masterTree;
    GGhostNode *parentNode;
    Ghost::BaseType baseType;
    Ghost::NodeType nodeType;
    GGhostNodeList childNodes;

public:
    bool callPrecondition();
    uint callWeight();
private:
    QJSValue precondition;
    QJSValue weight;

    // extra datas
public:
    GGhostData *_q_data() const;
public:
    GGhostData *extraData;

public:
    static bool greatThan(GGhostNode *leftChildNode, GGhostNode *rightChildNode);
    static void sort(GGhostNodeList &childNodes);
public:
    uint sortIndex;
};

inline QQmlListProperty<GGhostNode> GGhostNodePrivate::_q_childNodes()
{
    return QQmlListProperty<GGhostNode>(q_func(), childNodes);
}

inline GGhostData *GGhostNodePrivate::_q_data() const
{
    return extraData;
}

#endif // GGHOSTNODE_P_P_H
