#include "semanticweb.h"
SemanticWeb::SemanticWeb(){
    ObjectAdded=false;
    GenerateModel();
}
void SemanticWeb::GenerateModel(){
    head=CreateSemanticWebObject("User");
    head->next.append(CreateSemanticWebObject("Характеристики"));
    head->next.append(CreateSemanticWebObject("CPU"));
    head->next[0]->next.append(CreateSemanticWebObject("Быстродействие"));
    head->next[0]->next.append(CreateSemanticWebObject("Авторазгон"));
    head->next[0]->next.append(CreateSemanticWebObject("Частота"));
    head->next[0]->next.append(CreateSemanticWebObject("Архитектура"));
    head->next[0]->next.append(CreateSemanticWebObject("Ядер\\Потоков"));
    QVector<QString>Characteristic;
    QVector<QVector<QString>>Result;
    Characteristic<<"Performance"<<"Auto Acceleration"<<"Frequency"<<"Architecture"<<"Cores Threads";
    Database *database=new Database();
    for(int i=0;i<Characteristic.length();++i){
        Result=database->SelectRequest("SELECT ["+Characteristic[i]+"] "
                                       "FROM [CPU] "
                                       "GROUP BY ["+Characteristic[i]+"]",1);
        for(QVector<QString>j:Result){
            SemanticWebObject *temp=CreateSemanticWebObject(j[0]);
            temp->prev.append(head->next[0]->next[i]);
            head->next[0]->next[i]->next.append(temp);
        }
    }
    Result=database->SelectRequest("SELECT [Name] "
                                   "FROM [CPU] ",1);
    for(QVector<QString>j:Result){
        head->next[1]->next.append(CreateSemanticWebObject(j[0]));
    }
    Result=database->SelectRequest("SELECT [Name],[Previous object],[CPU object],[Attribute Map] "
                                   "FROM [Semantic web] ",4);
    delete database;
    for(QVector<QString>i:Result){
        QStringList temp=i[1].split("|");
        QStringList temp1=i[3].split("|");
        QStringList temp2=i[2].split("|");
        if(i[0]!=""){
            QVector<SemanticWebObject*> CPU;
            for(QString h:temp2){
                for(SemanticWebObject *o:head->next[1]->next){
                    if(o->GetName()==h){
                        CPU.append(o);
                        break;
                    }
                }
            }
            for(int j=0;j<temp.length();++j){
                ObjectAdded=false;
                AddSemanticWebObjectInModel(temp[j],AttributeMapDecoder(temp1[j]),CreateSemanticWebObject(i[0]),CPU);
            }
        }else{
            for(int j=0;j<temp.length();++j){
                for(SemanticWebObject *k:AttributeMapDecoder(temp1[j])->next){
                    if(k->GetName()==temp[j]){
                        for(QString h:temp2){
                            for(SemanticWebObject *o:head->next[1]->next){
                                if(o->GetName()==h){
                                    k->next.append(o);
                                    o->prev.append(k);
                                    break;
                                }
                            }
                        }
                        break;
                    }
                }
            }
        }
    }
}
SemanticWebObject* SemanticWeb::AttributeMapDecoder(QString Attribute){
    if(Attribute=="Б")return head->next[0]->next[0];
    else if(Attribute=="А")return head->next[0]->next[1];
    else if(Attribute=="Ч")return head->next[0]->next[2];
    else if(Attribute=="Ар")return head->next[0]->next[3];
    else if(Attribute=="ЯП")return head->next[0]->next[4];
    else return head->next[0];
}
SemanticWebObject* SemanticWeb::CreateSemanticWebObject(QString Name){
    SemanticWebObject *TempObj=new SemanticWebObject();
    TempObj->SetName(Name);
    return TempObj;
}
void SemanticWeb::AddSemanticWebObjectInModel(QString ParentObjectName, SemanticWebObject *CurrentObject, SemanticWebObject *ObjectToAdd, QVector<SemanticWebObject *> CPU){
    if(CurrentObject->GetName()==ParentObjectName){
        ObjectToAdd->prev.append(CurrentObject);
        for(SemanticWebObject *i:CPU){
            ObjectToAdd->next.append(i);
            i->prev.append(ObjectToAdd);
        }
        CurrentObject->next.append(ObjectToAdd);
        ObjectAdded=true;
        return;
    }else{
        for(SemanticWebObject *i:CurrentObject->next){
            AddSemanticWebObjectInModel(ParentObjectName,i,ObjectToAdd,CPU);
            if(ObjectAdded)return;
        }
    }
}
void SemanticWeb::SeekSemanticWebObjectInModel(SemanticWebObject* CurrentObject){
    if(CurrentObject->next.length()==0){
        TempCPU.append(CurrentObject->GetName());
        return;
    }else{
        for(SemanticWebObject *i:CurrentObject->next){
            SeekSemanticWebObjectInModel(i);
        }
    }
}
void SemanticWeb::SeekSemanticWebObjectInModel1(SemanticWebObject* CurrentObject){
    if(CurrentObject->prev[0]->prev.length()==0){
        CPUData.append(CurrentObject->prev[0]->GetName()+": "+CurrentObject->GetName());
        return;
    }else{
        for(SemanticWebObject *i:CurrentObject->prev){
            SeekSemanticWebObjectInModel1(i);
        }
    }
}
QVector<QString> SemanticWeb::Find(QVector<QString>Data){
    QVector<QString> Temp,Temp1;
    int s=0;
    for(int i=0;i<Data.length();++i){
        if(Data[i]!="-"){
            for(SemanticWebObject *j:head->next[0]->next[i]->next){
                if(j->GetName()==Data[i]){
                    TempCPU.clear();
                    SeekSemanticWebObjectInModel(j);
                    if(Temp.length()==0)Temp=TempCPU;
                    else{
                        Temp1.clear();
                        for(QString x:TempCPU){
                            for(QString y:Temp){
                                if(x==y)Temp1<<y;
                            }
                        }
                        Temp=Temp1;
                    }
                    break;
                }
            }
        }else ++s;
    }
    if(s==Data.length()){
        SeekSemanticWebObjectInModel(head->next[0]->next[0]);
        Temp=TempCPU;
    }
    return Temp;
}
QVector<QString> SemanticWeb::Find(QString Name){
    CPUData.clear();
    for(SemanticWebObject *i:head->next[1]->next){
        if(i->GetName()==Name){
            SeekSemanticWebObjectInModel1(i);
            break;
        }
    }
    return CPUData;
}
