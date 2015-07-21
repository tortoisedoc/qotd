#include "cudpfetcher.h"

#include <QUdpSocket>
#include <QHostAddress>
#include <QString>
#include <QDebug>
#include <QByteArray>

// From https://en.wikipedia.org/wiki/QOTD

QString s_Servers [] = {
    "djxmmx.net",
    "alpha.mike-r.com",
    "home.kyleterry.com"
};

#define UDP_PORT_QOTD 17
#define UDP_QOTD_MAX_LEN 512

CUdpFetcher::CUdpFetcher(QObject *parent, int port, int maxlen) : QObject(parent)
{
    m_pUdpSocket = new QUdpSocket(parent);
    m_maxRecLen = maxlen;
    if (port != UDP_NO_PORT){
        m_pUdpSocket->bind(UDP_PORT_QOTD);
        connect(m_pUdpSocket, SIGNAL(readyRead()), this, SLOT(readyRead()) );
    }
}

CUdpFetcher::~CUdpFetcher(){
    if (m_pUdpSocket->isOpen())
        m_pUdpSocket->close();
    m_pUdpSocket->deleteLater();
    m_pUdpSocket = None;
}

void CUdpFetcher::sendUpd(QByteArray * data, QString targetHost, int targetPort){
    if (m_pUdpSocket && data)
        m_pUdpSocket->writeDatagram(data->data(), QHostAddress::fromName(targetHost), targetPort);
}

void CUdpFetcher::readyRead(){
    int len = 0;
    if (m_maxRecLen > 0)
        len = m_maxRecLen;
    if (len > 0){
        char data[len];
        m_pUdpSocket->read(data,len);
        emit dataReceived(data);
    }else qDebug()<< "ERROR; INVALID RECEIVE LENGTH SPECIFIED (" << m_maxRecLen <<")";
}


