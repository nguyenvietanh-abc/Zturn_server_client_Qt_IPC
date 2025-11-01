#ifndef SENSORDATAGENERATOR_H
#define SENSORDATAGENERATOR_H

#include <QObject>
#include <QRandomGenerator>

class SensorDataGenerator : public QObject
{
    Q_OBJECT
public:
    explicit SensorDataGenerator(QObject *parent = nullptr);

    double getPitch() const;
    double getYaw() const;
    double getTemperature() const;
    double getHumidity() const;

private:
    double generateValue(double min, double max) const;
};

#endif // SENSORDATAGENERATOR_H
