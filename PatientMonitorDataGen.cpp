#include "PatientMonitorDataGen.h"
using namespace std;

StandAloneDataSupplier::StandAloneDataSupplier(QObject* parent): QObject(parent)
{
    ecgData <<0<<0<<0<<0<<-11<<-9<<-8<<-4<<0<<-1<<3<<7<<8<<12<<13<<12<<7<<5<<-3<<-7<<-12<<-13<<-16<<-12<<-13<<-13<<-13<<-14<<-14<<-12<<-13<<-13<<-13<<-14<<-15<<-16<<-16<<-17<<-14<<-15<<-8<<-17<<-16<<1<<44<<72<<96<<80<<31<<-11<<-16<<-13<<-12<<-13<<-15<<-16<<-17<<-19<<-17<<-16<<-16<<-15<<-14<<-13<<-14;
    abpData <<-7 << -1 <<11 <<24 <<35 <<46 <<55 <<63 <<72 <<79 <<85 << 92 << 98 <<102 <<102 <<103<<103 <<102 <<101 << 97 << 93 << 88 <<83 <<78 <<75 <<66 <<63 <<63 <<63 <<64 <<66 <<67 << 68 <<68<<67 << 64 << 58 <<50 <<49 <<42 <<38 <<33 <<29 <<26 << 24 << 22 << 20 <<18 <<16 <<14 <<13 <<11 <<10<<9 <<7 <<6 << 5 <<3 <<2 <<1 << 0 <<-1 <<-1 <<-2 <<-2 <<-2 <<-3 <<-3 <<-3 <<-4 <<-4 << -4<<-5 <<-5 <<-5 <<-6 <<-6 <<-6 << -6 << -6 <<-7 <<-7 << -7 <<-7<<-5<<-5;
    plethData <<-7 << -1 <<11 <<24 <<35 <<40 <<46 <<50 <<55 <<58 <<63 <<72 <<74 << 74 << 76<<78 <<80 << 81 << 81 <<81 <<80 <<80<<80 <<79 <<79 << 78 << 76 << 74 << 70 <<66 <<63 <<63 <<63 <<64 <<66 <<67 << 68 <<68<<67 << 64 << 58 <<50 <<49 <<42 <<38 <<33 <<29 <<26 << 24 << 22 << 20 <<18 <<16 <<14 <<13 <<11 <<10<<9 <<7 <<6 << 5 <<3 <<2 <<1 << 0 <<-1 <<-1 <<-2 <<-2 <<-2 <<-3 <<-3 <<-3 <<-4 <<-4 << -4<<-5 <<-5 <<-5 <<-6 <<-6 <<-6 << -6 << -6 <<-7 <<-7 << -7 <<-7<<-8<<-9<<-9;
    ecgIndex =-1;
    abpIndex =-1;
    plethIndex=-1;
    pm_data.index=0;

    connect (this,SIGNAL(dataAvailable(pm_data_struct*)),parent, SLOT(dataReady(pm_data_struct  *)));

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(updateData()));
    timer->setInterval(30);
    timer->start();
}

StandAloneDataSupplier::~StandAloneDataSupplier()
{
    ecgData.clear();
    abpData.clear();
    plethData.clear();
}

void StandAloneDataSupplier::connectionStatus()
{
	printf("ConnectionStatus Slot entered\n");
}

unsigned int StandAloneDataSupplier::getECGData()
{
    if (ecgIndex == ecgData.count()-1)
        ecgIndex = -1;

    ecgIndex++;
    return ecgData[ecgIndex];
}

unsigned int StandAloneDataSupplier::getABPData()
{
    if (abpIndex == abpData.count()-1)
        abpIndex = -1;

    abpIndex++;
    return abpData[abpIndex];
}

unsigned int StandAloneDataSupplier::getPlethData()
{
    if (plethIndex == plethData.count()-1)
        plethIndex = -1;

    plethIndex++;
    return plethData[plethIndex];
}

void StandAloneDataSupplier::updateData()
{
	int i = pm_data.index % 66;
	if ( i == 0 )
		printf("StandAloneDataSupplier::updateData() - %d\n", pm_data.index);
    if (pm_data.index == USHRT_MAX)
    {
        pm_data.index=0;
    }
    else
    {
        pm_data.index++;
    }

    pm_data.ecgValue = getECGData();
    pm_data.abpValue = getABPData();
    pm_data.plethValue = getPlethData();
    
	// Send data here
	emit dataAvailable(&pm_data);
}


