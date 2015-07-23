#ifndef QNETFETCHERBASE_H
#define QNETFETCHERBASE_H

#include <QObject>

#define UDP_NO_PORT -1
#define UDP_MAX_REC_LEN_NO_LEN -1

class QNetFetcherBase : public QObject
{
    Q_OBJECT
protected:
    int m_maxRecLen;
    virtual bool bind(int targetPort);
    virtual void fetch(int len);
public:
    explicit QNetFetcherBase(QObject *parent = 0, int max_len = 0, int local_port=UDP_NO_PORT);
    Q_INVOKABLE virtual bool send(QString data, QString targetHost, int sendLen, int targetPort=UDP_NO_PORT);
signals:
    void dataReceived(QString text);
public slots:
    virtual void readyRead();
};

#endif // QNETFETCHERBASE_H
