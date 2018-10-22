#ifndef CMSGBUSINESS_H
#define CMSGBUSINESS_H

#include <QObject>

class CMsgBusiness : public QObject
{
    Q_OBJECT
public:
    explicit CMsgBusiness(QObject *parent = nullptr);
    ~CMsgBusiness();
    //这里可以在UI里来直接调用
    QString get()const;
signals:
    //处理完的Msg发到界面上去显示
    void signalSomethingComing(QString);
private slots:
    //收到下层来的msg
    void onCommingMsg(const QByteArray&);
public slots:
};

#endif // CMSGBUSINESS_H
