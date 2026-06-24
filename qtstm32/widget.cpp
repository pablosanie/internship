#include "widget.h"
#include "ui_widget.h"
#include <QSerialPortInfo>


Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
    , m_serial(new QSerialPort(this))
    , m_timer(new QTimer(this))
    , m_generatorTimer(new QTimer(this))
    , m_timeCounter(0)
    , m_period(100)
    , m_percent(0)
    , m_lastByteCount(0)

{
    ui->setupUi(this);
    ui->lcdNumber->setStyleSheet(
        "QLCDNumber { background-color: black; color: red; }"
        );
    ui->periodBox->setMinimum(10);
    ui->periodBox->setValue(100);
    ui->perBox->setMinimum(0);
    ui->perBox->setMaximum(100);
    ui->perBox->setValue(50);

    populatePorts();
    setupChart();
    connect(m_serial, &QSerialPort::readyRead,
            this, &Widget::onReadyRead);
    connect(ui->connectButton, &QPushButton::clicked,
            this, &Widget::onConnectClicked);
    connect(m_timer, &QTimer::timeout,
            this, &Widget::onTimer);
    connect(ui->sendButton, &QPushButton::clicked,
            this, &Widget::onSendClicked);
    connect(ui->generatorButton, &QPushButton::clicked, this, &Widget::onGeneratorClicked);
    connect(m_generatorTimer, &QTimer::timeout, this, &Widget::onGeneratorTimer);
    connect(ui->periodBox, &QSpinBox::valueChanged, this, &Widget::onperiodBoxChanged);
    connect(ui->perBox, &QSpinBox::valueChanged, this, &Widget::onpercentBoxChanged);
}

Widget::~Widget()
{
    if (m_serial->isOpen())
        m_serial->close();
    delete ui;
}
void Widget::onTimer()
{
    m_timeCounter++;

    long current = ui->lcdNumber->intValue();
    long speed = current - m_lastByteCount;
    m_lastByteCount = current;

    m_seriesRx->append(m_timeCounter, speed);

    QValueAxis *axisX = qobject_cast<QValueAxis*>(
        m_chart->axes(Qt::Horizontal).first());
    if (axisX && m_timeCounter > 60)
        axisX->setRange(m_timeCounter - 60, m_timeCounter);
}
void Widget::populatePorts(){ // обнаружение портов
    ui->portComboBox->clear();
    for(const QSerialPortInfo &info : QSerialPortInfo::availablePorts()){
        ui->portComboBox->addItem(info.portName());
    }
}
void Widget::setupChart(){ // график
    m_series = new QLineSeries();
    m_chart = new QChart();
    m_chart->addSeries(m_series);
    m_chart->setTitle("Скорость передачи данных (байт/сек)");

    QValueAxis *axisX = new QValueAxis();
    axisX->setTitleText("Время (с)");
    axisX->setRange(0,60);

    QValueAxis *axisY = new QValueAxis();
    axisY->setTitleText("Байт/сек");
    axisY->setRange(0, 1000);

    m_chart->addAxis(axisX, Qt::AlignBottom);
    m_chart->addAxis(axisY, Qt::AlignLeft);
    m_series->attachAxis(axisX);
    m_series->attachAxis(axisY);

    ui->graph->setChart(m_chart);
    ui->graph->setRenderHint(QPainter::Antialiasing);

    m_seriesRx = new QLineSeries();
    m_seriesRx->setName("Приём (байт/сек)");
    m_series->setName("Скорость (от STM32)");
    m_chart->addSeries(m_seriesRx);
    m_seriesRx->attachAxis(axisX);
    m_seriesRx->attachAxis(axisY);
}
void Widget::onperiodBoxChanged(int value){
    if (value <= 0) return;
    m_period = value;
    if (m_generatorTimer->isActive()){
        m_generatorTimer->setInterval(m_period);  // setInterval вместо start!
    }
}
void Widget::onpercentBoxChanged(int value){
    m_percent = value;
}
void Widget::onGeneratorClicked(){ // включение/отключение генератора
    if (!m_serial->isOpen()){
        qDebug() << "Порт не открыт";
        return;
    }
    if(m_generatorTimer->isActive()){
        m_generatorTimer->stop();
        ui->generatorButton->setText("Включить генератор");
    }
    else{
        qDebug() << "Запуск генератора с периодом:" << m_period;
        m_generatorTimer->start(m_period);
        ui->generatorButton->setText("Отключить генератор");
    }
}
// void Widget::onStringGeneratorClicked(){

// }
void Widget::onGeneratorTimer(){
    if (!m_serial->isOpen())
    {
        qDebug() << "Порт не открыт";
        if(m_generatorTimer->isActive()){
            m_generatorTimer->stop();
            ui->generatorButton->setText("Включить генератор");
        }
        return;
    }
    qint8 rnd = QRandomGenerator::global()->bounded(100);
    if(rnd<m_percent){
        char text = (char)QRandomGenerator::global()->bounded(33, 127);
        m_serial->write(&text, 1);
    }
}
void Widget::onConnectClicked(){
    if(m_serial->isOpen()){
        m_serial->close();
        m_timer->stop();
        ui->connectButton->setText("Подключить");
        return;
    }
    m_serial->setPortName(ui->portComboBox->currentText());
    m_serial->setBaudRate(QSerialPort::Baud115200);
    m_serial->setDataBits(QSerialPort::Data8);
    m_serial->setParity(QSerialPort::NoParity);
    m_serial->setStopBits(QSerialPort::OneStop);
    if (m_serial->open(QIODevice::ReadWrite))
    {
        ui->connectButton->setText("Отключить");
        m_timer->start(1000);
        qDebug() << "Порт открыт:" << m_serial->portName();
    }
    else
    {
        qDebug() << "Ошибка:" << m_serial->errorString();
    }
}

void Widget::onReadyRead(){
    static QByteArray buffer;
    buffer += m_serial->readAll();

    while(buffer.contains('\n')){
        int idx = buffer.indexOf('\n');
        QString line = QString::fromUtf8((buffer.left(idx)).trimmed());
        buffer.remove(0, idx + 1);

        if (!line.isEmpty()){
            parseData(line);
        }
    }
}
void Widget::parseData(const QString &line)
{
    if (!line.contains("rx_byte_count="))
        return;

    auto extract = [&](const QString &key) -> long {
        int start = line.indexOf(key);
        if (start == -1) return -1;
        start += key.length();
        int end = line.indexOf(',', start);
        if (end == -1) end = line.indexOf(']', start);
        return line.mid(start, end - start).toLong();
    };

    long byteCount = extract("rx_byte_count=");
    long speed     = extract("speed=");

    if (byteCount >= 0)
        ui->lcdNumber->display((double)byteCount);

    if (speed >= 0)
    {
        m_series->append(m_timeCounter, speed);
    }
}
void Widget::onSendClicked()
{
    if (!m_serial->isOpen())
    {
        qDebug() << "Порт не открыт";
        return;
    }

    QString text = ui->inputLineEdit->text();
    if (text.isEmpty())
        return;

    m_serial->write(text.toUtf8());
    ui->inputLineEdit->clear();
}