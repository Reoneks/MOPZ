#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "productionmodel.h"
#include "framemodel.h"
#include "semanticweb.h"
MainWindow::MainWindow(QWidget *parent):QMainWindow(parent),ui(new Ui::MainWindow){
    ui->setupUi(this);
    this->setWindowFlags(Qt::MSWindowsFixedSizeDialogHint);
    setWindowTitle("МОПЗ_КР");
    QPalette pal;
    QPixmap map;
    map.load(":/image/images/MainwindowBackground.png");
    map=map.scaled(582,364,Qt::IgnoreAspectRatio,Qt::SmoothTransformation);
    pal.setBrush(ui->centralwidget->backgroundRole(),QBrush(map));
    ui->centralwidget->setPalette(pal);
    ui->centralwidget->setAutoFillBackground(true);
    combobox<<ui->Performance<<ui->AutoAcceleration<<ui->Frequency<<ui->Architecture<<ui->CoresThreads;
    QList<QRadioButton *> allButtons = ui->widget->findChildren<QRadioButton *>();
    for(int i=0;i<allButtons.size();++i){
        groupS.addButton(allButtons[i],i);
    }
    allButtons = ui->widget_3->findChildren<QRadioButton *>();
    for(int i=0;i<allButtons.size();++i){
        groupR.addButton(allButtons[i],i);
    }
    QVector<QString>Characteristic;
    Characteristic<<"Performance"<<"Auto Acceleration"<<"Frequency"<<"Architecture"<<"Cores Threads";
    QVector<QVector<QString>>Result;
    Database *database=new Database();
    for(int i=0;i<Characteristic.length();++i){
        Result=database->SelectRequest("SELECT ["+Characteristic[i]+"] "
                                       "FROM [CPU] "
                                       "GROUP BY ["+Characteristic[i]+"]",1);
        combobox[i]->addItem(" ");
        for(QVector<QString>j:Result){
            combobox[i]->addItem(j[0]);
        }
        ui->CoresThreads->setCurrentIndex(0);
    }
    Result=database->SelectRequest("SELECT [Name] "
                                   "FROM [CPU]",1);
    for(QVector<QString>i:Result){
        ui->CPU->addItem(i[0]);
    }
    ui->CPU->setCurrentIndex(0);
    delete database;
    ui->stackedWidget->setCurrentIndex(0);
}
MainWindow::~MainWindow(){
    delete ui;
}
void MainWindow::on_buttonBox_accepted(){
    QVector<QString> Data,Result;
    for(QComboBox *i:combobox){
        if(i->currentText()==" ")Data.append("-");
        else Data.append(i->currentText());
    }
    QString temp=groupS.checkedButton()->text();
    if(temp=="Семантическая сеть"){
        sw=new SemanticWeb();
        Result=sw->Find(Data);
    }
    else if(temp=="Фреймовая модель"){
        f=new FrameModel();
        Result=f->Find(Data);
    }
    else{
        p=new ProductionModel();
        Result=p->Find(Data);
    }
    ui->Console->clear();
    for(QString i:Result){
        ui->Console->append(i);
    }
}
void MainWindow::on_buttonBox_3_accepted(){
    QString temp=groupR.checkedButton()->text();
    QString Data;
    QVector<QString> Result;
    if(ui->CPU->currentText()==" ")Data="-";
    else Data=ui->CPU->currentText();
    if(temp=="Семантическая сеть"){
        sw=new SemanticWeb();
        Result=sw->Find(Data);
    }
    else if(temp=="Фреймовая модель"){
        f=new FrameModel();
        Result=f->Find(Data);
    }
    else{
        p=new ProductionModel();
        Result=p->Find(Data);
    }
    ui->Console1->clear();
    for(QString i:Result){
        ui->Console1->append(i);
    }
}
void MainWindow::on_buttonBox_rejected(){
    ui->stackedWidget->setCurrentIndex(0);
}
void MainWindow::on_StraightRun_clicked(){
    ui->stackedWidget->setCurrentIndex(1);
}
void MainWindow::on_Reverse_clicked(){
    ui->stackedWidget->setCurrentIndex(2);
}
void MainWindow::on_buttonBox_3_rejected(){
    ui->stackedWidget->setCurrentIndex(0);
}
void MainWindow::on_pushButton_clicked(){
    ui->Console1->clear();
}
void MainWindow::on_pushButton_2_clicked(){
    ui->Console->clear();
}
