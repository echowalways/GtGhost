#ifndef GGHOSTNODE_P_H
#define GGHOSTNODE_P_H

#include <QtQml/QJSValue>
#include <QtQml/QQmlParserStatus>

#include "gghostsourcenode_p.h"

class GGhostNode;
typedef QList<GGhostNode *> GGhostNodeList;
class GGhostTree;

class GGhostData;

class GGhostNodePrivate;
class GGhostNode : public GGhostSourceNode, public QQmlParserStatus
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(GGhostNode)
    Q_PROPERTY(GGhostTree* masterTree READ masterTree CONSTANT)
    Q_PROPERTY(GGhostNode* parentNode READ parentNode CONSTANT)
    Q_PROPERTY(Ghost::BaseType baseType READ baseType CONSTANT)
    Q_PROPERTY(Ghost::NodeType nodeType READ nodeType CONSTANT)
    Q_PRIVATE_PROPERTY(d_func(), QQmlListProperty<GGhostNode> childNodes READ _q_childNodes CONSTANT DESIGNABLE false)
    Q_PROPERTY(QJSValue precondition READ precondition WRITE setPrecondition NOTIFY preconditionChanged)
    Q_PROPERTY(QJSValue weight READ weight WRITE setWeight NOTIFY weightChanged)
    Q_PRIVATE_PROPERTY(d_func(), GGhostData* data READ _q_data CONSTANT)
    Q_INTERFACES(QQmlParserStatus)
    Q_CLASSINFO("DefaultProperty", "childNodes")

protected:
    GGhostNode(GGhostNodePrivate &dd, QObject *parent);

Q_SIGNALS:
    void initialized();
public:
    GGhostTree *masterTree() const;
    GGhostNode *parentNode() const;
    Ghost::BaseType baseType() const;
    Ghost::NodeType nodeType() const;
    GGhostNodeList childNodes() const;

Q_SIGNALS:
    void preconditionChanged(const QJSValue &value);
    void weightChanged(const QJSValue &value);
public:
    void setPrecondition(const QJSValue &value);
    void setWeight(const QJSValue &value);
    QJSValue precondition() const;
    QJSValue weight() const;

protected:
    virtual void classBegin() Q_DECL_OVERRIDE;
    virtual void componentComplete() Q_DECL_OVERRIDE;
};

#endif // GGHOSTNODE_P_H
