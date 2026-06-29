#ifndef UARTINTERFACE_H
#define UARTINTERFACE_H
#include "serialinterface.h"
#include <QSerialPort>
class UartInterface : public SerialInterface {
public:
    UartInterface();

    bool connect(const QString &port, int baudRate) override; // соединить
    void disconnect() override; // отключить
    bool isConnected() const override; // проверка на соединение
    void sendData(const QByteArray &data) override; // отправить

    // --- Геттеры ---
    long getByteCount() const override;
    long getOverflowCount() const override;
    long getBufferedCount() const override;
    long getSpeed() const override;
    QSerialPort* getSerial() const;

    // --- Специфичное для UART ---
    void parseData(const QString &line); // получить статистику метод парсинга

private:
    QSerialPort *m_serial;
    long m_byteCount;
    long m_overflowCount;
    long m_bufferedCount;
    long m_speed;
};

#endif // UARTINTERFACE_H
