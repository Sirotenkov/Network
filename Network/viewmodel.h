#ifndef VIEWMODEL_H
#define VIEWMODEL_H

#include <QObject>

class ViewModel : public QObject
{
    Q_OBJECT

public:
    explicit ViewModel(QObject *parent = nullptr);

signals:

};

#endif // VIEWMODEL_H
