#ifndef SEMANTICWEB_H
#define SEMANTICWEB_H
#include "semanticwebobject.h"
#include "database.h"
class SemanticWeb{
    bool ObjectAdded;
    SemanticWebObject *head;
    QVector<QString> CPUData,TempCPU;
    void GenerateModel();
    SemanticWebObject* CreateSemanticWebObject(QString Name);
    void AddSemanticWebObjectInModel(QString ParentObjectName, SemanticWebObject *CurrentObject, SemanticWebObject *ObjectToAdd,QVector<SemanticWebObject*> CPU);
    void SeekSemanticWebObjectInModel(SemanticWebObject* CurrentObject);
    void SeekSemanticWebObjectInModel1(SemanticWebObject* CurrentObject);
    SemanticWebObject* AttributeMapDecoder(QString Attribute);
public:
    SemanticWeb();
    QVector<QString> Find(QVector<QString>Data);
    QVector<QString> Find(QString Name);
};
#endif // SEMANTICWEB_H
