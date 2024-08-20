#include "include/mainwindow.h"
#include "ui_mainwindow.h"

#include <QMessageBox>
#include <QDebug>
#include <QPalette>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent), ui(new Ui::MainWindow)
{
    // ui->setupUi(this);
    pProc_ = new QProcess(parent);
    setupUi(this);
#if defined(__DEBUG_ON__)
    qDebug() << "[" << __FILE__ << ":" << __LINE__ << "]" << "_MSG_" << "Start";
#endif  /* __DEBUG_ON__ */
}

MainWindow::~MainWindow()
{
    delete ui;
#if defined(__DEBUG_ON__)
    qDebug() << "[" << __FILE__ << ":" << __LINE__ << "]" << "Destory Mainwindow";
    qDebug() << "[" << __FILE__ << ":" << __LINE__ << "]" << "_MSG_" << "End";
#endif  /* __DEBUG_ON__ */
}

Ui::MainWindow* MainWindow::getMainWindow()
{
    return ui;
}

void MainWindow::setupUi(QWidget *w)
{
    testButton.setParent(w);
    testButton.setText("test");
    testButton.setGeometry(50, 40, 75, 30);
    connect(&testButton, SIGNAL(clicked()), this, SLOT(testclick()));
}

void MainWindow::removeSshKeyfile()
{
    QString Command = "rm " + QDir().homePath() + "/.ssh/known_hosts";
    QProcess proc1;
#if defined(__DEBUG_ON__)
    qDebug() << "[" << __FILE__ << ":" << __LINE__ << "] " << "proc1.state()[" << proc1.state() << "]";
#endif  /* __DEBUG_ON__ */
    proc1.start(QString("rm"), QStringList() << QString(QDir().homePath() + "/.ssh/known_hosts"));
    if (proc1.waitForStarted(1000)) {
#if defined(__DEBUG_ON__)
        qDebug() << "[" << __FILE__ << ":" << __LINE__ << "] " << "proc1.state()[" << proc1.state() << "]";
#endif  /* __DEBUG_ON__ */
        if (proc1.waitForFinished(1000)) {
            QByteArray output = proc1.readAllStandardOutput();
#if defined(__DEBUG_ON__)
            qDebug() << "[" << __FILE__ << ":" << __LINE__ << "] " << "proc1.state()[" << proc1.state() << "]";
            qDebug() << "[" << __FILE__ << ":" << __LINE__ << "] " << "command output:" << output;
#endif  /* __DEBUG_ON__ */
        }
        else {
#if defined(__DEBUG_ON__)
            qDebug() << "[" << __FILE__ << ":" << __LINE__ << "] " << "proc1.state()[" << proc1.state() << "]";
            qDebug() << "[" << __FILE__ << ":" << __LINE__ << "] " << "Failed to run proc1";
#endif  /* __DEBUG_ON__ */
        }
    }
    proc1.close();
#if defined(__DEBUG_ON__)
    qDebug() << "[" << __FILE__ << ":" << __LINE__ << "] " << "proc1.state()[" << proc1.state() << "]";
    qDebug() << "[" << __FILE__ << ":" << __LINE__ << "] " << "Command[" << Command.toAscii() << "]";
#endif  /* __DEBUG_ON__ */
}

void MainWindow::generateSshKeyfile()
{
    QString ssh_keyfile_path = QDir().homePath() + "/.ssh/known_hosts";
#if defined(__DEBUG_ON__)
    qDebug() << "[" << __FILE__ << ":" << __LINE__ << "] " << "ssh_keyfile_path[" << ssh_keyfile_path << "]";
#endif  /* __DEBUG_ON__ */
    QProcess proc1;
    proc1.start(QString("ssh-keygen"), QStringList() << "-f" << ssh_keyfile_path << "-R" << "192.168.38.9");
    if (proc1.waitForStarted(1000)) {
        if (proc1.waitForFinished(5000)) {
            QByteArray output = proc1.readAllStandardOutput();
#if defined(__DEBUG_ON__)
            qDebug() << "[" << __FILE__ << ":" << __LINE__ << "] " << "command output:" << output;
#endif  /* __DEBUG_ON__ */
        }
        else {
#if defined(__DEBUG_ON__)
            qDebug() << "[" << __FILE__ << ":" << __LINE__ << "] " << "Failed to run proc";
#endif  /* __DEBUG_ON__ */
            proc1.close();
            return;
        }
    }
}

void MainWindow::testclick()
{
    removeSshKeyfile();
    generateSshKeyfile();

#if defined(__DEBUG_ON__)
    qDebug() << "[" << __FILE__ << ":" << __LINE__ << "]" << "_MSG_" << "Clicked Test";
#endif  /* __DEBUG_ON__ */
}