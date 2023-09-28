#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QProcess>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_btnGenerate_clicked();

    void onCmdFinished();

    void on_btnSelCompiler_clicked();

    void on_btnSelExe_clicked();

private:
    QString SelDirectory();
    
    QString SelFile();

    void GetSystemCompilerList();   //获取当前系统已安装的编译器

    void GetSystemAppList();        //获取当前系统所有软件列表

private:
    Ui::MainWindow *ui;

    QProcess m_process;

    int m_nCmdNumber;

    QString m_strCompiler;

    QString m_strTargetExe;
};
#endif // MAINWINDOW_H
