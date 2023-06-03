#ifndef ACTIONS_H
#define ACTIONS_H

#include <QObject>

class Actions : public QObject
{
    Q_OBJECT
public:
    explicit Actions(QObject *parent = 0);

signals:

public slots:
};

#endif // ACTIONS_H