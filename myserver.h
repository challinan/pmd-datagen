#ifndef MYSERVER_H
#define MYSERVER_H

#include <QObject>
#include <QtNetwork>
#include <QTcpServer>
#include <QTcpSocket>
#include "PatientMonitorDataGen.h"

#define SERV_PORT   3020 /* server port */

class MyServer: public QObject
{
    Q_OBJECT

public:
    MyServer(QObject * parent = 0);
    ~MyServer();

public slots:
    void acceptConnection();
    // void startRead();
    void clientDisconnected();
    // void updateTimer();
	void dataReady(pm_data_struct *);

signals:
    void myServerDataReceivedSig(pm_data_struct *);
    void connectionStatus(bool);

private:
    QTcpServer server;
    QTcpSocket* client;
    pm_data_struct pm_data;
	QObject *myParent;
	StandAloneDataSupplier *dataSupplier;
};

#endif // MYSERVER_H
