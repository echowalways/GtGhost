#ifndef GGHOSTNODE_P_P_H
#define GGHOSTNODE_P_P_H

#include <private/qobject_p.h>
#include <QtQml/QQmlListProperty>

#include "gghostnode_p.h"

class GGhostTreePrivate;

class GGhostEvent;
class GGhostExecuteEvent;
class GGhostConfirmEvent;

class GGhostNodePrivate : public QObjectPrivate
{
    Q_DECLARE_PUBLIC(GGhostNode)

public:
    GGhostNodePrivate(Ghost::BaseType baseType, Ghost::NodeType nodeType);
    virtual ~GGhostNodePrivate();

public:
    static GGhostNodePrivate *cast(GGhostNode *node) { Q_CHECK_PTR(node); return node->d_func(); }
    static const GGhostNodePrivate *cast(const GGhostNode *node) { Q_CHECK_PTR(node); return node->d_func(); }

    static GGhostTreePrivate *cast(GGhostTree *tree);
    static const GGhostTreePrivate *cast(const GGhostTree *tree);

    // Status
public:
    static const char *toString(Ghost::Status status);
    void setStatus(Ghost::Status status);
public:
    Ghost::Status status;

    // Event
public:
    void postExecuteEvent(GGhostNode *target);
    void postConfirmEvent(GGhostNode *source);
public:
    virtual void executeEvent(GGhostExecuteEvent *event);
    virtual void confirmEvent(GGhostConfirmEvent *event);

    //
public:
    virtual bool initialize();

public:
    virtual void reset() = 0;
    virtual void execute() = 0;
    virtual void terminate() = 0;

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
