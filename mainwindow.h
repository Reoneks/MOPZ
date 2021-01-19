#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include <QButtonGroup>
#include <QComboBox>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE
class FrameModel;
class ProductionModel;
class SemanticWeb;
class MainWindow : public QMainWindow{
    Q_OBJECT
    QButtonGroup groupS,groupR;
    QList<QComboBox *> combobox;
    FrameModel *f;
    ProductionModel *p;
    SemanticWeb *sw;
    public:
        MainWindow(QWidget *parent = nullptr);
        ~MainWindow();
    private slots:
        void on_buttonBox_accepted();
        void on_buttonBox_rejected();
        void on_StraightRun_clicked();
        void on_Reverse_clicked();
        void on_buttonBox_3_accepted();
        void on_buttonBox_3_rejected();
        void on_pushButton_clicked();
        void on_pushButton_2_clicked();
    private:
        Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
