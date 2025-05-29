#ifndef __SETTINGS_H__
#define __SETTINGS_H__

#include <QWidget>
#include <QLabel>
#include <QGridLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QFileDialog>
#include <QTableWidget>
#include <QComboBox>

#include "qxml.h"

class Settings : public QWidget
{
    Q_OBJECT
public:
    explicit Settings(QWidget *parent = NULL, QGridLayout *parentLayout = NULL);

public:
    QLineEdit *lineEdit_Settings_file_Path;
    QGridLayout *layout;
    QPushButton * pushbtn_open_file;
    QTableWidget *tablewidget_Device_Settings;
    QPushButton * pushbtn_Save;
    QPushButton * pushbtn_Load;
    QXml xml_Parser;

    bool LoadSettings(const QString &xmlfile);
    void SaveSettings(const QString &xmlfile);

private:
    void connectWidgetEvent();
    void setupUI();

    QComboBox combobox_CommType[Table::LOW_SETTINGS_DEVICES];
    QTableWidget *tablewidget_Motor;

signals:
    void changed();

public slots:
    void PushButton_Slot(bool checked);
};

#endif // __SETTINGS_H__
