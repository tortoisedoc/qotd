#include "cudpfetcher.h"

#include <QUdpSocket>
#include <QHostInfo>
#include <QString>
#include <QDebug>
#include <QByteArray>


CUdpFetcher::CUdpFetcher(QObject *parent, int listening_port, int in_maxlen) : QObject(parent)
{
    m_pUdpSocket = new QUdpSocket(parent);
    m_maxRecLen = in_maxlen;
    if (listening_port != UDP_NO_PORT){
        if (m_pUdpSocket->bind(listening_port)){
            bool result = connect(m_pUdpSocket, SIGNAL(readyRead()), this, SLOT(readyRead()) );
        }else qDebug() << "Error in UDP DGram bind : " << m_pUdpSocket->errorString();
    }
}

CUdpFetcher::~CUdpFetcher(){
    if (m_pUdpSocket->isOpen())
        m_pUdpSocket->close();
    m_pUdpSocket->deleteLater();
    m_pUdpSocket = NULL;
}

bool CUdpFetcher::sendUpd(QString data, QString targetHost, int sendLen, int targetPort){
    if (m_pUdpSocket && data.length() > 0){
        QHostInfo hInfo = QHostInfo::fromName(targetHost);
        if (!hInfo.addresses().isEmpty()){
            qDebug () << " Will send to " << hInfo.addresses().first();
            qint64 sent_count = m_pUdpSocket->writeDatagram(data.toStdString().c_str(), sendLen, hInfo.addresses().first(), targetPort);
            qDebug() << " Sending pushed " <<sent_count;
            if (!m_pUdpSocket->flush())
                qDebug()  << " Error in UDP Sending : " << m_pUdpSocket->errorString();
            return true;
        }
    }
    return false;
}

void CUdpFetcher::readyRead(){
    qDebug() << " READY READ ";
    int len = 0;
    if (m_maxRecLen > 0)
        len = m_maxRecLen;
    if (len > 0){
        char data[len];
        m_pUdpSocket->read(data,len);
        qDebug() << " GOT SOME DATA " << len;
        emit dataReceived(data);
    }else qDebug()<< "ERROR; INVALID RECEIVE LENGTH SPECIFIED (" << m_maxRecLen <<")";
}


