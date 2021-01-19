#ifndef FRAMEMODEL_H
#define FRAMEMODEL_H
#include "frame.h"
#include "database.h"
class FrameModel{
    Frame *head,*SoughtFrame;
    QVector<QString>CPU;
    bool FrameAdded;
    void GenerateModel();
    Frame* CreateFrame(QVector<QString>Data, QString name);
    void AddFrameInModel(QString ParentFrameName,Frame *CurrentFrame,Frame *FrameToAdd);
    void SeekFrameInModel(QVector<QString> Data, Frame* CurrentFrame);
    void SeekFrameInModel(QString Name,Frame* CurrentFrame);
    public:
        FrameModel();
        QVector<QString> Find(QVector<QString>Data);
        QVector<QString> Find(QString Name);
};
#endif // FRAMEMODEL_H
