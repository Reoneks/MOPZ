#ifndef SEMANTICWEBOBJECT_H
#define SEMANTICWEBOBJECT_H
#include <QString>
#include <QVector>
class SemanticWebObject{
    QString Name;
public:
    QVector<SemanticWebObject*> next,prev;
    QString GetName();
    void SetName(QString Name);
    SemanticWebObject();
};
#endif // SEMANTICWEBOBJECT_H
