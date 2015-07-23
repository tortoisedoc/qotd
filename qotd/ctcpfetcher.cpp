#include "ctcpfetcher.h"

#include <QTcpSocket>
#include <QHostInfo>
#include <QString>
#include <QDebug>
#include <QByteArray>


CTcpFetcher::CTcpFetcher(QObject *parent, QString targetHost,
    int listening_port, int in_maxlen)
:m_pTcpSocket(new QTcpSocket(parent)),
  QNetFetcherBase(parent, in_maxlen, listening_port), m_targetHost(targetHost){
  bind(listening_port);
}

bool CTcpFetcher::send(QString data, int sendLen, int targetPort){
    if (data.length() > 0){
        if (m_pTcpSocket && m_pTcpSocket->isOpen()){
            qint64 sent_count = m_pTcpSocket->write(data.toStdString().c_str(), sendLen);
            qDebug() << " Sending pushed " <<sent_count;
            if (!m_pTcpSocket->flush())
                qDebug()  << " Error in UDP Sending : " << m_pTcpSocket->errorString();
            return true;
        }else qDebug() << "Socket is not open";
    }
    return false;
}

void CTcpFetcher::fetch(int len){
    if (m_pTcpSocket){
        char data[len];
        m_pTcpSocket->read(data,len);
        qDebug() << " GOT SOME DATA " << data;
        emit dataReceived(QString(data));
    }
}

bool CTcpFetcher::bind(int targetPort){
    if (m_pTcpSocket->bind(targetPort)){
        QHostInfo hInfo = QHostInfo::fromName(m_targetHost);
        if (!hInfo.addresses().isEmpty()){
            foreach (QHostAddress addr, hInfo.addresses())
                qDebug() << " ADDRESS FOUND FOR HOST " << m_targetHost << " / " << addr.toString();
            qDebug () << " Will send to " << hInfo.addresses().first();
            m_pTcpSocket->connectToHost(hInfo.addresses().first(), targetPort);
            return connect(m_pTcpSocket, SIGNAL(readyRead()), this, SLOT(readyRead()) );
        }
    }else qDebug() << "Error in UDP DGram bind : " << m_pTcpSocket->errorString();
    return false;
}



CTcpFetcher::~CTcpFetcher(){
    if (m_pTcpSocket->isOpen())
        m_pTcpSocket->close();
    m_pTcpSocket->deleteLater();
    m_pTcpSocket = NULL;
}
