// server/SensorDataGenerator.h
#ifndef SENSORDATAGENERATOR_H
#define SENSORDATAGENERATOR_H

#include <QObject>
#include <QTimer>
#include <QMutex>
#include <random>               //Để khai báo ngẫu nhiên dùng std::mt19937dùng thuật toán Mersenne Twister 19937.
#include "SensorData.h"

class SensorDataGenerator : public QObject
{
    Q_OBJECT
public:
    explicit SensorDataGenerator(QObject *parent = nullptr);
    ~SensorDataGenerator();

    SensorData currentData() const;
    void startGenerating(int intervalMs = 1); // ~1000Hz = 1ms chu kì thời gian giữa các lần sinh data
    void stopGenerating();

private:
    void generateNewData();

    mutable QMutex m_mutex;             //Đồng bộ hóa luồng, chỉ cho phép 1 luồng truy cập tài nguyên tại 1 tdiem
    SensorData m_currentData{0.0, 0.0, 0.0, 0.0};  // Init explicit (khởi tạo rõ ràng)
    QTimer *m_timer{nullptr};  // init nullptr ở header, không new ở initializer list
    std::mt19937 m_rng;         //Khai báo biến sinh số ngẫu nhiên (m_rng)
    std::uniform_real_distribution<double> m_distPitch{-90.0, 90.0};;         //khai báo một phân phối đều (uniform distribution)
    std::uniform_real_distribution<double> m_distYaw{0.0, 360.0};           //cho số thực kiểu double
    std::uniform_real_distribution<double> m_distTemp{15.0, 35.0};
    std::uniform_real_distribution<double> m_distHum{30.0, 90.0};
};

#endif // SENSORDATAGENERATOR_H
