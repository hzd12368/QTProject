#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "qmessagebox.h"
#include "QFile"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    QString EXEName_src = ":/exe/A.exe";
    QString EXEName_Dst = "~A.exe";
    QFile EXEFile_src(EXEName_src);
    QFile EXEFile_Dst(EXEName_Dst);
   //对资源里的exe进行重新生成
    if(EXEFile_Dst.open (QIODevice::WriteOnly)){
       if(EXEFile_src.open(QIODevice::ReadOnly)){
       QByteArray tmp = EXEFile_src.readAll();
       EXEFile_Dst.write(tmp);
       }
    }
    EXEFile_Dst.close();

    QString EXEPara = ui->lineEdit->text(); //获取参数

    if (EXEPara.isEmpty()){
        QFile::remove(EXEName_Dst); //删掉exe文件
        QMessageBox::about(this,"Error","确保程序参数存在!!!");
        return;
    }

    QString CMD = EXEName_Dst + " " + EXEPara;
    //执行CMD命令
    char* ptr;
    QByteArray ba = CMD.toLocal8Bit(); //支持含中文
    ptr = ba.data();
    system(ptr);

   QFile::remove(EXEName_Dst); //删掉exe文件

}
