#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QSerialPortInfo>
#include <QMenu>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , m_uart(new UartInterface())
    , m_timer(new QTimer(this))
    , m_generatorTimer(new QTimer(this))
    , m_timeCounter(0)
    , m_period(100)
    , m_percent(50)
    , m_size(50)
    , m_txBytesCount(0)
    , m_lastTxBytes(0)

{
    ui->setupUi(this);
    ui->lcdNumber->setStyleSheet(
        "QLCDNumber { background-color: black; color: red; }"
        );
    ui->lcdNumber_2->setStyleSheet(
        "QLCDNumber { background-color: black; color: red; }"
        );
    ui->lcdNumber_3->setStyleSheet(
        "QLCDNumber { background-color: black; color: red; }"
        );
    ui->periodBox->setMinimum(10);
    ui->periodBox->setValue(100);
    ui->perBox->setMinimum(0);
    ui->perBox->setMaximum(100);
    ui->perBox->setValue(50);

    ui->sizeBox->setMinimum(0);
    ui->sizeBox->setMaximum(4096);
    ui->sizeBox->setValue(50);

    populatePorts();
    setupChart();
    connect(m_uart->getSerial(), &QSerialPort::readyRead,
            this, &MainWindow::onReadyRead);
    connect(ui->connectButton, &QPushButton::clicked,
            this, &MainWindow::onConnectClicked);
    connect(m_timer, &QTimer::timeout,
            this, &MainWindow::onTimer);
    connect(ui->sendButton, &QPushButton::clicked,
            this, &MainWindow::onSendClicked);
    connect(ui->generatorButton, &QPushButton::clicked, this, &MainWindow::onGeneratorClicked);
    connect(ui->stringGeneratorButton, &QPushButton::clicked, this, &MainWindow::onStringGeneratorClicked);
    connect(m_generatorTimer, &QTimer::timeout, this, &MainWindow::onGeneratorTimer);
    connect(ui->periodBox, &QSpinBox::valueChanged, this, &MainWindow::onperiodBoxChanged);
    connect(ui->perBox, &QSpinBox::valueChanged, this, &MainWindow::onpercentBoxChanged);
    connect(ui->sizeBox, &QSpinBox::valueChanged, this, &MainWindow::onsizeBoxChanged);

    addToolBar(Qt::TopToolBarArea, createToolBar());
}

MainWindow::~MainWindow()
{
    if (m_uart->isConnected())
        m_uart->disconnect();
    delete ui;
}
void MainWindow::onTimer()
{
    m_timeCounter++;

    long speedTx = m_txBytesCount - m_lastTxBytes;
    m_lastTxBytes = m_txBytesCount;
    m_seriesRx->append(m_timeCounter, speedTx);

    QValueAxis *axisX = qobject_cast<QValueAxis*>(
        m_chart->axes(Qt::Horizontal).first());
    if (axisX && m_timeCounter > 60)
        axisX->setRange(m_timeCounter - 60, m_timeCounter);
}
void MainWindow::populatePorts(){ // обнаружение портов
    ui->portComboBox->clear();
    for(const QSerialPortInfo &info : QSerialPortInfo::availablePorts()){
        ui->portComboBox->addItem(info.portName());
    }
}
void MainWindow::setupChart(){ // график
    m_series = new QLineSeries();
    m_chart = new QChart();
    m_chart->addSeries(m_series);
    m_chart->setTitle("Скорость передачи данных (байт/сек)");

    QValueAxis *axisX = new QValueAxis();
    axisX->setTitleText("Время (с)");
    axisX->setRange(0,60);

    QValueAxis *axisY = new QValueAxis();
    axisY->setTitleText("Байт/сек");
    axisY->setRange(0, 4000);

    m_chart->addAxis(axisX, Qt::AlignBottom);
    m_chart->addAxis(axisY, Qt::AlignLeft);
    m_series->attachAxis(axisX);
    m_series->attachAxis(axisY);

    ui->graph->setChart(m_chart);
    ui->graph->setRenderHint(QPainter::Antialiasing);

    m_seriesRx = new QLineSeries();
    m_series->setName("Скорость приёма данных STM32 (байт/сек)");
    m_seriesRx->setName("Скорость передачи данных от Qt (байт/сек)");
    m_chart->addSeries(m_seriesRx);
    m_seriesRx->attachAxis(axisX);
    m_seriesRx->attachAxis(axisY);

    ui->graph->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui->graph, &QChartView::customContextMenuRequested,
            this, &MainWindow::onChartContextMenu);
}
void MainWindow::onperiodBoxChanged(int value){
    if (value <= 0) return;
    m_period = value;
    if (m_generatorTimer->isActive()){
        m_generatorTimer->setInterval(m_period);  // setInterval вместо start!
    }
}
void MainWindow::onpercentBoxChanged(int value){
    m_percent = value;
}
void MainWindow::onsizeBoxChanged(int value){
    m_size = value;
}
void MainWindow::onGeneratorClicked(){ // включение/отключение генератора
    if (!m_uart->isConnected()){
        qDebug() << "Порт не открыт";
        QMessageBox::warning(0, "Предупреждение", "Порт не открыт!");
        return;
    }
    if(m_generatorTimer->isActive()){
        m_generatorTimer->stop();
        ui->generatorButton->setText("Включить генератор (1 байт)");
        m_generatorAction->setText("Генератор (включить)");
    }
    else{
        qDebug() << "Запуск генератора с периодом:" << m_period;
        m_generatorTimer->start(m_period);
        ui->generatorButton->setText("Отключить генератор");
        m_generatorAction->setText("Генератор (отключить)");
    }
}
void MainWindow::onStringGeneratorClicked(){
    if (!m_uart->isConnected()){
        qDebug() << "Порт не открыт";
        QMessageBox::warning(0, "Предупреждение", "Порт не открыт!");
        return;
    }
    QByteArray packet;
    packet.resize(m_size);
    for (int i = 0; i < m_size; i++){
        packet[i] = (char)QRandomGenerator::global()->bounded(33, 127);
    }
    m_uart->sendData(packet);
    m_txBytesCount += m_size;
}
void MainWindow::onGeneratorTimer(){
    if (!m_uart->isConnected())
    {
        qDebug() << "Порт не открыт";
        QMessageBox::warning(0, "Предупреждение", "Порт не открыт!");
        if(m_generatorTimer->isActive()){
            m_generatorTimer->stop();
            ui->generatorButton->setText("Включить генератор (1 байт)");
        }
        return;
    }
    qint8 rnd = QRandomGenerator::global()->bounded(100);
    if(rnd<m_percent){
        char text = (char)QRandomGenerator::global()->bounded(33, 127);
        m_uart->sendData(QByteArray(1, text));
        m_txBytesCount += 1;
    }
}
void MainWindow::onConnectClicked(){
    if(m_uart->isConnected()){
        m_uart->disconnect();
        m_timer->stop();
        ui->connectButton->setText("Подключить");
        m_connectAction->setText("Подключить");
        return;
    }
    QString port = ui->portComboBox->currentText();
    if (m_uart->connect(port, 115200))
    {
        ui->connectButton->setText("Отключить");
        m_connectAction->setText("Отключить");
        m_timer->start(1000);
        qDebug() << "Порт открыт:" << port;
    }
    else
    {
        qDebug() << "Ошибка подключения:" << m_uart->getSerial()->errorString();
        QMessageBox::warning(0, "Предупреждение", "Ошибка подключения\n" + m_uart->getSerial()->errorString());
    }
}

void MainWindow::onReadyRead(){
    static QByteArray buffer;
    buffer += m_uart->getSerial()->readAll();

    while(buffer.contains('\n')){
        int idx = buffer.indexOf('\n');
        QString line = QString::fromUtf8((buffer.left(idx)).trimmed());
        buffer.remove(0, idx + 1);

        if (!line.isEmpty()){
            m_uart->parseData(line);
            ui->lcdNumber->display((double)m_uart->getByteCount());
            ui->lcdNumber_2->display((double)m_uart->getOverflowCount());
            ui->lcdNumber_3->display((double)m_uart->getBufferedCount());
            m_series->append(m_timeCounter, m_uart->getSpeed());
        }
    }
}
void MainWindow::onSendClicked()
{
    if (!m_uart->isConnected())
    {
        qDebug() << "Порт не открыт";
        QMessageBox::warning(0, "Предупреждение", "Порт не открыт!");
        return;
    }

    QString text = ui->inputLineEdit->text();
    if (text.isEmpty())
        return;

    m_uart->sendData(text.toUtf8());
    m_txBytesCount += text.toUtf8().size();
    ui->inputLineEdit->clear();
}

void MainWindow::onChartContextMenu(const QPoint &pos)
{
    QMenu menu(this);

    QAction *action1000 = menu.addAction("Масштаб: 1000 байт/сек");
    QAction *action4000 = menu.addAction("Масштаб: 4000 байт/сек");
    QAction *action12000 = menu.addAction("Масштаб: 12000 байт/сек");

    QAction *selected = menu.exec(ui->graph->mapToGlobal(pos));

    QValueAxis *axisY = qobject_cast<QValueAxis*>(
        m_chart->axes(Qt::Vertical).first());
    if (!axisY) return;

    if (selected == action1000)
        axisY->setRange(0, 1000);
    else if (selected == action4000)
        axisY->setRange(0, 4000);
    else if (selected == action12000)
        axisY->setRange(0, 12000);
}

QToolBar* MainWindow::createToolBar(){
    QToolBar *ptb = new QToolBar("Toolbar");
    m_connectAction = ptb->addAction("Подключить", this, &MainWindow::onConnectClicked);
    m_generatorAction = ptb->addAction("Генератор (включить)", this, &MainWindow::onGeneratorClicked);
    ptb->addAction("Отправить пакет", this, &MainWindow::onStringGeneratorClicked);
    ptb->addSeparator();
    QComboBox *scaleBox = new QComboBox(ptb);
    scaleBox->addItem("Масштаб: 1000 байт/сек");
    scaleBox->addItem("Масштаб: 4000 байт/сек");
    scaleBox->addItem("Масштаб: 12000 байт/сек");
    scaleBox->setCurrentIndex(1);
    ptb->addWidget(scaleBox);
    connect(scaleBox, &QComboBox::currentIndexChanged, this, [this](int index){
        QList<QAbstractAxis*> axesY = m_chart->axes(Qt::Vertical);
        QValueAxis *axisY = qobject_cast<QValueAxis*>(axesY.first());
        if (!axisY) return;
        switch(index){
            case 0: axisY->setRange(0, 1000);  break;
            case 1: axisY->setRange(0, 4000);  break;
            case 2: axisY->setRange(0, 12000); break;
        }
    });


    return ptb;
}
