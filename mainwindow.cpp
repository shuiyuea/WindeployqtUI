#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QDebug>
#include<QFile>
#include<QFileDialog>
#include<QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(&m_process,&QProcess::finished,this,&MainWindow::onCmdFinished);

    m_nCmdNumber = 0;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onCmdFinished()
{
    //命令执行完成
    ui->plainTextEdit->appendPlainText("----------------------------------------");

    QString strInfo;
    strInfo = "输出结果：" + QString::fromLocal8Bit(m_process.readAllStandardOutput());
    ui->plainTextEdit->appendPlainText(strInfo);

    strInfo = "错误信息：" + QString::fromLocal8Bit(m_process.readAllStandardError());
    ui->plainTextEdit->appendPlainText(strInfo);
}


void MainWindow::on_btnGenerate_clicked()
{
    //生成

    QStringList argument;
    //QString m_strCompiler="C:/Biancheng/Qt/6.5.2/msvc2019_64";
    //QString m_strTargetExe="E:/Biancheng/workspace/QT/learn/WindeployqtUI//release/WindeployqtUI.exe";

    //argument <<
    //    "/C" <<
    //    "C:/Biancheng/Qt/6.5.2/msvc2019_64/bin/qtenv2.bat "
    //    "&& windeployqt E:/Biancheng/workspace/QT/learn/WindeployqtUI//release/WindeployqtUI.exe";
    argument <<
        "/C" <<
        "set PATH="+ m_strCompiler+"/bin;%PATH%"
        "&& cd /D "+ m_strCompiler+
        "&& windeployqt "+ m_strTargetExe;
    m_process.start("cmd", argument);
}


void MainWindow::on_btnSelCompiler_clicked()
{
    //选择编译器目录
    QString strCompiler = SelDirectory();

    //验证编译器是否存在
    if (!QFile::exists(strCompiler + "/bin/windeployqt.exe"))
        QMessageBox::warning(this, "错误", "编译器目录无效，请重新选择！");
    else {
        m_strCompiler = strCompiler;
        ui->lineEdit->setText(m_strCompiler);
    }
}


void MainWindow::on_btnSelExe_clicked()
{
    //选择程序
    QString strTargetExe = SelFile();

    //验证文件是否存在
    if (!QFile::exists(strTargetExe))
        QMessageBox::warning(this, "错误", "程序不存在，请重新选择！");
    else {
        m_strTargetExe = strTargetExe;
        ui->lineEdit_2->setText(strTargetExe);
    }
}

QString MainWindow::SelDirectory()
{
    //选择目录，并返回对应路径
    QString strResult;

    strResult=QFileDialog::getExistingDirectory();

    return strResult;
}

QString MainWindow::SelFile()
{
    //选择文件，并返回对应路径
    QString strResult;

    strResult = QFileDialog::getOpenFileName();

    return strResult;
}

void MainWindow::GetSystemCompilerList()
{
    //获取当前系统已安装的编译器
}

void MainWindow::GetSystemAppList()
{
    //获取当前系统所有软件列表

}

