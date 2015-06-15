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

    // 快捷转换方法
public:
    static GGhostNodePrivate *cast(GGhostNode *node);
    static const GGhostNodePrivate *cast(const GGhostNode *node);
    static GGhostTreePrivate *cast(GGhostTree *tree);
    static const GGhostTreePrivate *cast(const GGhostTree *tree);

    // 状态
public:
    void setStatus(Ghost::Status status);
public:
    Ghost::Status status;

    // 事件队列
public:
    void postExecuteEvent(GGhostNode *target);
    void postConfirmEvent(GGhostNode *source);
public:
    virtual void executeEvent(GGhostExecuteEvent *event);
    virtual void confirmEvent(GGhostConfirmEvent *event);

    // 核心数据
public:
    QQmlListProperty<GGhostNode> _q_childNodes();
private:
    static void childNodes_append(QQmlListProperty<GGhostNode> *prop, GGhostNode *v);
    static GGhostNode *childNodes_at(QQmlListProperty<GGhostNode> *prop, int i);
    static void childNodes_clear(QQmlListProperty<GGhostNode> *prop);
    static int childNodes_count(QQmlListProperty<GGhostNode> *prop);
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

    // 节点排序
public:
    static bool greatThan(GGhostNode *leftChildNode, GGhostNode *rightChildNode);
    static void sort(GGhostNodeList &childNodes);
public:
    uint sortIndex;

    // 扩展数据
public:
    QString comment;

    //
public:
    virtual bool initialize();

public:
    virtual void reset() = 0;
    virtual void execute() = 0;
    virtual void terminate() = 0;

public:
    bool initialize(const GGhostNodeList &childNodes);
};

inline GGhostNodePrivate *GGhostNodePrivate::cast(GGhostNode *node)
{
    Q_CHECK_PTR(node);
    return node->d_func();
}

inline const GGhostNodePrivate *GGhostNodePrivate::cast(const GGhostNode *node)
{
    Q_CHECK_PTR(node);
    return node->d_func();
}

inline QQmlListProperty<GGhostNode> GGhostNodePrivate::_q_childNodes()
{
    return QQmlListProperty<GGhostNode>(q_func(), &childNodes,
                                        &GGhostNodePrivate::childNodes_append,
                                        &GGhostNodePrivate::childNodes_count,
                                        &GGhostNodePrivate::childNodes_at,
                                        &GGhostNodePrivate::childNodes_clear);
}

#endif // GGHOSTNODE_P_P_H
