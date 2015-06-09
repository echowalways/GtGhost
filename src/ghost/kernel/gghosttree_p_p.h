#ifndef GGHOSTTREE_P_P_H
#define GGHOSTTREE_P_P_H

#include <QtQml/QQmlListProperty>

#include "gghostsourcenode_p_p.h"
#include "gghosttree_p.h"
#include "gghostnode_p.h"
#include "gghostnode_p_p.h"

class GGhostTreePrivate : public GGhostSourceNodePrivate
{
    Q_DECLARE_PUBLIC(GGhostTree)

public:
    GGhostTreePrivate();
    virtual ~GGhostTreePrivate();

public:
    static GGhostNodePrivate *cast(GGhostNode *node) { return GGhostNodePrivate::cast(node); }
    static const GGhostNodePrivate *cast(const GGhostNode *node) { return GGhostNodePrivate::cast(node); }

    virtual void onChildStatusChanged(GGhostSourceNode *childNode) Q_DECL_FINAL;

public:
    virtual bool initialize() Q_DECL_FINAL;

    virtual void reset() Q_DECL_FINAL;
    virtual void execute() Q_DECL_FINAL;
    virtual void terminate() Q_DECL_FINAL;

private:
    void onStatusChanged(Ghost::Status status);

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

inline QQmlListProperty<GGhostNode> GGhostTreePrivate::_q_childNodes()
{
    return QQmlListProperty<GGhostNode>(q_func(), childNodes);
}

inline GGhostData *GGhostTreePrivate::_q_data() const
{
    return extraData;
}

#endif // GGHOSTTREE_P_P_H
