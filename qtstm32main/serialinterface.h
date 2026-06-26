#ifndef SERIALINTERFACE_H
#define SERIALINTERFACE_H

#include <QString>
#include <QByteArray>

class SerialInterface {
public:
    virtual ~SerialInterface() {}
    virtual bool connect(const QString &port, int baudRate) = 0;
    virtual void disconnect() = 0;
    virtual bool isConnected() const = 0;
    virtual void sendData(const QByteArray &data) = 0;

    // статистика — общая для любого интерфейса
    virtual long getByteCount() const = 0;
    virtual long getOverflowCount() const = 0;
    virtual long getBufferedCount() const = 0;
    virtual long getSpeed() const = 0;
};

#endif // SERIALINTERFACE_H
