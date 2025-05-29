#include "include/settings.h"

#include <QHeaderView>
#include <QTextEdit>
#include <QMessageBox>


Settings::Settings(QWidget *parent, QGridLayout* parentLayout) :
    QWidget(parent)
{
    // layout = new QGridLayout;
    layout = parentLayout;

    lineEdit_Settings_file_Path = new QLineEdit;
    lineEdit_Settings_file_Path->setReadOnly(true);
    pushbtn_open_file = new QPushButton;
    pushbtn_open_file->setText("...");
    pushbtn_open_file->setObjectName("...");

    pushbtn_Save = new QPushButton(STR_SAVE);
    pushbtn_Save->setObjectName(STR_SAVE);

    pushbtn_Load = new QPushButton(STR_LOAD);
    pushbtn_Load->setObjectName(STR_LOAD);

    tablewidget_Device_Settings = new QTableWidget(Table::LOW_SETTINGS_DEVICES, Table::COLUMN_SETTINGS_DEVICES);

    setupUI();
    connectWidgetEvent();

    if(parent)
    {
        parent->setLayout(layout);
    }
}

void Settings::connectWidgetEvent()
{
    connect(pushbtn_open_file, SIGNAL(clicked(bool)), this, SLOT(PushButton_Slot(bool)));
    connect(pushbtn_Save, SIGNAL(clicked(bool)), this, SLOT(PushButton_Slot(bool)));
    connect(pushbtn_Load, SIGNAL(clicked(bool)), this, SLOT(PushButton_Slot(bool)));
}

void Settings::setupUI()
{
    tablewidget_Motor = new QTableWidget(Table::ROW, Table::COLUMN_MOTOR);
    tablewidget_Motor->setHorizontalHeaderLabels(QStringList() << Table::CURRENT_KP_GAIN << Table::CURRENT_KI_GAIN
                                                 << Table::CURRENT_KA_GAIN << Table::CURRENT_KFF_GAIN
                                                 << Table::CURRENT_MAX_VOLT_GAIN << Table::LQR_POS_GAIN << Table::LQR_VEL_GAIN
                                                 << Table::LQR_CURR_GAIN << Table::LQR_POS_INT_GAIN << Table::LQR_MAX_VOLT_GAIN
                                                 << Table::POS_P_GAIN << Table::POS_I_GAIN << Table::POS_D_GAIN
                                                 << Table::LIMIT_TRJGAP << Table::LIMIT_ACCEL << Table::LIMIT_VEL
                                                 << Table::LIMIT_CURR << Table::ERROR_DEG << Table::JLIMIT_MIN << Table::JLIMIT_MAX
                                                 << Table::STALL_RATIO << Table::VELOCITY_RATIO << Table::ABSOLUTE_HOME
                                                 << Table::G_COMP << Table::G_OFFSET << Table::F_COMP << Table::MOTOR_MADV
                                                 << Table::ABSOLUTE_MADV << Table::UNDERCURRENT_CURRATIO << Table::UNDERCURRENT_VOLTRATIO
                                                 << Table::STIFFNESS_CONSTANT << Table::STIFFNESS_CURRENT << Table::CUR_LPF_CUR << Table::CUR_LPF_VEL
                                                 << Table::LQR_LPF_CUR << Table::LQR_LPF_VEL << Table::PID_LPF_CUR << Table::PID_LPF_VEL);

    tablewidget_Motor->setVerticalHeaderLabels(QStringList() << STR_ALL << "0" << "1" << "2" << "3" << "4" << "5" << "6");
    tablewidget_Motor->setAlternatingRowColors(true);
    tablewidget_Motor->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    tablewidget_Motor->setMinimumHeight(240);


    lineEdit_Settings_file_Path->setText(QString(VER));
    layout->addWidget(new QLabel(STR_VERSION), 0, 0, 1, 1);
    layout->addWidget(new QLabel(VER), 0, 1, 1, 1);
    layout->addWidget(new QLabel(STR_LOAD_SETTINGS_FILE), 1, 0, 1, 1);
    layout->addWidget(lineEdit_Settings_file_Path, 1, 1, 1, 8);
    layout->addWidget(pushbtn_open_file, 1, 9, 1, 1);
    layout->addWidget(new QLabel(QString("Devices Settings")), 2,0,1,1);
    layout->addWidget(tablewidget_Device_Settings, 3,0,1,6);
    layout->addWidget(pushbtn_Load, 4,4,1,1);
    layout->addWidget(pushbtn_Save, 4,5,1,1);
    layout->addWidget(tablewidget_Motor, 5, 0, 7, 0);

    tablewidget_Device_Settings->setHorizontalHeaderLabels(QStringList()
                                                         << Table::IP << Table::Port
                                                         << Table::Refresh_Time << Table::Comm_Type);

    tablewidget_Device_Settings->setVerticalHeaderLabels(QStringList()
                                                         << Table::Master_L << Table::Master_R
                                                         << Table::Slave_A << Table::Slave_B
                                                         << Table::Slave_C << Table::Slave_D
                                                         << Table::Console << Table::Mobile
                                                         << Table::Vision << Table::Operation);

    tablewidget_Device_Settings->setColumnWidth(0, 150);
#if defined(__ENABLE_QT4__)
    tablewidget_Device_Settings->horizontalHeader()->setResizeMode(1, QHeaderView::Stretch);
    tablewidget_Device_Settings->horizontalHeader()->setResizeMode(2, QHeaderView::Stretch);
    tablewidget_Device_Settings->horizontalHeader()->setResizeMode(3, QHeaderView::Stretch);
#else
    tablewidget_Device_Settings->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch);
    tablewidget_Device_Settings->horizontalHeader()->setSectionResizeMode(2, QHeaderView::Stretch);
    tablewidget_Device_Settings->horizontalHeader()->setSectionResizeMode(3, QHeaderView::Stretch);
#endif  /* __ENABLE_QT4__ */

    for(int v = 0; v < tablewidget_Device_Settings->verticalHeader()->count(); v++ )
    {
        for(int h = 0; h < tablewidget_Device_Settings->horizontalHeader()->count(); h++ )
        {
            if(!tablewidget_Device_Settings->horizontalHeaderItem(h)->text().compare(Table::Comm_Type))
            {
                combobox_CommType[v].addItem(Table::COMM_TCP, Table::COMM_TCP);
                combobox_CommType[v].addItem(Table::COMM_UDP, Table::COMM_UDP);
                combobox_CommType[v].addItem(Table::COMM_RS232,Table::COMM_RS232);
                tablewidget_Device_Settings->setCellWidget(v,h, &combobox_CommType[v]);

            }

            QTableWidgetItem *newItem = new QTableWidgetItem(QString(""));
            newItem->setTextAlignment(Qt::AlignRight);
            tablewidget_Device_Settings->setItem(v, h,newItem);
        }
    }

    LoadSettings(Table::XmlFile);
    lineEdit_Settings_file_Path->setText(Table::XmlFile);
}

void Settings::PushButton_Slot(bool checked)
{
    QString name(dynamic_cast<QPushButton*>(sender())->objectName());

    if(name == QString("..."))
    {
        QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), "", tr("Files (*.xml)"));
        lineEdit_Settings_file_Path->setText(fileName);
        LoadSettings(fileName);
    }
    else if(name == QString(STR_SAVE))
    {
        qDebug() << "Click Message Settings Save button" << checked;
        QString fileName = lineEdit_Settings_file_Path->text();

        if(fileName == QString(STR_XML_ERROR) || fileName.isEmpty())
        {
            QMessageBox msgBox(parentWidget());

            msgBox.setWindowTitle(STR_SAVE_ERROR);
            msgBox.setIcon(QMessageBox::Critical);

            QPushButton *button = msgBox.addButton(tr("Ok"), QMessageBox::ActionRole);

            msgBox.setText(QString(STR_NO_FILE_PATH));

            msgBox.exec();

            if (msgBox.clickedButton() == button) {
                // connect
            }
        }
        SaveSettings(fileName);
    }
    else if(name == QString(STR_LOAD))
    {
        qDebug() << "Click Message Setting Load button" << checked;
        QString fileName = lineEdit_Settings_file_Path->text();

        if(fileName == QString(STR_XML_ERROR) || fileName.isEmpty())
        {
            QMessageBox msgBox(parentWidget());

            msgBox.setWindowTitle(STR_LOAD_ERROR);
            msgBox.setIcon(QMessageBox::Critical);

            QPushButton *button = msgBox.addButton(tr("Ok"), QMessageBox::ActionRole);

            msgBox.setText(QString(STR_NO_FILE_PATH));

            msgBox.exec();

            if (msgBox.clickedButton() == button) {
                // connect
            }
        }
        LoadSettings(fileName);
    }
}

bool Settings::LoadSettings(const QString &xmlfile)
{
    QString xsd(":/xsd/test.xsd");

    QString xmlName(xmlfile);

    bool ret = xml_Parser.validation(xsd, xmlfile);

    if(ret == false)
    {
        lineEdit_Settings_file_Path->setText(STR_XML_ERROR);
#if defined(__DEBUG_ON__)
        qDebug() << "[" << __FILE__ << ":" << __LINE__ << "] ret[" << ret << "]";
#endif  /* __DEBUG_ON__ */
        return false;
    }

    xml_Parser.readFile(xmlfile);

    for(int v = 0; v < tablewidget_Device_Settings->verticalHeader()->count(); v++ )
    {
        QString rowName = tablewidget_Device_Settings->verticalHeaderItem(v)->text();

        if(!rowName.isNull())
        {
            for(int h = 0; h < tablewidget_Device_Settings->horizontalHeader()->count(); h++ )
            {
                QString key("Device(%1).%2");
                key = key.arg(rowName).arg(tablewidget_Device_Settings->horizontalHeaderItem(h)->text());
                QString value(xml_Parser.xmlSettings[key]);
#if defined(__DEBUG_ON__)
                qDebug() << "[" << __FILE__ << ":" << __LINE__ << "] h(" << h << "); key[" << key << "] value[" << value << "]";
#endif  /* __DEBUG_ON__ */
                tablewidget_Device_Settings->item(v, h)->setData(Qt::EditRole, value);
                if(tablewidget_Device_Settings->horizontalHeaderItem(h)->text().contains(Table::Comm_Type, Qt::CaseSensitive))
                {
                    int index = combobox_CommType[v].findData(value);

                    if ( index != -1 ) { // -1 for not found
                       combobox_CommType[v].setCurrentIndex(index);
                    }
                }
            }

        }
    }

    if(!xmlfile.contains("/")) // 제어기 맥을 가져와서 해당 xml을 다시 로딩할 때 아래의 패스도 변경한다.
    {
        lineEdit_Settings_file_Path->setText(QString("./%1").arg(xmlfile));
    }

    changed();
#if defined(__DEBUG_ON__)
    QString testKey = "Device(Slave_A).Motor(0).Tooltip";
    QString tooltip = xml_Parser.xmlSettings[testKey];
    qDebug() << "[" << __FILE__ << ":" << __LINE__ << "] testKey[" << testKey << "] tooltip[" << tooltip << "]";
#endif  /* __DEBUG_ON__ */

    return true;

}

void Settings::SaveSettings(const QString &xmlfile)
{
    for(int v = 0; v < tablewidget_Device_Settings->verticalHeader()->count(); v++ )
    {
        QString rowName = tablewidget_Device_Settings->verticalHeaderItem(v)->text();
        for(int h = 0; h < tablewidget_Device_Settings->horizontalHeader()->count(); h++ )
        {

            QVariant value;
            QString colName = tablewidget_Device_Settings->horizontalHeaderItem(h)->text();
            if(!colName.compare(Table::Comm_Type))
            {
                value = combobox_CommType[v].currentText();
            }
            else
            {
                value = tablewidget_Device_Settings->item(v, h)->data(Qt::EditRole);
            }

            if(value.isNull() && !value.isValid())
                continue;

            QString key("Device %1 %2");

            key = key.arg(rowName).arg(tablewidget_Device_Settings->horizontalHeaderItem(h)->text());

            xml_Parser.SaveXml(xmlfile, key, value.toString());
        }
    }

    xml_Parser.SaveXml(xmlfile, NULL, NULL);
    changed();
}
