// server/SensorDataGenerator.h
#ifndef SENSORDATAGENERATOR_H
#define SENSORDATAGENERATOR_H

#include <QObject>
#include <QTimer>
#include <QMutex>
#include <random>
#include "SensorData.h"

class SensorDataGenerator : public QObject
{
    Q_OBJECT
public:
    explicit SensorDataGenerator(QObject *parent = nullptr);
    ~SensorDataGenerator();

    SensorData currentData() const;
    void startGenerating(int intervalMs = 1); // ~1000Hz
    void stopGenerating();

private:
    void generateNewData();

    mutable QMutex m_mutex;
    SensorData m_currentData;
    QTimer *m_timer{nullptr};
    std::mt19937 m_rng;
    std::uniform_real_distribution<double> m_distPitch;
    std::uniform_real_distribution<double> m_distYaw;
    std::uniform_real_distribution<double> m_distTemp;
    std::uniform_real_distribution<double> m_distHum;
};

#endif // SENSORDATAGENERATOR_H
