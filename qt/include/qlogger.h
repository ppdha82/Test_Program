#ifndef QLOGGER_H
#define QLOGGER_H

#include <QtCore/QObject>
#include <QtCore/QFile>
#include <QtCore/QDateTime>
#include <QTextEdit>
#include <QMutex>

class QLogger : public QObject
{
Q_OBJECT

public:
    QLogger();
    ~QLogger();

    static QTextEdit * txtEditWidget;
    static void start();
    static void finish();
    static void setWidget(QTextEdit* w) {txtEditWidget = w;};

    static QString filename;
    static QString motionLogFile;
    static QMutex  mutex_;
    static QFile logFile_;
    static QFile motionLogFile_;

private:
    static void myloggerfunction(QtMsgType type, const char *msg);

};

#endif // QLOGGER_H
