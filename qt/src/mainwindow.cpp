#include "include/mainwindow.h"
#include "ui_mainwindow.h"

#include <QMessageBox>
#include <QDebug>
#include <QPalette>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    // pProc_ = new QProcess(parent);
    pGridlayout_ = new QGridLayout(ui->centralWidget);

    setupUi(this);
    connectWidgetEvent();
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

void MainWindow::setupUi(QMainWindow *w)
{
    testButton.setParent(w);
    testButton.setText("test");
    testButton.setGeometry(50, 40, 75, 30);

    layoutTestCommand = new QGridLayout();
    layoutTestCommand->setVerticalSpacing(0);
    layoutTestCommand->setHorizontalSpacing(0);
    layoutTestCommand->setContentsMargins(15, 0, 0, 0);

    layoutTestCommand->addWidget(new QLabel("Request"), 0, 0, 1, 1, Qt::AlignCenter);
    layoutTestCommand->addWidget(new QLabel("Response"), 0, 1, 1, 1, Qt::AlignCenter);
    layoutTestCommand->addWidget(new QLabel("Code"), 0, 2, 1, 1, Qt::AlignCenter);
    layoutTestCommand->addWidget(new QLabel("Ch"), 0, 3, 1, 1, Qt::AlignCenter);

    layoutTestCommand->addWidget(new QLabel("Request Data: "), 2, 0, 1, 2, Qt::AlignRight);
    layoutTestCommand->addWidget(new QLabel("Response Data: "), 3, 0, 1, 1, Qt::AlignRight);

    // pGridlayout_->addWidget(tablewidget_DIO,3, 0, 1, -1);
    setupTestCommandUILayout(ui->centralWidget);
    pGridlayout_->addLayout(layoutTestCommand, 3, 10, 1, -1, Qt::AlignRight);
    // pGridlayout_->addWidget(tablewidget_ETC,4, 0, 1, -1);

    // pGridlayout_->setRowStretch(0, 100);
    // pGridlayout_->setRowStretch(1, 10);

    ui->centralWidget->setLayout(pGridlayout_);
}

void MainWindow::connectWidgetEvent()
{
    connect(&testButton, SIGNAL(clicked()), this, SLOT(testclick()));
}

QLayout* MainWindow::setupTestCommandUILayout(QWidget *w)
{
    layoutTestCommand = new QGridLayout(w);
    layoutTestCommand->setVerticalSpacing(0);
    layoutTestCommand->setHorizontalSpacing(0);
    layoutTestCommand->setContentsMargins(15, 0, 0, 0);

    // combConvertData = new QComboBox();
    // combConvertData->addItems(QStringList() << "Dec" << "Hex");
    // combConvertData->setObjectName("DataConvert");

    // spinCode = new ShortHexSpinBox();
    // spinCode->setPrefix("0x");
    // spinCode->setValue(0);
    // spinCode->setMinimum(0);
    // spinCode->setMaximum(0xFFFF);

    // spinValue = new QSpinBox();
    // spinValue->setValue(0);
    // spinValue->setMinimum(std::numeric_limits<int32_t>::min());
    // spinValue->setMaximum(std::numeric_limits<int32_t>::max());
    // spinValue->setFixedWidth(85);

    // spinChannel = new QSpinBox();
    // spinChannel->setMinimum(0);
    // spinChannel->setMaximum(255);

    // LineEditRecievedValue = new QLineEdit();    
    // LineEditRecievedValue->setEnabled(false);

    // pubtnSend = new QPushButton("Send");
    // pubtnSend->setObjectName("Send");
    // pubtnSend->setFixedWidth(60);

    layoutTestCommand->addWidget(new QLabel("Request"), 0, 0, 1, 1, Qt::AlignCenter);
    layoutTestCommand->addWidget(new QLabel("Response"), 0, 1, 1, 1, Qt::AlignCenter);
    layoutTestCommand->addWidget(new QLabel("Code"), 0, 2, 1, 1, Qt::AlignCenter);
    layoutTestCommand->addWidget(new QLabel("Ch"), 0, 3, 1, 1, Qt::AlignCenter);

    // layoutTestCommand->addWidget(spinCode, 1, 2, 1, 1, Qt::AlignRight);
    // layoutTestCommand->addWidget(spinChannel, 1, 3, 1, 1, Qt::AlignLeft);
    layoutTestCommand->addWidget(new QLabel("Request Data: "), 2, 0, 1, 2, Qt::AlignRight);
    // layoutTestCommand->addWidget(spinValue, 2, 2, 1, 1, Qt::AlignLeft);
    // layoutTestCommand->addWidget(pubtnSend, 2, 3, 1, 1, Qt::AlignLeft);
    layoutTestCommand->addWidget(new QLabel("Response Data: "), 3, 0, 1, 1, Qt::AlignRight);
    // layoutTestCommand->addWidget(LineEditRecievedValue, 3, 1, 1, 2, Qt::AlignLeft);
    // layoutTestCommand->addWidget(combConvertData, 3, 3, 1, -1, Qt::AlignLeft);

    return layoutTestCommand;
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
#if defined(__ENABLE_QT4__)
    qDebug() << "[" << __FILE__ << ":" << __LINE__ << "] " << "Command[" << Command.toAscii() << "]";
#else
    qDebug() << "[" << __FILE__ << ":" << __LINE__ << "] " << "Command[" << Command.toLatin1() << "]";
#endif  /* __ENABLE_QT4__ */
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

void MainWindow::saveMessage()
{

}

void MainWindow::touchReceive()
{

}

void MainWindow::touchStore()
{
#if defined(__DEBUG_ON__)
    qDebug() << "[" << __FILE__ << ":" << __LINE__ << "]" << "Enter" << __func__;
#endif  /* __DEBUG_ON__ */
}

void MainWindow::loadMessage()
{

}

void MainWindow::clearMessage()
{

}
