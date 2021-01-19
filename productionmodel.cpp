#include "productionmodel.h"
ProductionModel::ProductionModel(){}
QVector<QString> ProductionModel::Find(QVector<QString> Data){
    QString Request="SELECT [Name] "
                    "FROM [CPU]";
    QVector<QString>Characteristic;
    Characteristic<<"Performance"<<"Auto Acceleration"<<"Frequency"<<"Architecture"<<"Cores Threads";
    int j=0;
    for(int i=0;i<Data.length();++i){
        if(Data[i]!="-"){
            if(j==0){
                ++j;
                Request+=" WHERE ["+Characteristic[i]+"]=\""+Data[i]+"\"";
            }else Request+=" AND ["+Characteristic[i]+"]=\""+Data[i]+"\"";
        }
    }
    Database *database=new Database();
    QVector<QVector<QString>>Result=database->SelectRequest(Request,1);
    delete database;
    QVector<QString>Temp;
    for(int i=0;i<Result.length();++i)Temp.append(Result[i][0]);
    if(Temp.length()==0)Temp.append("Ничего не найдено");
    return Temp;
}
QVector<QString> ProductionModel::Find(QString Name){
    Database *database=new Database();
    QVector<QVector<QString>>Result=database->SelectRequest("SELECT [Performance],[Auto Acceleration],[Frequency],[Architecture],[Cores Threads] "
                                                            "FROM [CPU] "
                                                            "WHERE [Name]=\""+Name+"\"",5);
    delete database;
    QVector<QString>Temp;
    if(Result.length()==0)Temp.append("Ничего не найдено");
    else Temp.append(Result[0]);
    QVector<QString>Characteristic;
    Characteristic<<"Быстродействие"<<"Авторазгон"<<"Частота"<<"Архитектура"<<"Ядер\\Потоков";
    for(int i=0;i<Temp.length();++i){
        Temp[i]=Characteristic[i]+": "+Temp[i];
    }
    return Temp;
}
