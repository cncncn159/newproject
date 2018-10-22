#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QMessageBox>
#include "scantest.h"
#include "uartthread.h"

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

signals:
    void readyRead();
    void dlgReturn(QByteArray);

private:
    Ui::Widget *ui;
    QStringList baudList;
    void initPort(void);
    void initText(void);
    void closeSerialPort(void);
    QSerialPort *serial;
    void handleError(QSerialPort::SerialPortError error);
    UartThread* uart;
private slots:
    void recSerialData(void);

    void on_pushButton_clicked();
};

#endif // WIDGET_H
