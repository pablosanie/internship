#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QtCharts>
#include <QSerialPort>
#include <QComboBox>
#include <QSerialPortInfo>
#include <QTimer>

QT_BEGIN_NAMESPACE
namespace Ui {
class Widget;
}
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = nullptr);
    ~Widget() override;

private:
    Ui::Widget *ui;
    QLineSeries *m_series;
    QLineSeries *m_seriesRx; // приём
    long m_lastByteCount;
    QChart *m_chart;
    QChartView *m_charView;
    QSerialPort *m_serial;
    QTimer *m_timer;
    QTimer *m_generatorTimer;
    qint64 m_timeCounter;
    int m_period;
    int m_percent;
    qint32 m_size;
    void populatePorts();
    void setupChart();
    void parseData(const QString &line);
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
};
#endif // WIDGET_H
