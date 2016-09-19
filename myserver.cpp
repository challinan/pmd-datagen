#include "myserver.h"
#include <iostream>
#include "mainwindow.h"

using namespace std;

MyServer::MyServer(QObject* parent): QObject(parent)
{
	printf("MyServer::MyServer() entered - parent = %p\n", parent);
	myParent = parent;
	connect(&server, SIGNAL(newConnection()), this, SLOT(acceptConnection()));
	connect (this,SIGNAL(connectionStatus(bool)),
           parent, SLOT(connectionStatusMainWindow(bool)));

  server.listen(QHostAddress::Any, SERV_PORT);
}

MyServer::~MyServer()
{
  server.close();
}

void MyServer::acceptConnection()
{
	client = server.nextPendingConnection();
	printf("MyServer::acceptConnection(): Connection established\n");
	connect(client, SIGNAL(readyRead()), this, SLOT(startRead()));
	connect(client, SIGNAL(disconnected()),this, SLOT(clientDisconnected()));
	// timer->stop();
	emit connectionStatus(true);

	// Start DataSupplier 
    dataSupplier = new StandAloneDataSupplier(this);
}

void MyServer::dataReady(pm_data_struct *pm) {

	int i = pm->index % 66;
	if ( i == 0 )
		printf("MyServer::dataReady(): index %d\n", pm->index);
	client->write((char *)pm, sizeof(pm_data_struct));
}

void MyServer::clientDisconnected()
{
    pm_data.abpValue=0;
    pm_data.ecgValue =0;
    pm_data.plethValue=0;

	// Kill the data supplier
	delete dataSupplier;
    emit connectionStatus(false);
}
