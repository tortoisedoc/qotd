#include "cudpfetcher.h"

#include <QUdpSocket>
#include <QHostInfo>
#include <QString>
#include <QDebug>
#include <QByteArray>


CUdpFetcher::CUdpFetcher(QObject *parent, int listening_port, int in_maxlen) : m_pUdpSocket(new QUdpSocket(parent)), QNetFetcherBase(parent, in_maxlen, listening_port){
}

bool CUdpFetcher::send(QString data, QString targetHost, int sendLen, int targetPort){

    if (m_pUdpSocket && data.length() > 0){
        QHostInfo hInfo = QHostInfo::fromName(targetHost);
        if (!hInfo.addresses().isEmpty()){
            foreach (QHostAddress addr, hInfo.addresses())
                qDebug() << " ADDRESS FOUND FOR HOST " << targetHost << " / " << addr.toString();
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

void CUdpFetcher::fetch(int len){
    if (m_pUdpSocket){
        char data[len];
        m_pUdpSocket->read(data,len);
        qDebug() << " GOT SOME DATA " << len;
        emit dataReceived(data);
    }
}

bool CUdpFetcher::bind(int targetPort){
    if (m_pUdpSocket->bind(targetPort)){
        return connect(m_pUdpSocket, SIGNAL(readyRead()), this, SLOT(readyRead()) );
    }else qDebug() << "Error in UDP DGram bind : " << m_pUdpSocket->errorString();
    return false;
}

CUdpFetcher::~CUdpFetcher(){
    if (m_pUdpSocket->isOpen())
        m_pUdpSocket->close();
    m_pUdpSocket->deleteLater();
    m_pUdpSocket = NULL;
}
