#ifndef GGHOSTSOURCENODE_P_H
#define GGHOSTSOURCENODE_P_H

#include <QtCore/QObject>

#include "gghostnamespace.h"

class GGhostSourceNodePrivate;
class GGhostSourceNode : public QObject
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(GGhostSourceNode)
    Q_PROPERTY(Ghost::Status status READ status NOTIFY statusChanged)
    Q_PROPERTY(QString summary READ summary WRITE setSummary NOTIFY summaryChanged)

public:
    GGhostSourceNode(GGhostSourceNodePrivate &dd, QObject *parent);

Q_SIGNALS:
    void statusChanged(Ghost::Status);
public Q_SLOTS:
    Ghost::Status status() const;

Q_SIGNALS:
    void summaryChanged(const QString &value);
public:
    void setSummary(const QString &value);
    QString summary() const;
};

#endif // GGHOSTSOURCENODE_P_H
