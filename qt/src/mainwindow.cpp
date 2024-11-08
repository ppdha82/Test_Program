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

    setupTestCommandUILayout(ui->gridLayout);
}

void MainWindow::connectWidgetEvent()
{
    connect(&testButton, SIGNAL(clicked()), this, SLOT(testclick()));

    onPing.setParent(w);
    onPing.setText("Ping");
    onPing.setGeometry(150, 100, 80, 50);
    onPing.setCheckable(true);
    connect(&onPing, SIGNAL(clicked()), this, SLOT(onClickPing()));

    connect(&proc1, SIGNAL(started()), this, SLOT(onPingStarted()));
}

void MainWindow::setupTestCommandUILayout(QGridLayout *grid)
{
    // setStyleSheet
    QString StyleSheetDefault = "QLabel { background-color: %1; width: 1px; margin: 0px; text-align: center;}";
    QString StyleSheetGreen = StyleSheetDefault.arg("green");
    QString StyleSheetYellow = StyleSheetDefault.arg("yellow");
    QString StyleSheetRed = StyleSheetDefault.arg("red");
    int count = 0;

    Request = new QLabel(QString("Request_%1").arg(count++));
    Response = new QLabel(QString("Response_%1").arg(count++));
    Code = new QLabel(QString("Code_%1").arg(count++));
    Ch = new QLabel(QString("Ch_%1").arg(count++));
    RequestData = new QLabel(QString("Request Data: _%1").arg(count++));
    ResponseData = new QLabel(QString("Response Data: _%1").arg(count++));
    testButton2 = new QPushButton(QString("pushbutton_test_test_test_%1").arg(count++));

    Request->setStyleSheet(StyleSheetGreen);
    Response->setStyleSheet(StyleSheetYellow);
    Code->setStyleSheet(StyleSheetRed);
    Ch->setStyleSheet(StyleSheetGreen);
    RequestData->setStyleSheet(StyleSheetYellow);
    ResponseData->setStyleSheet(StyleSheetRed);
    testButton2->setStyleSheet(StyleSheetRed);

    QRect rect = Request->geometry();
    QSize size(200, 100);
    rect.setSize(size);
    Request->setFrameRect(rect);
    Request->setFrameShape(QFrame::Box);
    Response->setFrameShape(QFrame::Panel);
    Code->setFrameShape(QFrame::StyledPanel);
    Ch->setFrameShape(QFrame::HLine);
    RequestData->setFrameShape(QFrame::VLine);
    ResponseData->setFrameShape(QFrame::WinPanel);

    layoutTestCommand = grid;

    layoutTestCommand->setVerticalSpacing(0);
    layoutTestCommand->setHorizontalSpacing(0);
    layoutTestCommand->setContentsMargins(15, 0, 15, 15);

    combConvertData = new QComboBox();
    combConvertData->addItems(QStringList() << "Dec" << "Hex");
    combConvertData->setObjectName("DataConvert");

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

    layoutTestCommand->addWidget(Request, 1, 0, 1, 1, Qt::AlignCenter);
    layoutTestCommand->addWidget(Response, 1, 1, 1, 1, Qt::AlignCenter);
    layoutTestCommand->addWidget(Code, 1, 2, 1, 1, Qt::AlignCenter);
    layoutTestCommand->addWidget(Ch, 1, 3, 1, 1, Qt::AlignCenter);
    layoutTestCommand->addWidget(testButton2, 2, 3, 1, 3, Qt::AlignCenter);

    layoutTestCommand->addWidget(RequestData, 3, 0, 1, 3, Qt::AlignCenter);
    layoutTestCommand->addWidget(combConvertData, 3, 3, 1, -1, Qt::AlignLeft);
    layoutTestCommand->addWidget(ResponseData, 4, 0, 1, 1, Qt::AlignCenter);

    // layoutTestCommand->addWidget(spinCode, 1, 2, 1, 1, Qt::AlignRight);
    // layoutTestCommand->addWidget(spinChannel, 1, 3, 1, 1, Qt::AlignLeft);
    // layoutTestCommand->addWidget(spinValue, 2, 2, 1, 1, Qt::AlignLeft);
    // layoutTestCommand->addWidget(pubtnSend, 2, 3, 1, 1, Qt::AlignLeft);
    // layoutTestCommand->addWidget(LineEditRecievedValue, 3, 1, 1, 2, Qt::AlignLeft);
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
            qDebug() << "[" << __FILE__ << ":" << __LINE__ << "] " << "command output:" << output;
#endif  /* __DEBUG_ON__ */
        }
        else {
#if defined(__DEBUG_ON__)
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
#if defined(__DEBUG_ON__)
    qDebug() << "[" << __FILE__ << ":" << __LINE__ << "] Enter" << __func__;
#endif  /* __DEBUG_ON__ */
    QString StyleSheetDefault = "QLabel { background-color: %1; width: 1px; margin: 0px; text-align: center;}";
    QString StyleSheetGreen = StyleSheetDefault.arg("green");
    static int count = 0;

    QString strRequest = QString("Request_%1").arg(count++);
    if (Request == NULL) {
        Request = new QLabel(strRequest);
    }
    else {
        Request->setText(strRequest);
    }
    Request->setStyleSheet(StyleSheetGreen);
    layoutTestCommand->addWidget(Request, 1, 0, 1, 1, Qt::AlignCenter);
}

void MainWindow::touchReceive()
{
#if defined(__DEBUG_ON__)
    qDebug() << "[" << __FILE__ << ":" << __LINE__ << "] Enter" << __func__;
#endif  /* __DEBUG_ON__ */
}

void MainWindow::touchStore()
{
#if defined(__DEBUG_ON__)
    qDebug() << "[" << __FILE__ << ":" << __LINE__ << "]" << "Enter" << __func__;
#endif  /* __DEBUG_ON__ */
}

void MainWindow::loadMessage()
{
#if defined(__DEBUG_ON__)
    qDebug() << "[" << __FILE__ << ":" << __LINE__ << "] Enter" << __func__;
#endif  /* __DEBUG_ON__ */
}

void MainWindow::clearMessage()
{
#if defined(__DEBUG_ON__)
    qDebug() << "[" << __FILE__ << ":" << __LINE__ << "] Enter" << __func__;
#endif  /* __DEBUG_ON__ */
#if defined(__DEBUG_ON__)
    QRect rect;
    for (int i = 0;i < layoutTestCommand->rowCount();i++) {
        qDebug() << "[" << __FILE__ << ":" << __LINE__ << "] i[" << i << "/" << layoutTestCommand->rowCount() << "]";
        for (int j = 0;j < layoutTestCommand->columnCount();j++) {
            qDebug() << "[" << __FILE__ << ":" << __LINE__ << "] i[" << j << "/" << layoutTestCommand->columnCount() << "]";
            if (layoutTestCommand->itemAtPosition(i, j) == NULL) {
                qDebug() << "[" << __FILE__ << ":" << __LINE__ << "] layoutTestCommand->itemAtPosition(" << i << "," << j << ") NULL";
                continue;
            }
            rect = layoutTestCommand->itemAtPosition(i, j)->geometry();
            qDebug() << "[" << __FILE__ << ":" << __LINE__ << "] layoutTestCommand(" << i << "," << j << ")->geometry()[" << rect << "] w[" << rect.width() << "] h[" << rect.height() << "]";
        }
    }
#endif  /* __DEBUG_ON__ */
}
