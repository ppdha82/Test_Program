#include "include/mainwindow.h"
#include "ui_mainwindow.h"

#include <QMessageBox>
#include <QDebug>
#include <QPalette>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent), ui(new Ui::MainWindow)
{
    // ui->setupUi(this);
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

void MainWindow::testclick()
{
#if defined(__DEBUG_ON__)
    qDebug() << "[" << __FILE__ << ":" << __LINE__ << "]" << "_MSG_" << "Clicked Test";
#endif  /* __DEBUG_ON__ */
}