#ifndef CQUOTEFETCHER_H
#define CQUOTEFETCHER_H

#include "qnetfetcherbase.h"

class QUdpSocket;
class QByteArray;


class CUdpFetcher : public QNetFetcherBase
{
    Q_OBJECT
protected:
    QUdpSocket * m_pUdpSocket;    
    virtual void fetch(int len);
    virtual bool bind(int targetPort);
public:
    explicit CUdpFetcher(QObject *parent=0, int listening_port=UDP_NO_PORT, int in_maxlen = UDP_MAX_REC_LEN_NO_LEN);
    Q_INVOKABLE virtual bool send(QString data, QString targetHost, int sendLen, int targetPort);
    ~CUdpFetcher();
signals:
    void dataReceived(char * text);

};

#endif // CQUOTEFETCHER_H
