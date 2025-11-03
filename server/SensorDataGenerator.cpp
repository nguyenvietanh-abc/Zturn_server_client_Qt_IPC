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

SensorDataGenerator::~SensorDataGenerator()
{
    stopGenerating();
}

void SensorDataGenerator::startGenerating(int intervalMs)
{
    if (m_timer->isActive()) return;
    m_timer->start(intervalMs);
}

void SensorDataGenerator::stopGenerating()
{
    m_timer->stop();
}

void SensorDataGenerator::generateNewData()
{
    QMutexLocker locker(&m_mutex);
    m_currentData.pitch = m_distPitch(m_rng);
    m_currentData.yaw = m_distYaw(m_rng);
    m_currentData.temperature = m_distTemp(m_rng);
    m_currentData.humidity = m_distHum(m_rng);
}

SensorData SensorDataGenerator::currentData() const
{
    QMutexLocker locker(&m_mutex);
    return m_currentData;
}

