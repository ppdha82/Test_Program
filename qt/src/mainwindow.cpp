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
    pGridlayout_ = new QGridLayout(this);

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
    // testButton.setParent(w);
    // testButton.setText("test");
    // testButton.setGeometry(50, 40, 75, 30);

    layoutTestCommand = new QGridLayout(w);
    layoutTestCommand->setVerticalSpacing(0);
    layoutTestCommand->setHorizontalSpacing(0);
    layoutTestCommand->setContentsMargins(15, 0, 0, 0);

    layoutTestCommand->addWidget(new QLabel("Request"), 0, 0, 1, 1, Qt::AlignCenter);
    layoutTestCommand->addWidget(new QLabel("Response"), 0, 1, 1, 1, Qt::AlignCenter);
    layoutTestCommand->addWidget(new QLabel("Code"), 0, 2, 1, 1, Qt::AlignCenter);
    layoutTestCommand->addWidget(new QLabel("Ch"), 0, 3, 1, 1, Qt::AlignCenter);

    // layoutTestCommand->addWidget(combReqType, 1, 0, 1, 1 ,Qt::AlignRight);
    // layoutTestCommand->addWidget(combResType, 1, 1, 1, 1, Qt::AlignRight);
    // layoutTestCommand->addWidget(spinCode, 1, 2, 1, 1, Qt::AlignRight);
    // layoutTestCommand->addWidget(spinChannel, 1, 3, 1, 1, Qt::AlignLeft);
    layoutTestCommand->addWidget(new QLabel("Request Data: "), 2, 0, 1, 2, Qt::AlignRight);
    // layoutTestCommand->addWidget(spinValue, 2, 2, 1, 1, Qt::AlignLeft);
    // layoutTestCommand->addWidget(pubtnSend, 2, 3, 1, 1, Qt::AlignLeft);
    layoutTestCommand->addWidget(new QLabel("Response Data: "), 3, 0, 1, 1, Qt::AlignRight);
    // layoutTestCommand->addWidget(LineEditRecievedValue, 3, 1, 1, 2, Qt::AlignLeft);
    // layoutTestCommand->addWidget(combConvertData, 3, 3, 1, -1, Qt::AlignLeft);

    // pGridlayout_->addWidget(splitter,1, 0, 1, -1);
    // pGridlayout_->addWidget(pbntTakeTable_,2, 0, 1, -1);
    // pGridlayout_->addWidget(pSplitter_,2, 0, 1, -1);

    // pGridlayout_->addWidget(tablewidget_DIO,3, 0, 1, -1);
    // setupTestCommandUILayout(w);
    // pGridlayout_->addLayout(layoutTestCommand, 3, 10, 1, -1, Qt::AlignRight);
    // pGridlayout_->addWidget(tablewidget_ETC,4, 0, 1, -1);

    // pGridlayout_->setRowStretch(0, 100);
    // pGridlayout_->setRowStretch(1, 10);
    // pGridlayout_->setRowStretch(2, 100);
    // pGridlayout_->setRowStretch(3, 50);
    // pGridlayout_->setRowStretch(4, 70);

    // setLayout(pGridlayout_);

    // QGridLayout *leftLayout = new QGridLayout;
    // leftLayout->addWidget(new QLabel("namedLabel"), 0, 0);
    // leftLayout->addWidget(new QLabel("namedLineEdit"), 0, 1);
    // leftLayout->addWidget(new QLabel("lookInLabel"), 1, 0);
    // leftLayout->addWidget(new QLabel("lookInLineEdit"), 1, 1);
    // leftLayout->addWidget(new QLabel("subfoldersCheckBox"), 2, 0, 1, 2);
    // leftLayout->addWidget(new QLabel("tableWidget"), 3, 0, 1, 2);
    // leftLayout->addWidget(new QLabel("messageLabel"), 4, 0, 1, 2);

    // QVBoxLayout *rightLayout = new QVBoxLayout;
    // rightLayout->addWidget(new QLabel("findButton"));
    // rightLayout->addWidget(new QLabel("stopButton"));
    // rightLayout->addWidget(new QLabel("closeButton"));
    // rightLayout->addStretch();
    // rightLayout->addWidget(new QLabel("helpButton"));

    // QHBoxLayout *mainLayout = new QHBoxLayout;
    // mainLayout->addLayout(leftLayout);
    // mainLayout->addLayout(rightLayout);
    // setLayout(mainLayout);

    // setWindowTitle(tr("Find Files or Folders"));
}

void MainWindow::connectWidgetEvent()
{
    connect(&testButton, SIGNAL(clicked()), this, SLOT(testclick()));
    // connect(combConvertData, SIGNAL(currentIndexChanged(int)), this, SLOT(comboboxChangeIndex(int)));
    // connect(pubtnSend, SIGNAL(clicked(bool)), this, SLOT(PushButton_Slot(bool)));
}

QLayout* MainWindow::setupTestCommandUILayout(QWidget *w)
{
    QStringList Types = QStringList() << "NONE" << "INT32" << "UINT32" << "GRIP" << "UINT16" << "FLOAT" << "CHAR" << "MOTOR"
                                      << "ARM" << "GATHER" << "SYSTEM" << "PLAYBACK" << "INT32A" << "FLOATA" << "CHARA" << "ERROR";

    layoutTestCommand = new QGridLayout(w);
    layoutTestCommand->setVerticalSpacing(0);
    layoutTestCommand->setHorizontalSpacing(0);
    layoutTestCommand->setContentsMargins(15, 0, 0, 0);

    // combReqType = new QComboBox();
    // combReqType->addItems(Types);
    // combReqType->setFixedWidth(80);

    // combResType = new QComboBox();
    // combResType->addItems(Types);
    // combResType->setFixedWidth(80);

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

    // layoutTestCommand->addWidget(combReqType, 1, 0, 1, 1 ,Qt::AlignRight);
    // layoutTestCommand->addWidget(combResType, 1, 1, 1, 1, Qt::AlignRight);
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

}

void MainWindow::loadMessage()
{

}

void MainWindow::clearMessage()
{

}
