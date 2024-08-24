#ifndef VIEWMODEL_H
#define VIEWMODEL_H

#include <QObject>
#include <QDateTime>
#include <QTimer>

class Model;

class ViewModel : public QObject
{
    Q_OBJECT

public:
    explicit ViewModel(Model* model, QObject *parent = nullptr);

    Q_PROPERTY(QDateTime currentDateTime READ currentDateTime NOTIFY currentweatherUpdated)

    Q_PROPERTY(double temp READ temp NOTIFY currentweatherUpdated)
    Q_PROPERTY(double windSpeed READ windSpeed NOTIFY currentweatherUpdated)
    Q_PROPERTY(int humidity READ humidity NOTIFY currentweatherUpdated)

    Q_PROPERTY(QString tempUnits READ tempUnits NOTIFY currentweatherUpdated)
    Q_PROPERTY(QString windSpeedUnits READ windSpeedUnits NOTIFY currentweatherUpdated)
    Q_PROPERTY(QString humidityUnits READ humidityUnits NOTIFY currentweatherUpdated)

    QDateTime currentDateTime() const;

    double temp() const;
    double windSpeed() const;
    int humidity() const;

    QString tempUnits() const;
    QString windSpeedUnits() const;
    QString humidityUnits() const;

signals:
    void currentweatherUpdated();

private slots:
    void onTimeout();

private:
    Model* m_model = nullptr;
    QTimer m_timer;

    // INFO: Интервал обновления данных с сайта
    int m_interval = 60 * 60 * 1000;

    QString m_tempUnits;
    QString m_windSpeedUnits;
    QString m_humidityUnits;
};

#endif // VIEWMODEL_H
