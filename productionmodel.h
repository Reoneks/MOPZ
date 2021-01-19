#ifndef PRODUCTIONMODEL_H
#define PRODUCTIONMODEL_H
#include "database.h"
#include <QVector>
class ProductionModel{
    public:
        ProductionModel();
        QVector<QString> Find(QVector<QString> Data);
        QVector<QString> Find(QString Name);
};
#endif // PRODUCTIONMODEL_H
