#include "uartinterface.h"

UartInterface::UartInterface()
    : m_serial(new QSerialPort())
    , m_byteCount(0)
    , m_overflowCount(0)
    , m_bufferedCount(0)
    , m_speed(0)
{}

bool UartInterface::connect(const QString &port, int baudRate) // подключить
{
    m_serial->setPortName(port);
    m_serial->setBaudRate(baudRate);
    m_serial->setDataBits(QSerialPort::Data8);
    m_serial->setParity(QSerialPort::NoParity);
    m_serial->setStopBits(QSerialPort::OneStop);
    return m_serial->open(QIODevice::ReadWrite);
}

void UartInterface::disconnect() // отключить
{
    if (m_serial->isOpen())
        m_serial->close();
}

bool UartInterface::isConnected() const // проверка соединения
{
    return m_serial->isOpen();
}

void UartInterface::sendData(const QByteArray &data) // отправка данных
{
    if (m_serial->isOpen())
        m_serial->write(data);
}

long UartInterface::getByteCount() const { return m_byteCount; }
long UartInterface::getOverflowCount() const { return m_overflowCount; }
long UartInterface::getBufferedCount() const { return m_bufferedCount; }
long UartInterface::getSpeed() const { return m_speed; }

void UartInterface::parseData(const QString &line)
{
    auto extract = [&](const QString &key) -> long { // лямбда-функция для извлечения значений из строки
        int start = line.indexOf(key); // ищем ключ
        if (start == -1) return -1; // отрицательные значения не идут в статистику
        start += key.length(); // убираем сам ключ из передаваемого значения
        int end = line.indexOf(',', start); // находим конец передаваемого значения
        if (end == -1) end = line.indexOf(']', start);
        return line.mid(start, end - start).toLong(); // (позиция начала, длина)
    };

    long byteCount = extract("rx_byte_count=");
    long overflow  = extract("overflow=");
    long speed     = extract("speed=");
    long buffered  = extract("buffered=");

    if (byteCount >= 0) m_byteCount = byteCount;
    if (overflow >= 0)  m_overflowCount = overflow;
    if (speed >= 0)     m_speed = speed;
    if (buffered >= 0)  m_bufferedCount = buffered;
}

QSerialPort* UartInterface::getSerial() const { // доступ к QSerialPort
    return m_serial;
}
