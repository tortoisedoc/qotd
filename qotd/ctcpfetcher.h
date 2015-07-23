#ifndef CTCPFETCHER_H
#define CTCPFETCHER_H


#include "qnetfetcherbase.h"

class QTcpSocket;

class CTcpFetcher : public QNetFetcherBase
{
    Q_OBJECT
private:
    QTcpSocket * m_pTcpSocket;
    QString m_targetHost;
protected:
    virtual bool bind(int targetPort);
    virtual void fetch(int len);
public:
    explicit CTcpFetcher(QObject *parent=0, QString targetHost="localhost", int listening_port=UDP_NO_PORT, int in_maxlen = UDP_MAX_REC_LEN_NO_LEN);
    Q_INVOKABLE virtual bool send(QString data, int sendLen, int targetPort);
    ~CTcpFetcher();
};

#endif // CTCPFETCHER_H
