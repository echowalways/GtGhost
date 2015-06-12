#ifndef GGHOSTTREE_P_P_H
#define GGHOSTTREE_P_P_H

#include <private/qobject_p.h>

#include <QtCore/QQueue>
#include <QtQml/QQmlListProperty>

#include "gghosttree_p.h"

class GGhostNodePrivate;

class GGhostEvent;
class GGhostExecuteEvent;
class GGhostConfirmEvent;

class GGhostTreePrivate : public QObjectPrivate
{
    Q_DECLARE_PUBLIC(GGhostTree)

public:
    GGhostTreePrivate();
    virtual ~GGhostTreePrivate();

    // 快捷转换方法
public:
    static GGhostTreePrivate *cast(GGhostTree *tree);
    static const GGhostTreePrivate *cast(const GGhostTree *tree);
    static GGhostNodePrivate *cast(GGhostNode *node);
    static const GGhostNodePrivate *cast(const GGhostNode *node);

    // 状态
public:
    void setStatus(Ghost::Status status);
public:
    Ghost::Status status;

    // 事件队列
private:
    void postEvent(GGhostEvent *event);
    void _q_processEvents();
private:
    QQueue<GGhostEvent *> eventQueue;
    bool eventsProcessing;

public:
    void postExecuteEvent(GGhostNode *target);
    void postConfirmEvent(GGhostNode *source);
private:
    void processExecuteEvent(GGhostExecuteEvent *event);
    void processConfirmEvent(GGhostConfirmEvent *event);

    // 核心数据
public:
    QQmlListProperty<GGhostNode> _q_childNodes();
public:
    GGhostNodeList childNodes;

    // 扩展数据
public:
    GGhostData *_q_data() const;
public:
    GGhostData *extraData;

    //
public:
    bool initialize();

    void reset();
    void execute();
    void terminate();
};

inline GGhostTreePrivate *GGhostTreePrivate::cast(GGhostTree *tree)
{
    Q_CHECK_PTR(tree);
    return tree->d_func();
}

inline const GGhostTreePrivate *GGhostTreePrivate::cast(const GGhostTree *tree)
{
    Q_CHECK_PTR(tree);
    return tree->d_func();
}

inline QQmlListProperty<GGhostNode> GGhostTreePrivate::_q_childNodes()
{
    return QQmlListProperty<GGhostNode>(q_func(), childNodes);
}

inline GGhostData *GGhostTreePrivate::_q_data() const
{
    return extraData;
}

#endif // GGHOSTTREE_P_P_H
