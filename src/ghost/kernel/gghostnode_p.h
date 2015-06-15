#ifndef GGHOSTNODE_P_H
#define GGHOSTNODE_P_H

#include "gghostglobal.h"

class GGhostNodePrivate;
class GGhostNode : public QObject, public QQmlParserStatus
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(GGhostNode)
    Q_PROPERTY(Ghost::Status status READ status NOTIFY statusChanged)
    Q_PROPERTY(GGhostTree* masterTree READ masterTree CONSTANT)
    Q_PROPERTY(GGhostNode* parentNode READ parentNode CONSTANT)
    Q_PROPERTY(Ghost::BaseType baseType READ baseType CONSTANT)
    Q_PROPERTY(Ghost::NodeType nodeType READ nodeType CONSTANT)
    Q_PRIVATE_PROPERTY(d_func(), QQmlListProperty<GGhostNode> childNodes READ _q_childNodes CONSTANT DESIGNABLE false)
    Q_PROPERTY(QString comment READ comment WRITE setComment NOTIFY commentChanged)
    Q_PROPERTY(QJSValue precondition READ precondition WRITE setPrecondition NOTIFY preconditionChanged)
    Q_PROPERTY(QJSValue weight READ weight WRITE setWeight NOTIFY weightChanged)
    Q_CLASSINFO("DefaultProperty", "childNodes")
    Q_INTERFACES(QQmlParserStatus)

protected:
    GGhostNode(GGhostNodePrivate &dd, QObject *parent);

Q_SIGNALS:
    void statusChanged(Ghost::Status);
public:
    Ghost::Status status() const;

Q_SIGNALS:
    void initialized();
public:
    GGhostTree *masterTree() const;
    GGhostNode *parentNode() const;
    Ghost::BaseType baseType() const;
    Ghost::NodeType nodeType() const;
    GGhostNodeList childNodes() const;

Q_SIGNALS:
    void commentChanged(const QString &value);
    void preconditionChanged(const QJSValue &value);
    void weightChanged(const QJSValue &value);
public:
    void setComment(const QString &value);
    void setPrecondition(const QJSValue &value);
    void setWeight(const QJSValue &value);
    QString comment() const;
    QJSValue precondition() const;
    QJSValue weight() const;

private:
    virtual void classBegin() Q_DECL_FINAL;
    virtual void componentComplete() Q_DECL_FINAL;
};

#endif // GGHOSTNODE_P_H
