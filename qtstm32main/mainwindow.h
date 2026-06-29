#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QtCharts>
#include <QSerialPort>
#include <QComboBox>
#include <QSerialPortInfo>
#include <QTimer>
#include <QRandomGenerator>
#include "uartinterface.h"


QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

private:
    // --- UI --
    Ui::MainWindow *ui;
    QAction *m_connectAction;
    QAction *m_generatorAction;
    QComboBox *m_scaleBox;

    // -- График ---
    QLineSeries *m_series;
    QLineSeries *m_seriesRx; // приём
    QChart *m_chart;
    qint32 m_size;
    qint64 m_timeCounter; // счётчик времени (x)

    long m_txBytesCount;
    long m_lastTxBytes; // разница этих 2 показатель это скорость отправки в 1 секунду

    // -- UART ---
    UartInterface *m_uart; // интерфейс Uart
    QTimer *m_timer; // таймер между приёмами статистики
    int m_baudRate; // передаваемый baudRate из scaleBox

    // --- Параметры генератора ---
    int m_period;
    int m_percent;
    QTimer *m_generatorTimer; // таймер для генератора

    // --- Методы ---
    void populatePorts(); // распознать устройства
    void setupChart(); // создать график
    QToolBar* createToolBar(); // создать ToolBar. Инициализация внутри метода
private slots:
    void onConnectClicked(); // соединиться с UART
    void onReadyRead(); // чтение данных и обновление показателей (в т.ч. кривая скорости от STM32)
    void onTimer(); // сдвиг во времени и кривая скорости согласно Qt
    void onSendClicked(); // отправка своего сообщения
    void onGeneratorClicked(); // вкл/выкл генератора байт
    void onStringGeneratorClicked(); // отправка массива (строки) генератором из рандомных символов
    void onGeneratorTimer(); //
    void onperiodBoxChanged(int value); // выбор периода отправки 1го байт генератором
    void onpercentBoxChanged(int value); // выбор % шанса того, что генератор отправит 1 байт
    void onsizeBoxChanged(int value); // выбор размера отправляемого массива (строки)
    void onChartContextMenu(const QPoint &pos); // выбор масштаба графика
    void speedBox(int index); // выбор скорости отправки данных
};
#endif // MAINWINDOW_H
