// server/SensorData.h
#ifndef SENSORDATA_H
#define SENSORDATA_H

#include <QMetaType>
#include <QJsonObject>

struct SensorData {
    double pitch{0.0};       // độ cao (elevation): -90 → 90
    double yaw{0.0};         // phương vị (azimuth): 0 → 360
    double temperature{0.0}; // °C: 15 → 35
    double humidity{0.0};    // %: 30 → 90

    QJsonObject toJson() const {
        QJsonObject obj;
        obj["pitch"] = pitch;
        obj["yaw"] = yaw;
        obj["temperature"] = temperature;
        obj["humidity"] = humidity;
        return obj;
    }

    static SensorData fromJson(const QJsonObject &obj) {
        SensorData data;
        data.pitch = obj["pitch"].toDouble();
        data.yaw = obj["yaw"].toDouble();
        data.temperature = obj["temperature"].toDouble();
        data.humidity = obj["humidity"].toDouble();
        return data;
    }
};

Q_DECLARE_METATYPE(SensorData)

#endif // SENSORDATA_H
