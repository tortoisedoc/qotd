#ifndef QNETFETCHERBASE_H
#define QNETFETCHERBASE_H

#include <QObject>

class QNetFetcherBase : public QObject
{
    Q_OBJECT
public:
    explicit QNetFetcherBase(QObject *parent = 0);

signals:

public slots:
};

#endif // QNETFETCHERBASE_H
