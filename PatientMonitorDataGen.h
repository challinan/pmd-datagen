#ifndef PMD_GEN_DATASUPPLIER_H
#define PMD_GEN_DATASUPPLIER_H

#include <QObject>
#include <QTimer>
#include <QtCore>

typedef struct {
    unsigned short int index;
    signed short int ecgValue;
    signed short int abpValue;
    signed short int plethValue;
} pm_data_struct;

class StandAloneDataSupplier: public QObject
{
    Q_OBJECT

public:
    StandAloneDataSupplier(QObject * parent = 0);
    ~StandAloneDataSupplier();
    QList <unsigned int>  ecgData;
    QList <unsigned int>  abpData;
    QList <unsigned int>  plethData;

public slots:
    void updateData();
    void connectionStatus();

signals:
    void dataAvailable(pm_data_struct *);

private:
    unsigned int getECGData();
    unsigned int getABPData();
    unsigned int getPlethData();

	pm_data_struct pm_data;
    QTimer *timer;
    int ecgIndex;
    int abpIndex;
    int plethIndex;
};

#endif // PMD_GEN_DATASUPPLIER_H
