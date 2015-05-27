#ifndef GACTIONITEM_H
#define GACTIONITEM_H

#include "gghostitem.h"

class GActionItemPrivate;
class GActionItem : public GGhostItem
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(GActionItem)

public:
    explicit GActionItem(QObject *parent = 0);

private:
    virtual Ghost::NodeType nodeType() const Q_DECL_FINAL;
    virtual Ghost::ItemType itemType() const Q_DECL_FINAL;

Q_SIGNALS:
    void reset();
    void execute();
    void terminate();

public Q_SLOTS:
    void setSuccessStatus();
    void setFailureStatus();
    void setStoppedStatus();
};

#endif // GACTIONITEM_H
