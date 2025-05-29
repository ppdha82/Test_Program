#include "include/qlogger.h"
#include <QTextStream>
#include <QDateTime>
#include <QDir>
#include <iostream>
#include <QDebug>

using namespace std;

QString QLogger::filename = QString("./Qlog/QLog.txt");
QString QLogger::motionLogFile = QString("./Qlog/MotionLog.txt");
QTextEdit * QLogger::txtEditWidget = NULL;
QMutex QLogger::mutex_;
QFile QLogger::logFile_;
QFile QLogger::motionLogFile_;

QLogger::QLogger()
{
}

QLogger::~QLogger()
{
}

void QLogger::start()
{
    qInstallMsgHandler(myloggerfunction);

    QString SaveDir("./Qlog");
    QDir Dir(SaveDir);

    if(Dir.exists() == false)
    {
        QDir().mkpath(SaveDir);
    }

    if(logFile_.isOpen())
    {
        return;
    }

    logFile_.setFileName(filename);
    logFile_.open(QIODevice::Append | QIODevice::Text);

    if(motionLogFile_.isOpen())
    {
        return;
    }

    motionLogFile_.setFileName(motionLogFile);
    motionLogFile_.open(QIODevice::Append | QIODevice::Text);
}

void QLogger::finish()
{
    qInstallMsgHandler(0);
}

void QLogger::myloggerfunction(QtMsgType type, const char *msg)
{
    switch ((int)type)
    {
     case QtDebugMsg:
         finish();
         mutex_.lock();

         QString Msg(msg);

         if(Msg.contains("_MSG_"))
         {
             if(QLogger::txtEditWidget)
             {
                 QLogger::txtEditWidget->append(trUtf8(QString("%1: %2")
                                                        .arg(QDateTime::currentDateTime().toString("yyyy/MM/dd hh:mm:ss"))
                                                        .arg(Msg.remove("_MSG_")).toStdString().c_str()));

                 QTextStream streamer(&logFile_);
                 streamer << QDateTime::currentDateTime().toString("yyyy/MM/dd hh:mm:ss")
                          << Msg <<  "\n";
             }
         }
         else if(Msg.contains("_LOG_"))
         {
                 QTextStream streamer(&logFile_);
                 streamer << QDateTime::currentDateTime().toString("yyyy/MM/dd hh:mm:ss")
                          <<" Log:" << Msg.remove("_LOG_") <<  "\n";
         }
         else if(Msg.contains("_MOTION_"))
         {
             if(QLogger::txtEditWidget)
             {
                 QLogger::txtEditWidget->append(trUtf8(QString("%1: %2")
                                                        .arg(QDateTime::currentDateTime().toString("yyyy/MM/dd hh:mm:ss"))
                                                        .arg(Msg.remove("_MOTION_")).toStdString().c_str()));

                 QTextStream streamer(&motionLogFile_);
                 streamer << QDateTime::currentDateTime().toString("yyyy/MM/dd hh:mm:ss")
                          << Msg <<  "\n";
             }
         }
         else
         {
            qDebug() << Msg;
         }

         mutex_.unlock();
         break;
//     case QtWarningMsg:

//        if (logFile.open(QIODevice::Append | QIODevice::Text))
//        {
//             mutex_.lock();
//             QTextStream streamer(&logFile);
//             streamer << QDateTime::currentDateTime().toString("yyyy/MM/dd hh:mm:ss") <<" Warning: " << msg <<  "\n";
//             finish();
//             qWarning(msg);
//             logFile.close();
//             mutex_.unlock();
//        }
//        break;
//     case QtCriticalMsg:
//        if (logFile.open(QIODevice::Append | QIODevice::Text))
//        {
//            mutex_.lock();
//            QFile logFile(filename);
//            QTextStream streamer(&logFile);
//            streamer << QDateTime::currentDateTime().toString("yyyy/MM/dd hh:mm:ss") <<" Critical: " << msg <<  "\n";
//            finish();
//            qCritical(msg);
//            logFile.close();
//            mutex_.unlock();
//        }
//        break;
//     case QtFatalMsg:
//        if (logFile.open(QIODevice::Append | QIODevice::Text))
//        {
//            mutex_.lock();
//            QFile logFile(filename);
//            QTextStream streamer(&logFile);
//            streamer << QDateTime::currentDateTime().toString("yyyy/MM/dd hh:mm:ss") <<" Fatal: " << msg <<  "\n";
//            finish();
//            qFatal(msg);
//            logFile.close();
//            mutex_.unlock();
//        }
//        break;
    }

    start();
}


