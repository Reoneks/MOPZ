#include "framemodel.h"
FrameModel::FrameModel(){
    head=nullptr;
    FrameAdded=false;
    GenerateModel();
}
void FrameModel::GenerateModel(){
    Database *database=new Database();
    QVector<QVector<QString>>Result=database->SelectRequest("SELECT [ISA],[Performance],[Auto Acceleration],[Frequency],[Architecture],[Cores Threads] "
                                                            "FROM [Frame model] "
                                                            "ORDER BY [ID]",6);
    QVector<QVector<QString>>Result1=database->SelectRequest("SELECT [Frame name] "
                                                             "FROM [Frame model] "
                                                             "ORDER BY [ID]",1);
    delete database;
    int j=0;
    for(QVector<QString>i:Result){
        QStringList temp2=i[0].split(" ")[3].split("|");
        QString Temp3;
        for(int k=0;k<temp2.length();++k){
            if(k!=temp2.length()-1)Temp3+=temp2[k]+" ";
            else Temp3+=temp2[k];
        }
        FrameAdded=false;
        AddFrameInModel(Temp3,head,CreateFrame(i,Result1[j][0]));
        ++j;
    }
}
Frame* FrameModel::CreateFrame(QVector<QString>Data,QString name){
    QVector<QVector<QString>>Result;
    for(QString i:Data){
        QVector<QString>Temp;
        QStringList temp1=i.split(" ");
        for(QString j:temp1){
            QStringList temp2=j.split("|");
            QString Temp3;
            for(int k=0;k<temp2.length();++k){
                if(k!=temp2.length()-1)Temp3+=temp2[k]+" ";
                else Temp3+=temp2[k];
            }
            Temp<<Temp3;
        }
        Result<<Temp;
    }
    Frame *f=new Frame();
    f->SetData(Result);
    f->SetName(name);
    return f;
}
void FrameModel::AddFrameInModel(QString ParentFrameName, Frame* CurrentFrame, Frame *FrameToAdd){
    if(head==nullptr){
        head=FrameToAdd;
        return;
    }else{
        if(CurrentFrame->GetName()==ParentFrameName){
            FrameToAdd->prev=CurrentFrame;
            CurrentFrame->next.append(FrameToAdd);
            FrameAdded=true;
            return;
        }else{
            for(Frame *f:CurrentFrame->next){
                AddFrameInModel(ParentFrameName,f,FrameToAdd);
                if(FrameAdded)return;
            }
        }
    }
}
void FrameModel::SeekFrameInModel(QVector<QString>Data,Frame* CurrentFrame){
    if(CurrentFrame->next.length()==0){
        int k=0;
        QVector<QVector<QString>> TempData=CurrentFrame->GetData();
        for(int i=0;i<TempData.length();++i){
            if(TempData[i][1]=="S"){
                Frame *temp=CurrentFrame->prev;
                while(temp->GetData()[i][1]=="S"){
                    temp=temp->prev;
                }
                TempData[i][3]=temp->GetData()[i][3];
            }
        }
        for(int i=0;i<Data.length();++i){
            if(Data[i]!="-"){
                if(Data[i]==TempData[i][3]) ++k;
            }else ++k;
        }
        if(k==Data.length())CPU.append(CurrentFrame->GetName());
    }
    for(Frame *f:CurrentFrame->next){
        SeekFrameInModel(Data,f);
    }
}
void FrameModel::SeekFrameInModel(QString Name,Frame* CurrentFrame){
    if(CurrentFrame->GetName()==Name){
        SoughtFrame=CurrentFrame;
        return;
    }else{
        for(Frame *f:CurrentFrame->next){
            SeekFrameInModel(Name,f);
            if(SoughtFrame!=nullptr)return;
        }
    }
}
QVector<QString> FrameModel::Find(QVector<QString>Data){
    CPU.clear();
    SeekFrameInModel(Data,head);
    return CPU;
}
QVector<QString> FrameModel::Find(QString Name){
    SoughtFrame=nullptr;
    SeekFrameInModel(Name,head);
    QVector<QVector<QString>> TempData=SoughtFrame->GetData();
    for(int i=0;i<TempData.length();++i){
        if(TempData[i][1]=="S"){
            Frame *temp=SoughtFrame->prev;
            while(temp->GetData()[i][1]=="S"){
                temp=temp->prev;
            }
            TempData[i][3]=temp->GetData()[i][3];
        }
    }
    QVector<QString> Temp;
    for(QVector<QString> i:TempData){
        Temp<<i[0]+": "+i[3];
    }
    return Temp;
}
