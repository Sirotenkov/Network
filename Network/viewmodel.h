#ifndef VIEWMODEL_H
#define VIEWMODEL_H

#include <QObject>

class viewmodel : public QObject
{
    Q_OBJECT
public:
    explicit viewmodel(QObject *parent = nullptr);

signals:

};

#endif // VIEWMODEL_H
