#include "qnetfetcherbase.h"
#include <QDebug>

QNetFetcherBase::QNetFetcherBase(QObject *parent, int max_len, int local_port) : QObject(parent){
    m_maxRecLen = max_len;
    if (local_port!= UDP_NO_PORT)
        bind(local_port);
}


bool QNetFetcherBase::bind(int targetPort){
    return false;
}


void QNetFetcherBase::fetch(int len){
}

bool QNetFetcherBase::send(QString data, QString targetHost, int sendLen, int targetPort){
    return false;
}

void QNetFetcherBase::readyRead(){
    qDebug() << " READY READ ";
    int len = 0;
    if (m_maxRecLen > 0)
        len = m_maxRecLen;
    if (len > 0){
        this->fetch(len);
    }else qDebug()<< "ERROR; INVALID RECEIVE LENGTH SPECIFIED (" << m_maxRecLen <<")";
}


