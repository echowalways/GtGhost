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

public:
    static GGhostTreePrivate *cast(GGhostTree *tree);
    static const GGhostTreePrivate *cast(const GGhostTree *tree);

    static GGhostNodePrivate *cast(GGhostNode *node);
    static const GGhostNodePrivate *cast(const GGhostNode *node);

    // Status
public:
    static const char *toString(Ghost::Status status);
    void setStatus(Ghost::Status status);
public:
    Ghost::Status status;

    // Event Queue
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
    void executeEvent(GGhostExecuteEvent *event);
    void confirmEvent(GGhostConfirmEvent *event);

    //
public:
    virtual bool initialize() Q_DECL_FINAL;

    virtual void reset() Q_DECL_FINAL;
    virtual void execute() Q_DECL_FINAL;
    virtual void terminate() Q_DECL_FINAL;

    // core datas
public:
    QQmlListProperty<GGhostNode> _q_childNodes();
public:
    GGhostNodeList childNodes;

    // extra datas
public:
    GGhostData *_q_data() const;
public:
    GGhostData *extraData;
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
