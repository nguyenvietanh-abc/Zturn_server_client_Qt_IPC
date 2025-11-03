//server/SensorDataGenerator.cpp
#include "SensorDataGenerator.h"
#include <QRandomGenerator>

SensorDataGenerator::SensorDataGenerator(QObject *parent)
    : QObject(parent)               // Base init
    , m_rng(static_cast<unsigned int>(QRandomGenerator::global()->generate64() % UINT_MAX))  // tránh overflow)
    , m_distPitch(-90.0, 90.0)
    , m_distYaw(0.0, 360.0)
    , m_distTemp(15.0, 35.0)
    , m_distHum(30.0, 90.0)
    //, m_timer(new QTimer(this))  // init pointer với new QTimer(this) – dùng constructor QTimer(QObject*)
{
    m_timer = new QTimer(this);  // new trong body, an toàn sau base init
    connect(m_timer, &QTimer::timeout, this, &SensorDataGenerator::generateNewData);        // Kết nối signal-slot (sự kiện timeout → generate)
    m_currentData = {0.0, 0.0, 0.0, 0.0};
}

SensorDataGenerator::~SensorDataGenerator()
{
    stopGenerating();
    // m_timer tự delete nhờ RAII (parent = this, tự động giải phóng bộ nhớ)
}

void SensorDataGenerator::startGenerating(int intervalMs)
{
    if (!m_timer->isActive()){ return;
    m_timer->start(intervalMs);     // Start timer
    }
}

void SensorDataGenerator::stopGenerating()
{
    m_timer->stop();                // Stop timer (dừng đếm)
}

void SensorDataGenerator::generateNewData()
{
    QMutexLocker locker(&m_mutex);  // RAII lock (khóa tự động mở khi ra khỏi scope)
    m_currentData.pitch = m_distPitch(m_rng);
    m_currentData.yaw = m_distYaw(m_rng);
    m_currentData.temperature = m_distTemp(m_rng);
    m_currentData.humidity = m_distHum(m_rng);
}

SensorData SensorDataGenerator::currentData() const
{
    QMutexLocker locker(&m_mutex);
    return m_currentData;           // Copy thread-safe (sao chép an toàn luồng)
}

