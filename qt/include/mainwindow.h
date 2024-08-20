#ifndef __MAINWINDOW_H__
#define __MAINWINDOW_H__

#include <QMainWindow>
#include <QPushButton>
#include <QProcess>
#include <QDir>

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

    void setupUi(QWidget *);
    void removeSshKeyfile();
    void generateSshKeyfile();

    Ui::MainWindow *getMainWindow();

signals:
    
public slots:
    void testclick();

private:
    QPushButton testButton;
    QProcess *pProc_;
    Ui::MainWindow *ui;
};

#endif // __MAINWINDOW_H__
