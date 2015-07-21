#ifndef CQUOTEFETCHER_H
#define CQUOTEFETCHER_H

#include <QObject>

class QUdpSocket;
class QByteArray;

#define UDP_NO_PORT -1
#define UDP_MAX_REC_LEN_NO_LEN -1

class CUdpFetcher : public QObject
{
    Q_OBJECT
private:
    int m_maxRecLen;
protected:
    QUdpSocket * m_pUdpSocket;
public:
    explicit CUdpFetcher(QObject *parent=0, int port=UDP_NO_PORT, int maxlen = UDP_MAX_REC_LEN_NO_LEN);
    ~CUdpFetcher();
    Q_INVOKABLE void sendUpd(QByteArray * data, QString targetHost, int targetPort);
signals:
    void dataReceived(char * text);

public slots:
    void readyRead();
};

#endif // CQUOTEFETCHER_H
