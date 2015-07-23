#ifndef CTCPFETCHER_H
#define CTCPFETCHER_H

#include <QObject>

class CTcpFetcher : public QObject
{
    Q_OBJECT
public:
    explicit CTcpFetcher(QObject *parent = 0);

signals:

public slots:
};

#endif // CTCPFETCHER_H
