#ifndef __GLOBALDEF_H__
#define __GLOBALDEF_H__

#include <QtPlugin>
#include <QString>
#include <QSize>
#include <QDebug>
#include <QObject>

#include "ui_mainwindow.h"

#if FOR_CS
#define TAILER " CS Light"
#else
#define TAILER
#endif

#define STR_TITLE "QMonitoring" TAILER

#define VERSION6
#define MAP_ALL_VALUE               0xFFFF
#define TO_RAW(t)                   #t
//Pre Define Result Value
#define OK                          0
#define FAIL                        -1
#define NO_IMPL                     ~(-1)

//Ui::MainWindow* MainWindow::ui;
#define STR_VERSION                 tr("Version: ")
#define NOTUSE                       0
#define ALL_CHANNEL                 0
#define AIN                         0
#define AOUT                        1
#define DIN                         0
#define DOUT                        1

namespace JointName
{
    enum
    {
        MASTER_WAIST = 0,
        MASTER_ELBOW = 1,
        MASTER_SHOULDER = 2,
        MASTER_LOWER = 3,
        MASTER_MIDDLE = 4,
        MASTER_UPPER = 5,
        MASTER_HANDLE = 6,

    };

    enum
    {
        CAMERA_YAW = 0,
        CAMERA_PITCH = 1,
        CAMERA_SLIDE = 2,
        CAMERA_ROLL = 3,
        CAMERA_ALL = 4
    };

    enum
    {
        SLAVE_YAW = 0,
        SLAVE_PITCH = 1,
        SLAVE_SLIDE = 2,
        SLAVE_FINGER = 3,
        SLAVE_ROLL = 4,
        SLAVE_WRIST = 5,
        SLAVE_THUMB = 6
    };
    enum
    {
        MOBILE_LEFT_WHEEL = 0,
        MOBILE_RIGHT_WHEEL,
    };
}

#define ID_OBJ_PUSHBUTTON           QString("PushButton")
#define ID_OBJ_LABEL                QString("Label")
#define ID_OBJ_PROGRESSBAR          QString("ProgressBar")
#define ID_OBJ_CHECKBOX             QString("CheckBox")
#define ID_OBJ_COMBOBOX             QString("ComboBox")
#define ID_OBJ_SPINBOX              QString("SpinBox")
#define ID_OBJ_DOUBLESPINBOX        QString("DoubleSpinBox")
#if !defined(VERSION6)
#define NET_GATHERING_PORT              QString("7779")
#else
#define NET_GATHERING_PORT              QString("7776")
#endif
#define SI_PORT              QString("7777")

#define STR_FPGA_DEBUGGING          tr("FPGA Debugging")
#define STR_SHOW_RFPG_RESISTER_MAP  tr("Show FPGA Resister Map")
#define STR_FPGA                    tr("FPGA")
#define STR_FPGA_SET                tr("Set")

#define STR_DISPLAY_ANGLE           tr("Display Angle")
#define STR_EXAMIN_PULLEY           tr("Examine Pulley")
#define STR_EXAMIN_SLIDE_ROLL       tr("Examine Slide,Roll")

#define STR_PAUSE                   tr("Pause")
#define STR_FROM                    tr("From")
#define STR_TO                      tr("To")
#define STR_HIDE                    tr("Hide")
#define STR_SHOW                    tr("Sho&w")
#define STR_PAUSE_ONE_WAY           tr("Pause One Way")
#define STR_STEOPBYSTEP             tr("Step by step")
#define STR_HOMMING                 tr("Homming")
#define STR_START                   tr("Start")
#define STR_START_EXAMINE           tr("Start_Examine")
#define STR_START_PLAYBACK          tr("Start_Playback")
#define STR_CHART                   tr("&Chart")
#define STR_MOTIONPLAYBACK          tr("Motion Playback")
#define STR_GATHERING               tr("Gathering")
#define STR_INSTRUMENT              tr("Inst")
#define STR_CAMERA_EXAMIN           tr("S/Roll")
#define STR_MESSAGE                 tr("Message")
#define STR_CONNECT                 tr("Connect")
#define STR_DISCONNECT              tr("Disconnect")
#define STR_ON                      tr("On")
#define STR_OFF                     tr("Off")
#define STR_STOP                    tr("Stop")
#define STR_SETTINGS_SAVE_ALL       tr("Save All")
#define STR_SETTINGS_LOAD_ALL       tr("Load All")
#define STR_MESSAGE_SAVE            tr("Save Message")
#define STR_LOAD_SETTINGS_FILE      tr("Load Settings File")
#define STR_LOAD_PLAYBACK_FILE      tr("Load Playback File")
#define STR_XML_VALID               tr("The Xml of settings is valid")
#define STR_XML_INVALID             tr("The Xml of settings is invalid")
#define STR_XSD_INVALID             tr("The Xml schema is invalid")
#define STR_XML_ERROR               tr("XML Error!!!")
#define STR_LOAD_MOTOR_SETTINGS     tr("Load Motor Settings")
#define STR_SAVE_MOTOR_SETTINGS     tr("Save Motor Settings")
#define STR_LOAD_IO_SETTINGS        tr("Load I/O Settings")
#define STR_SAVE_IO_SETTINGS        tr("Save I/O Settings")
#define STR_LOAD_ETC_SETTINGS        tr("Load ETC Settings")
#define STR_SAVE_ETC_SETTINGS        tr("Save ETC Settings")
#define STR_LOAD_ARM_SETTINGS       tr("Load Arm Settings")
#define STR_SAVE_ARM_SETTINGS       tr("Save Arm Settings")
#define STR_SAVE_GRIPPER_SETTINGS   tr("Save Gripper Settings")
#define STR_SAVE_PASSIVE_ABS_SETTINGS   tr("Save Passive ABS Settings")
#define STR_SAVE                    tr("Save")
#define STR_LOAD                    tr("Load")
#define STR_LOAD_ERROR              tr("File Load Error!!")
#define STR_SAVE_ERROR              tr("File Save Error!!")
#define STR_NO_FILE_PATH            tr("There is no file path")
#define STR_ALL                     tr("All")
#define STR_AMPERE                  tr("Ampere")
#define STR_PERCENTAGE              tr("Percentage")
#define STR_CURRENT_LIMIT_TEST      tr("CURRENT_LIMIT_TEST")
#define STR_VELOCITY_LIMIT_TEST     tr("VELOCITY_LIMIT_TEST")
#define STR_ACCELERATION_LIMIT_TEST tr("ACCELERATION_LIMIT_TEST")
#define STR_DECELERATION_LIMIT_TEST tr("DECELERATION_LIMIT_TEST")
#define STR_POPOUT                  tr("Pop out")
//#define STR_TITLE                   "QMonitoring"
#define STR_CONSOLE                 "Console"
#define STR_OPERATION_CART          "Operation Cart"
#define STR_VISION_CART             "Vision Cart"
#define STR_INIFINITE_RESET         "Restart Infinite"
#define STR_INSTRUMENT_COMBO        "Instrument Combo"
#define STR_HOME                    "Home"

#define HEIGHT_STATUS_BAR           30
#define HEIGHT_TAB_HEAD             30
#define WIDTH_APP                   1024
#define HEIGHT_APP                  (768-HEIGHT_STATUS_BAR-HEIGHT_TAB_HEAD)

#define NOTIFY_ON_TITLE2(target, msg)        foreach(QWidget *widget, qApp->topLevelWidgets()) {\
                                        if(widget->inherits(target))\
                                        qobject_cast<QWidget*>(widget)->setWindowTitle(QString(STR_TITLE" %1").arg(msg));\
                                    }
#define NOTIFY_ON_TITLE(msg)        foreach(QWidget *widget, qApp->topLevelWidgets()) {\
                                        if(widget->inherits("QMainWindow"))\
                                        qobject_cast<QWidget*>(widget)->setWindowTitle(QString(STR_TITLE": %1").arg(msg));\
                                    }
#define NOTIFY_CLEAR_ON_TITLE(msg)        foreach(QWidget *widget, qApp->topLevelWidgets()) {\
                                        if(widget->inherits("QMainWindow"))\
                                        qobject_cast<QWidget*>(widget)->setWindowTitle(QString(STR_TITLE));\
                                    }

namespace Table
{
    namespace ArmIndex {
        enum table_Arm_Index
        {
            SERVO = 0,
            STOP,
            MOTOR_CONTROL,
            ABS,
            ACTUAL_POSITION,
            DESIRED_POSITION,
            ACTUAL_VELOCITY,
            ACTUAL_VOLTAGE,
            DESIRED_VOLTAGE,
            ACTUAL_CURRENT,
            DESIRED_CURRENT,
            DEBUG_VALUE,
            SIZE
        };
    }
    namespace MotorIndex {
        enum table_Motor_Index
        {
            CURRENT_KP_GAIN = 0,
            CURRENT_KI_GAIN,
            CURRENT_KA_GAIN,
            CURRENT_KFF_GAIN,
            CURRENT_MAX_VOLT_GAIN,
            LQR_POS_GAIN,
            LQR_VEL_GAIN,
            LQR_CURR_GAIN,
            LQR_POS_INT_GAIN,
            LQR_MAX_VOLT_LIMIT,
            POS_PGAIN,
            POS_IGAIN,
            POS_DGAIN,
            LIMIT_TRJGAP,
            LIMIT_ACCEL,
            LIMIT_VEL,
            LIMIT_CURR,
            ERROR_DEG,
            JLIMIT_MIN,
            JLIMIT_MAX,
            STALL_RATIO,
            VELOCITY_RATIO,
            ABS_HOME,
            G_COMP,
            G_OFFSET,
            F_COMP,
            MOTOR_MADV,
            ABS_MADV,
            UNDER_CURRENT_CUR_RATIO,
            UNDER_CURRENT_VOLT_RATIO,
//            MAX_JUMP_RANGE,
//            PTP_RATIO,
//            SMOOTH_STOP_RATIO,
            STIFFNESS_CONSTANT,
            STIFFNESS_CURRENT,
            CUR_LPF_CUR,
            CUR_LPF_VEL,
            LQR_LPF_CUR,
            LQR_LPF_VEL,
            PID_LPF_CUR,
            PID_LPF_VEL,
            SIZE
        };
    }

    const int Analog_IN_Count = 13;
    const int Digital_IN_Count = 31;
    const int Digital_OUT_Count = 14;
    const int MaxAbsolute_Count = 13;
    const int DArmAbsolute_Count = 12;
    const int ABArmAbsolute_Count = 11;
    const int CArmAbsolute_Count = 8;
    const int MasterAbsolute_Count = 7;
    const int Motor_Count = 7;
    const int Bit32_Debug_Count = 7;
    const int ETC_Count = 16;
    const int LOW_SETTINGS_DEVICES = 9;
    const int COLUMN_SETTINGS_DEVICES = 4;
    const int COLUMN_IO = 33;
    const int COLUMN_ETC = 17;
    const int COLUMN_DOUTPUT = (Digital_OUT_Count + 1);
    const int COLUMN_DINPUT = (Digital_IN_Count + 1);
    const int COLUMN_AINPUT = (Analog_IN_Count + 1);
    const int COLUMN_ETCINPUT = 16;
    const int ROW_IO = 2;
    const int ROW_ETC = 6;

    const int COLUMN = 12;
    const int COLUMN_MOTOR = 38;
    const int ROW = 8;
    const int Default_Width = 80;
    const int Default_Width_IO = 44;
    const int Default_Width_MOTOR_SETTINGS = 93;
    const int Default_Height = 20;
    const int Width4Button = 27;
    const int Width4DigitalIOButton = 26;
    const int Width4Combo = 55;
    const int Width4Progress = 100;
    const QSize Column_Head_Height = QSize(10,50);

    const QString XmlFile("./QMonitoring.xml");
    ///// Arm Table
    const QString ARM_TABLE_OBJECT_NAME("ARM_TABLE");
    const QString Motor_Mapping("M-\nap");
    const QString Servo("se-\nrvo");
    const QString Stop("st-\nop");
    const QString Traject_Type("Trj");
    const QString Motor_Control("MCtl");
    const QString Actual_Current("Actual\nCurrent");
    const QString Desired_Current("Desired\nCurrent");
    const QString Actual_Postion("Actual\nPosition");
    const QString Desired_Position("Desired\nPosition");
    const QString Actual_Velocity("Actual\nVelocity");
    const QString Desired_Voltage("Desired\nVoltage");
    const QString Actual_Voltage("Actual\nVoltage");
    const QString Absolute("Abs");
    const QString Capacity("Cap");
    const QString Debug_Value("Debug\nValue");

    ///// IO Table
    const QString IO_TABLE_OBJECT_NAME("DIO_TABLE");
    const QString ETC_TABLE_OBJECT_NAME("ETC_TABLE");
    const QString ETC_Mapping("Etc Map");
    const QString ABS_Mapping("Abs Map");
    const QString AIn_Mapping("AIn Map");
    const QString Digital_IN("DIn");
    const QString Digital_OUT("DOut");
    const QString Analog_IN("AIn");
    const QString Analog_OUT("AOut");
    const QString ETC("Etc");
    const QString RFID_DRAPE_PLATE("RFID Drape Plate");
    const QString RFID_READ_INSTRUMENT("Read Instrument Tag");
    const QString RFID_WRITE_INSTRUMENT("Write Tag");
    const QString INSTRUMENT_INVENTORY_VIEWER("Inst Inventory");
    const QString SET_STAGE("Inf Stage");
    const QString STANDBY_STAGE("Standby");
    const QString ACTIVE_STAGE("Active");
    const QString INIT_STAGE("Init..");
    const QString CURRENT_BIAS("Motor Current Bias");
    const QString GET_BIAS("Get Bias");
    const QString SET_BIAS("Set Bias");

    ///// Motor Settings Table
    const QString MOTOR_TABLE_OBJECT_NAME("MOTOR_TABLE");
    const QString CURRENT_KP_GAIN("Cur\nKp");
    const QString CURRENT_KI_GAIN("Cur\nKi");
    const QString CURRENT_KA_GAIN("Cur\nKa");
    const QString CURRENT_KFF_GAIN("Cur\nKff");
    const QString CURRENT_MAX_VOLT_GAIN("Cur\nMaxVolt");

    const QString LQR_POS_GAIN("LQR\nPos");
    const QString LQR_VEL_GAIN("LQR\nVel");
    const QString LQR_CURR_GAIN("LQR\nCur");
    const QString LQR_POS_INT_GAIN("LQR\nPosInt");
    const QString LQR_MAX_VOLT_GAIN("LQR\nMaxVolt");

    const QString POS_P_GAIN("Pos\nPGain");
    const QString POS_I_GAIN("Pos\nIGain");
    const QString POS_D_GAIN("Pos\nDGain");

    const QString VEL_P_GAIN("Vel\nPGain");
    const QString VEL_I_GAIN("Vel\nIGain");

    const QString LIMIT_ACCEL("Limit\nAccel");
    const QString LIMIT_VEL("Limit\nVel");
    const QString LIMIT_CURR("Limit\nCur");
    const QString LIMIT_TRJGAP("Limit\nTrjGap");

    const QString ABSOLUTE_HOME("Abs\nHome");
    const QString MOTOR_MADV("Motor\nMadv");
    const QString ABSOLUTE_MADV("Abs\nMadv");
    const QString ERROR_DEG("Error\nDeg");
    const QString JLIMIT_MIN("JLimit\nMin");
    const QString JLIMIT_MAX("JLimit\nMax");
    const QString STALL_RATIO("Stall\nRatio");
    const QString VELOCITY_RATIO("Velocity\nRatio");
    const QString G_COMP("G\nComp");
    const QString G_OFFSET("G\nOffset");
    const QString F_COMP("F\nComp");
    const QString UNDERCURRENT_VOLTRATIO("UnderCurrent\nVoltRatio");
    const QString UNDERCURRENT_CURRATIO("UnderCurrent\nCurRatio");
    const QString MAXJUMP_RANGE("MaxJump\nRange");
    const QString PTP_RATIO("PTP\nRatio");
    const QString SMOOTHSTOP_RATIO("SmoothStop\nRatio");
    const QString STIFFNESS_CONSTANT("Stiffness\nConstant");
    const QString STIFFNESS_CURRENT("Stiffness\nCurrent");
    const QString CUR_LPF_CUR("CUR_LPF\nCur");
    const QString CUR_LPF_VEL("CUR_LPF\nVel");
    const QString LQR_LPF_CUR("LQR_LPF\nCur");
    const QString LQR_LPF_VEL("LQR_LPF\nVel");
    const QString PID_LPF_CUR("PID_LPF\nCur");
    const QString PID_LPF_VEL("PID_LPF\nVel");

    ///// Table in Settings
    const QString SETTINGS_TABLE_OBJECT_NAME("SETTINGS_TABLE");
    const QString IP("IP");
    const QString Port("Port");
    const QString Refresh_Time("RefreshTime");
    const QString Comm_Type("CommType");
    const QString Master_L("Master_L");
    const QString Master_R("Master_R");
    const QString Slave_A("Slave_A");
    const QString Slave_B("Slave_B");
    const QString Slave_C("Slave_C");
    const QString Slave_D("Slave_D");
    const QString Console("Console");
    const QString Vision("Vision");
    const QString Mobile("Mobile");
    const QString HOST_PC("Host PC");
    const QString Setup_PC("Setup PC");
    const QString VISION_PC("Vision PC");
    const QString Operation("Operation");
    const QString COMM_TCP("TCP");
    const QString COMM_UDP("UDP");
    const QString COMM_RS232("RS232");
    const QString COMM_SERIAL("Serial");

    //Test for Instrument table
    const QString INSTRUMENT_TABLE_OBJECT_NAME("INSTRUMET_TABLE");
    const QString INSTRUMENT_TABLE_FOR_PLAYBACK_OBJECT_NAME("INSTRUMET_TABLE_FOR_PLAYBACK");
    const QString INSTRUMENT_TABLE_FOR_EXAMINE_PULLEY_NAME("INSTRUMENT_TABLE_FOR_EXAMINE_PULLEY");
    const QString INST_ABS("ABS Angle");
    const QString INST_Diff_ABS_ACTUAL("ABS-Actual");
    const QString INST_Actual("Actual Angle");
    const QString INST_Diff_Actual_Desired("Act-Des");
    const QString INST_Desired("Desired Angle");
    const QString INST_MIN("MIN");
    const QString INST_MAX("MAX");

    //Examine for the slide and the roll of Camera
    const QString CAMERA_TABLE_FOR_EXAMINE_NAME("CAMERA_TABLE_FOR_EXAMINE");

    const QString PLAYBACK_SELECT("Select");
    const QString PLAYBACK_IP("IP");
    const QString PLAYBACK_CONNECT("Connect");
    const QString PLAYBACK_ERROR("Error");
    const QString PLAYBACK_SERVO("Servo");
    const QString PLAYBACK_HOMING("Homing");
    const QString PLAYBACK_PLAY("Play/Pause");
    const QString PLAYBACK_STOP("Stop");
    const QString PLAYBACK_LOOP("Loop");
    const QString PLAYBACK_TOTAL("Count/Total");
    const QString PLAYBACK_FROM("From");
    const QString PLAYBACK_TO("To");
    const QString PLAYBACK_RUN_TYPE("Running Type");
    const QString PLAYBACK_RUNNING_TIME("Running Time");
    const QString PLAYBACK_CURRENT_INDEX("Index");
    const QString PLAYBACK_TRIP_MODE("Trip");
    const QString PLAYBACK_MS("ms");

    const QString A_B_REPEAT_SELECT("Select");
    const QString A_B_REPEAT_APOS("A Pos");
    const QString A_B_REPEAT_BPOS("B Pos");
    const QString A_B_REPEAT_ABGAP("A-B Gap");
    const QString A_B_REPEAT_TIME_INTERVAL("Interval");
    const QString A_B_REPEAT_MOVE_A("Move A");
    const QString A_B_REPEAT_MOVE_B("Move B");
    const QString A_B_REPEAT_LOOP("Loop");
    const QString A_B_REPEAT_PLAY("Play");
    const QString A_B_REPEAT_COUNT("Counts");

    namespace Trajectory_Type {
        const QString PAV("PAV");
        const QString PTP("PTP");
    };

    namespace Control_Mode {
        const QString STEP("Step");
        const QString CUR("Cur");
        const QString LQR("LQR");
        const QString PID("PID");
        const QString LQRPP("PosPP");
        const QString CURLQRPP("Cur/LQR PP");
    };
}

#endif // __GLOBALDEF_H__
