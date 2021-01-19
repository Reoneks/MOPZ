#ifndef FRAME_H
#define FRAME_H
#include <QString>
#include <QVector>
class Frame{
    QString name;
    QVector<QString>Performance,AutoAcceleration,Frequency,Architecture,CoresThreads,ISA;
    public:
        Frame();
        QVector<Frame*> next;
        Frame *prev;
        void SetData(QVector<QVector<QString>>Data);
        void SetName(QString name);
        QString GetName();
        QVector<QString> GetISA();
        QVector<QVector<QString>> GetData();
};
#endif // FRAME_H
