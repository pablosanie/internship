#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QtCharts>
#include <QSerialPort>
#include <QComboBox>
#include <QSerialPortInfo>
#include <QTimer>
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
    Ui::MainWindow *ui;
    QLineSeries *m_series;
    QLineSeries *m_seriesRx; // приём
    QChart *m_chart;
    QChartView *m_charView;
    UartInterface *m_uart;
    QTimer *m_timer;
    QTimer *m_generatorTimer;
    qint64 m_timeCounter;
    int m_period;
    int m_percent;
    qint32 m_size;
    QAction *m_connectAction;
    QAction *m_generatorAction;
    void populatePorts();
    void setupChart();
    long m_txBytesCount;
    long m_lastTxBytes;
    QToolBar* createToolBar();
    int m_baudRate;
    QComboBox *m_scaleBox;
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
