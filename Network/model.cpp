#include <QUrlQuery>
#include <QNetworkReply>
#include <QJsonArray>
#include <QNetworkRequest>
#include <QJsonDocument>

#include "model.h"

// INFO: https://open-meteo.com/
// Данные широты и долготы введены для Токио
// Это сделано в качестве примера

Model::Model(QObject *parent) : QObject(parent)
{
    connect(&m_networkManager, &QNetworkAccessManager::finished, this, &Model::onFinished);
}

QList<Model::CurrentWeather> const& Model::currentweather() const
{
    return m_currentweather;
}

void Model::updateCurrentweather()
{
    qDebug() << "Access the weather API";

    QUrlQuery query;
    query.addQueryItem("latitude", "35.6895");     // Для примера выбран город Токио
    query.addQueryItem("longitude", "139.6917");   //
    query.addQueryItem("current", "temperature_2m,relative_humidity_2m,wind_speed_10m");
    query.addQueryItem("hourly", "temperature_2m,relative_humidity_2m,wind_speed_10m");

    QUrl requestUrl {"https://api.open-meteo.com/v1/forecast"};
    requestUrl.setQuery(query);
    QNetworkRequest request(requestUrl);
    m_networkManager.get(request);
}

QString Model::tempUnits() const
{
    return m_tempUnits;
}

QString Model::windSpeedUnits() const
{
    return m_windSpeedUnits;
}

QString Model::humidityUnits() const
{
    return m_humidityUnits;
}

void Model::onFinished(QNetworkReply* reply)
{
    QString const data = reply->readAll();
    qDebug() << "Request finished" << reply->error() << data;

    QJsonDocument const doc = QJsonDocument::fromJson(data.toUtf8());
    if (doc.isNull() || !doc.isObject()) {
        qDebug() << "Invalid JSON";
        return;
    }

    parse(doc.object());
    emit currentweatherUpdated();
}

void Model::parse(const QJsonObject &json)
{
    m_currentweather.clear();

    m_currentweather.push_back({QDateTime::fromString(json["current"].toObject()["time"].toString(), Qt::ISODate),
        json["current"].toObject()["temperature_2m"].toDouble(),
            json["current"].toObject()["wind_speed_10m"].toDouble(),
                json["current"].toObject()["relative_humidity_2m"].toInt()
    });

    auto const timeArray = json["hourly"].toObject()["time"].toArray();
    auto const temperatureArray = json["hourly"].toObject()["temperature_2m"].toArray();
    auto const windSpeedArray = json["hourly"].toObject()["wind_speed_10m"].toArray();
    auto const humidityArray = json["hourly"].toObject()["relative_humidity_2m"].toArray();

    auto const size = qMin(timeArray.size(),
                           qMin(temperatureArray.size(),
                                qMin(windSpeedArray.size(),
                                     humidityArray.size())));

    for (auto i = 0; i < size; ++i) {
        m_currentweather.push_back({QDateTime::fromString(timeArray[i].toString(), Qt::ISODate),
            temperatureArray[i].toDouble(),
                windSpeedArray[i].toDouble(),
                    humidityArray[i].toInt()
        });
    }

    m_tempUnits = json["current_units"].toObject()["temperature_2m"].toString();
    m_windSpeedUnits = json["current_units"].toObject()["wind_speed_10m"].toString();
    m_humidityUnits = json["current_units"].toObject()["relative_humidity_2m"].toString();
}
