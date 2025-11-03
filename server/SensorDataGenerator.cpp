//server/SensorDataGenerator.cpp
#include "SensorDataGenerator.h"
#include <QRandomGenerator>

SensorDataGenerator::SensorDataGenerator(QObject *parent)
    : QObject(parent)
    , m_rng(QRandomGenerator::global()->generate())
    , m_distPitch(-90.0, 90.0)
    , m_disrYaw(0.0, 360,0)
    , m_distTemp(15.0, 35.0)
    , m_dist_Hum(30.0, 90.0)
{
    m_timer = new QTimer(this);
    connect(m_timer, &QTimer::timeout, this, &SensorDataGenerator::generateNewData);
}

double SensorDataGenerator::generateValue(double min, double max) const
{
    //tránh lỗi ambiguous
    std::uniform_real_distribution<double> dist(min,max);
    return dist(*QRandomGenerator::global());
}

double SensorDataGenerator::getPitch() const
{
    return generateValue(-90.0, 90.0);
}

double SensorDataGenerator::getYaw() const
{
    return generateValue(0.0, 360.0);
}

double SensorDataGenerator::getTemperature() const
{
    return generateValue(15.0, 35.0);
}

double SensorDataGenerator::getHumidity() const
{
    return generateValue(30.0, 90.0);
}
