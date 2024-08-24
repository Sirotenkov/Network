#ifndef MODEL_H
#define MODEL_H

#include <QObject>
#include <QDateTime>
#include <QJsonObject>
#include <QNetworkAccessManager>

class Model : public QObject
{
    Q_OBJECT

public:
    explicit Model(QObject *parent = nullptr);

    struct CurrentWeather
    {
        QDateTime currentDateTime;
        double temp;
        double windSpeed;
        int humidity;
    };

    QList<CurrentWeather> const& currentweather() const;

    void updateCurrentweather();

    QString tempUnits() const;
    QString windSpeedUnits() const;
    QString humidityUnits() const;

signals:
    void currentweatherUpdated();

private slots:
    void onFinished(QNetworkReply* reply);

private:
    void parse(QJsonObject const& json);
    QList<CurrentWeather> m_currentweather;

    QString m_tempUnits;
    QString m_windSpeedUnits;
    QString m_humidityUnits;

    QNetworkAccessManager m_networkManager;
};

#endif // MODEL_H
