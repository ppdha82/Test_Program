#ifndef __MAINWINDOW_H__
#define __MAINWINDOW_H__

#include <QMainWindow>
#include <QPushButton>
#include <QProcess>
#include <QThread>
#include <QDir>
#include <QGridLayout>
#include <QLayout>
#include <QLabel>
#include <QComboBox>

class QMSound : public QWidget
{
    Q_OBJECT
public:
    explicit QMSound(QWidget *parent = 0) : QWidget(parent)
    {
        pProc_ = new QProcess(parent);
        homePath_ = QDir::homePath();
    };

    ~QMSound()
    {
        pProc_->close();
        delete pProc_;
    };

    void playSound(QString fileName)
    {
        QStringList param = QStringList() << QString("--volume=65536")
                                          << QString("%1/.QMonitoring/sounds/%2").arg(homePath_).arg(fileName);
        pProc_->execute("paplay", param);
    };

private:
    QProcess *pProc_;
    QString homePath_;
};

class QMThread : public QThread
{
    Q_OBJECT

public:
    explicit QMThread(QObject *parent = 0);

    void customSleep();

private:
};

namespace Ui
{
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    virtual ~MainWindow();

    Ui::MainWindow *getMainWindow();

signals:
    
public slots:
    void testclick();
    void saveMessage();
    void touchReceive();
    void touchStore();
    void loadMessage();
    void clearMessage();

private:
    void setupUi(QMainWindow *);
    void removeSshKeyfile();
    void generateSshKeyfile();
    void connectWidgetEvent();
    void setupTestCommandUILayout(QGridLayout*);

    QPushButton testButton;
    // QProcess *pProc_;
    Ui::MainWindow *ui;

    QGridLayout *layoutTestCommand;
    QPushButton *testButton2;
    QLabel *Request;
    QLabel *Response;
    QLabel *Code;
    QLabel *Ch;
    QLabel *RequestData;
    QLabel *ResponseData;
    QComboBox *combConvertData;
};

#endif // __MAINWINDOW_H__
