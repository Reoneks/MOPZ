#include "frame.h"
Frame::Frame(){}
void Frame::SetData(QVector<QVector<QString>>Data){
    ISA=Data[0];
    Performance=Data[1];
    AutoAcceleration=Data[2];
    Frequency=Data[3];
    Architecture=Data[4];
    CoresThreads=Data[5];
}
void Frame::SetName(QString name){
    this->name=name;
}
QString Frame::GetName(){
    return name;
}
QVector<QVector<QString>> Frame::GetData(){
    QVector<QVector<QString>>Data;
    Data<<Performance<<AutoAcceleration<<Frequency<<Architecture<<CoresThreads;
    return Data;
}
QVector<QString> Frame::GetISA(){
    return ISA;
}
