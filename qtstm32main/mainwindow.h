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
    // --- UI ---
    Ui::MainWindow *ui;
    QAction *m_connectAction;
    QAction *m_generatorAction;
    QComboBox *m_scaleBox;

    // --- График ---
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
    void populatePorts();
    void setupChart();
    QToolBar* createToolBar();
private slots:
    void onConnectClicked();
    void onReadyRead();
    void onTimer();
    void onSendClicked();
    void onGeneratorClicked();
    void onStringGeneratorClicked();
    void onGeneratorTimer();
    void onperiodBoxChanged(int value);
    void onpercentBoxChanged(int value);
    void onsizeBoxChanged(int value);
    void onChartContextMenu(const QPoint &pos);
    void speedBox(int index);
};
#endif // MAINWINDOW_H
