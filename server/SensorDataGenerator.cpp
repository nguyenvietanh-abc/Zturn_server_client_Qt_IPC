#include "SensorDataGenerator.h"

SensorDataGenerator::SensorDataGenerator(QObject *parent)
    : QObject(parent)
{
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
