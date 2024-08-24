#include "model.h"
#include "viewmodel.h"

ViewModel::ViewModel(Model* model, QObject *parent) : QObject(parent), m_model(model)
{
    connect(m_model, &Model::currentweatherUpdated, this, &ViewModel::currentweatherUpdated);
    connect(&m_timer, &QTimer::timeout, this, &ViewModel::onTimeout);
    m_timer.start(m_interval);

    onTimeout();
}

QDateTime ViewModel::currentDateTime() const
{
    auto const currentweather = m_model->currentweather();
    return !currentweather.isEmpty() ? currentweather.front().currentDateTime
                : QDateTime::currentDateTimeUtc();
}

double ViewModel::temp() const
{
    auto const currentweather = m_model->currentweather();
    return !currentweather.isEmpty() ? currentweather.front().temp : 0.0;
}

double ViewModel::windSpeed() const
{
    auto const currentweather = m_model->currentweather();
    return !currentweather.isEmpty() ? currentweather.front().windSpeed : 0.0;
}

int ViewModel::humidity() const
{
    auto const currentweather = m_model->currentweather();
    return !currentweather.isEmpty() ? currentweather.front().humidity: 0;
}

QString ViewModel::tempUnits() const
{
    return m_model->tempUnits();
}

QString ViewModel::windSpeedUnits() const
{
    return m_model->windSpeedUnits();
}

QString ViewModel::humidityUnits() const
{
    return m_model->humidityUnits();
}

void ViewModel::onTimeout()
{
    m_model->updateCurrentweather();
}
