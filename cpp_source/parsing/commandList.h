#ifndef __COMMAND_LIST_H__
#define __COMMAND_LIST_H__

#define     COMMEND_CODE(REQ_TYPE, RES_TYPE, CODE)              ((REQ_TYPE << 20) + (RES_TYPE << 16)    + CODE)
#define     GET_COMMEND_CODE(RES_TYPE, CODE)                    (                   (RES_TYPE << 16)    + (CODE & 0xFFFE))
#define     SET_COMMEND_CODE(REQ_TYPE, CODE)                    ((REQ_TYPE << 20)                       + (CODE | 0x0001))

#define     ERROR_CODE(ERROR_LEVEL, CODE)                       ((ERROR_LEVEL << 28) + CODE)

typedef enum _InfDataType_ {
    NONE_TYPE = 0,
    INT32_TYPE = 1,
    UINT32_TYPE,
    GRIPPER_TYPE,
    UINT16_TYPE,
    FLOAT_TYPE,
    CHAR_TYPE,
    MOTOR_TYPE,
    ARM_TYPE,
    GATHERING_TYPE,
    SYSTEM_INFO_TYPE,
    MOTION_PLAYBACK_TYPE,
    INT32_TYPE_ARRAY,
    FLOAT_TYPE_ARRAY,
    CHAR_TYPE_ARRAY,
    ERROR_TYPE_ARRAY,
} _InfDataType;

typedef enum _EventErrorLevel_ {
    InfOk                           = 0x0,    //No Error
    InfNotify                       = 0x1,   // Notify any problems.
    InfWarning                      = 0x3,   // No Servo off, just notice.
    InfError                        = 0x5,   // Servo Off
    InfCritical                     = 0x7,   // Servo Off and need to reboot.
}_EventErrorLevel;

typedef  enum {
    RESET_SYSTEM =                          COMMEND_CODE(NONE_TYPE,             NONE_TYPE,      0x0001),
    GET_DEVICE_INFORMATION =                GET_COMMEND_CODE(SYSTEM_INFO_TYPE,  0x1010),
    SET_NETWORK_TIMEOUT =                   SET_COMMEND_CODE(UINT32_TYPE,       0x1021),

    GET_CALIBRATION_BIAS =                  GET_COMMEND_CODE(UINT32_TYPE,       0x2010),
    SET_CALIBRATION_BIAS =                  SET_COMMEND_CODE(NONE_TYPE,         0x2011),

    GET_MOTOR_TYPE =                        GET_COMMEND_CODE(UINT32_TYPE,       0x2050),
    SET_MOTOR_TYPE =                        SET_COMMEND_CODE(UINT32_TYPE,       0x2051),

    GET_MOTOR_STATUS =                      GET_COMMEND_CODE(UINT32_TYPE,       0x2060),

    GET_SERVO_STATUS =                      GET_COMMEND_CODE(UINT32_TYPE,       0x2070),
    SET_SERVO_STATUS =                      SET_COMMEND_CODE(UINT32_TYPE,       0x2071),
    GET_CONTROL_MODE =                      GET_COMMEND_CODE(UINT32_TYPE,       0x2090),
    SET_CONTROL_MODE =                      SET_COMMEND_CODE(UINT32_TYPE,       0x2091),

    SET_SAVE_DATALOG =                      SET_COMMEND_CODE(UINT32_TYPE,       0x20B1),
    GET_SAVE_DATALOG =                      GET_COMMEND_CODE(CHAR_TYPE_ARRAY,   0x20B0),

    GET_MOTOR_DATA =                        GET_COMMEND_CODE(MOTOR_TYPE,        0x2100),
//            GET_JOINT_DATA =                        GET_COMMEND_CODE(JOINT_TYPE,        0x2200),
    GET_ARM_DATA =                          GET_COMMEND_CODE(ARM_TYPE,          0x2300),

    GET_DESIRED_CURRENT =                   GET_COMMEND_CODE(FLOAT_TYPE,        0x3020),
    SET_DESIRED_CURRENT =                   SET_COMMEND_CODE(FLOAT_TYPE,        0x3021),
    GET_ACTUAL_CURRENT =                    GET_COMMEND_CODE(FLOAT_TYPE,        0x3030),
    GET_TOTAL_DESIRED_CURRENT =             GET_COMMEND_CODE(FLOAT_TYPE,        0x3040),

    GET_DESIRED_VELOCITY =                  GET_COMMEND_CODE(FLOAT_TYPE,        0x4060),
    SET_DESIRED_VELOCITY =                  SET_COMMEND_CODE(FLOAT_TYPE,        0x4061),
    GET_ACTUAL_VELOCITY =                   GET_COMMEND_CODE(FLOAT_TYPE,        0x4070),

    GET_DESIRED_VOLTAGE =                   GET_COMMEND_CODE(FLOAT_TYPE,        0x4080),
    SET_DESIRED_VOLTAGE =                   SET_COMMEND_CODE(FLOAT_TYPE,        0x4081),
    GET_ACTUAL_VOLTAGE =                    GET_COMMEND_CODE(FLOAT_TYPE,        0x4090),

    GET_DESIRED_POSITION =                  GET_COMMEND_CODE(INT32_TYPE,        0x5020),
    SET_DESIRED_POSITION =                  SET_COMMEND_CODE(INT32_TYPE,        0x5021),
    GET_MOTOR_ENCODER =                     GET_COMMEND_CODE(INT32_TYPE,        0x5030),
    SET_MOTOR_ENCODER =                     SET_COMMEND_CODE(INT32_TYPE,        0x5031),
    GET_TRAJECTORY_POSITION =               GET_COMMEND_CODE(FLOAT_TYPE,        0x5040),
    GET_CONSOLEBASE_POSITION =              GET_COMMEND_CODE(UINT32_TYPE,       0x5050),
    SET_CONSOLEBASE_POSITION =              SET_COMMEND_CODE(UINT32_TYPE,       0x5051),

    GET_DIGITAL_INPUT =                     GET_COMMEND_CODE(UINT32_TYPE,       0xA020),
    GET_DIGITAL_OUTPUT =                    GET_COMMEND_CODE(UINT32_TYPE,       0xA420),
    SET_DIGITAL_OUTPUT =                    SET_COMMEND_CODE(UINT32_TYPE,       0xA421),

    // Ch,Interval 1ms unit
    GET_LED_FLICKER =                       GET_COMMEND_CODE(UINT32_TYPE,       0xA430),
    SET_LED_FLICKER =                       SET_COMMEND_CODE(UINT32_TYPE,       0xA431),

    GET_GRIPPER_PARAM    =                  GET_COMMEND_CODE(GRIPPER_TYPE,      0xA440),
    SET_GRIPPER_PARAM    =                  SET_COMMEND_CODE(GRIPPER_TYPE,      0xA441),

    GET_ABSOLUTE_ENCODER =                  GET_COMMEND_CODE(UINT32_TYPE,       0xA820),

    GET_ANALOG_INPUT =                      GET_COMMEND_CODE(UINT32_TYPE,       0xAC20),

    GET_TEMPERATURE =                       GET_COMMEND_CODE(FLOAT_TYPE,        0xAF40),

    GET_MAIN_FPGA_REGISTER =                GET_COMMEND_CODE(UINT32_TYPE,       0xAFA0),
    SET_MAIN_FPGA_REGISTER =                SET_COMMEND_CODE(UINT32_TYPE,       0xAFA1),
    GET_SUB_FPGA_REGISTER =                 GET_COMMEND_CODE(UINT32_TYPE,       0xAFB0),
    SET_SUB_FPGA_REGISTER =                 SET_COMMEND_CODE(UINT32_TYPE,       0xAFB1),

    //Mobile
    GET_MOBILE_BATTERY_LEVEL =              GET_COMMEND_CODE(UINT32_TYPE,       0xB000),
    GET_MOBILE_BATTERY_STATUS =             GET_COMMEND_CODE(UINT32_TYPE,       0xB010),

    //console,mobile Lock
    GET_LOCK =                              GET_COMMEND_CODE(UINT32_TYPE,       0xB020),
    SET_LOCK =                              SET_COMMEND_CODE(UINT32_TYPE,       0xB021),
                                                                                                        
    // console infinite power state check
    GET_STAGE =                             GET_COMMEND_CODE(UINT32_TYPE,       0xC000),
    SET_STAGE =                             SET_COMMEND_CODE(UINT32_TYPE,       0xC001),

    // Get Infinite Power switch status
    GET_INFINITE_POWER_BUTTON     =         GET_COMMEND_CODE(UINT32_TYPE,       0xC010),

    GET_CURRENT_KP_GAIN =                   GET_COMMEND_CODE(FLOAT_TYPE,        0xD010),
    SET_CURRENT_KP_GAIN =                   SET_COMMEND_CODE(FLOAT_TYPE,        0xD011),
    GET_CURRENT_KI_GAIN =                   GET_COMMEND_CODE(FLOAT_TYPE,        0xD020),
    SET_CURRENT_KI_GAIN =                   SET_COMMEND_CODE(FLOAT_TYPE,        0xD021),
    GET_CURRENT_KA_GAIN =                   GET_COMMEND_CODE(FLOAT_TYPE,        0xD030),
    SET_CURRENT_KA_GAIN =                   SET_COMMEND_CODE(FLOAT_TYPE,        0xD031),
    GET_CURRENT_KFF_GAIN =                  GET_COMMEND_CODE(FLOAT_TYPE,        0xD040),
    SET_CURRENT_KFF_GAIN =                  SET_COMMEND_CODE(FLOAT_TYPE,        0xD041),

    GET_LQR_VELOCITY_GAIN =                 GET_COMMEND_CODE(FLOAT_TYPE,        0xD060),
    SET_LQR_VELOCITY_GAIN =                 SET_COMMEND_CODE(FLOAT_TYPE,        0xD061),
    GET_LQR_POSITION_GAIN =                 GET_COMMEND_CODE(FLOAT_TYPE,        0xD070),
    SET_LQR_POSITION_GAIN =                 SET_COMMEND_CODE(FLOAT_TYPE,        0xD071),
    GET_LQR_CURRENT_GAIN =                  GET_COMMEND_CODE(FLOAT_TYPE,        0xD080),
    SET_LQR_CURRENT_GAIN =                  SET_COMMEND_CODE(FLOAT_TYPE,        0xD081),
    GET_LQR_POS_INT_GAIN =                  GET_COMMEND_CODE(FLOAT_TYPE,        0xD090),
    SET_LQR_POS_INT_GAIN =                  SET_COMMEND_CODE(FLOAT_TYPE,        0xD091),

    GET_POS_P_GAIN =                        GET_COMMEND_CODE(FLOAT_TYPE,        0xD300),
    SET_POS_P_GAIN =                        SET_COMMEND_CODE(FLOAT_TYPE,        0xD301),
    GET_POS_I_GAIN =                        GET_COMMEND_CODE(FLOAT_TYPE,        0xD310),
    SET_POS_I_GAIN =                        SET_COMMEND_CODE(FLOAT_TYPE,        0xD311),
    GET_POS_D_GAIN =                        GET_COMMEND_CODE(FLOAT_TYPE,        0xD320),
    SET_POS_D_GAIN =                        SET_COMMEND_CODE(FLOAT_TYPE,        0xD321),

    GET_VEL_P_GAIN =                        GET_COMMEND_CODE(FLOAT_TYPE,        0xD330),
    SET_VEL_P_GAIN =                        SET_COMMEND_CODE(FLOAT_TYPE,        0xD331),
    GET_VEL_I_GAIN =                        GET_COMMEND_CODE(FLOAT_TYPE,        0xD340),
    SET_VEL_I_GAIN =                        SET_COMMEND_CODE(FLOAT_TYPE,        0xD341),

    GET_ACCELERATION_LIMIT =                GET_COMMEND_CODE(FLOAT_TYPE,        0xD0A0),
    SET_ACCELERATION_LIMIT =                SET_COMMEND_CODE(FLOAT_TYPE,        0xD0A1),
    GET_VELOCITY_LIMIT =                    GET_COMMEND_CODE(FLOAT_TYPE,        0xD0B0),
    SET_VELOCITY_LIMIT =                    SET_COMMEND_CODE(FLOAT_TYPE,        0xD0B1),
    GET_CURRENT_LIMIT =                     GET_COMMEND_CODE(FLOAT_TYPE,        0xD0C0),
    SET_CURRENT_LIMIT =                     SET_COMMEND_CODE(FLOAT_TYPE,        0xD0C1),
    GET_CURRENT_MAX_VOLT_LIMIT =            GET_COMMEND_CODE(FLOAT_TYPE,        0xD0D0),
    SET_CURRENT_MAX_VOLT_LIMIT =            SET_COMMEND_CODE(FLOAT_TYPE,        0xD0D1),
    GET_LQR_MAX_VOLT_LIMIT =                GET_COMMEND_CODE(FLOAT_TYPE,        0xD0E0),
    SET_LQR_MAX_VOLT_LIMIT =                SET_COMMEND_CODE(FLOAT_TYPE,        0xD0E1),
    GET_TRAJECTORY_GAP_LIMIT =              GET_COMMEND_CODE(FLOAT_TYPE,        0xD0F0),
    SET_TRAJECTORY_GAP_LIMIT =              SET_COMMEND_CODE(FLOAT_TYPE,        0xD0F1),

    GET_ABSOLUTE_ZERO_COUNT =               GET_COMMEND_CODE(FLOAT_TYPE,        0xD100),
    SET_ABSOLUTE_ZERO_COUNT =               SET_COMMEND_CODE(FLOAT_TYPE,        0xD101),

    GET_ABSOLUTE_MADV =                     GET_COMMEND_CODE(FLOAT_TYPE,        0xD110),
    SET_ABSOLUTE_MADV =                     SET_COMMEND_CODE(FLOAT_TYPE,        0xD111),

    GET_MOTOR_MADV =                        GET_COMMEND_CODE(FLOAT_TYPE,        0xD120),
    SET_MOTOR_MADV =                        SET_COMMEND_CODE(FLOAT_TYPE,        0xD121),

    GET_ENCODER_DIFF_ERROR_LIMIT =          GET_COMMEND_CODE(FLOAT_TYPE,        0xD130),
    SET_ENCODER_DIFF_ERROR_LIMIT =          SET_COMMEND_CODE(FLOAT_TYPE,        0xD131),

    GET_STALL_DETECTION_RATIO =             GET_COMMEND_CODE(FLOAT_TYPE,        0xD140),
    SET_STALL_DETECTION_RATIO =             SET_COMMEND_CODE(FLOAT_TYPE,        0xD141),

    GET_OVER_CURRENT_RATIO =                GET_COMMEND_CODE(FLOAT_TYPE,        0xD1E0),
    SET_OVER_CURRENT_RATIO =                SET_COMMEND_CODE(FLOAT_TYPE,        0xD1E1),

    GET_JOINT_LIMIT_MIN =                   GET_COMMEND_CODE(FLOAT_TYPE,        0xD150),
    SET_JOINT_LIMIT_MIN =                   SET_COMMEND_CODE(FLOAT_TYPE,        0xD151),

    GET_JOINT_LIMIT_MAX =                   GET_COMMEND_CODE(FLOAT_TYPE,        0xD160),
    SET_JOINT_LIMIT_MAX =                   SET_COMMEND_CODE(FLOAT_TYPE,        0xD161),

    GET_OVER_VELOCITY_RATIO =               GET_COMMEND_CODE(FLOAT_TYPE,        0xD170),
    SET_OVER_VELOCITY_RATIO =               SET_COMMEND_CODE(FLOAT_TYPE,        0xD171),

    GET_UNDER_CURRENT_VOLT_RATIO =          GET_COMMEND_CODE(FLOAT_TYPE,        0xD180),
    SET_UNDER_CURRENT_VOLT_RATIO =          SET_COMMEND_CODE(FLOAT_TYPE,        0xD181),

    GET_UNDER_CURRENT_CUR_RATIO =           GET_COMMEND_CODE(FLOAT_TYPE,        0xD190),
    SET_UNDER_CURRENT_CUR_RATIO =           SET_COMMEND_CODE(FLOAT_TYPE,        0xD191),

    GET_MAX_JUMP_RANGE =                    GET_COMMEND_CODE(FLOAT_TYPE,        0xD1A0),
    SET_MAX_JUMP_RANGE =                    SET_COMMEND_CODE(FLOAT_TYPE,        0xD1A1),

    GET_CURRENT_GAP_RATIO =                 GET_COMMEND_CODE(FLOAT_TYPE,        0xD1F0),
    SET_CURRENT_GAP_RATIO =                 SET_COMMEND_CODE(FLOAT_TYPE,        0xD1F1),

    GET_VEL_LPF_TAU =                       GET_COMMEND_CODE(FLOAT_TYPE,        0xD1DC),
    SET_VEL_LPF_TAU =                       SET_COMMEND_CODE(FLOAT_TYPE,        0xD1DD),
                
    /////////////////// Old LPF Param ////////////////////            
    GET_PID_LPF_CURRENT =                   GET_COMMEND_CODE(FLOAT_TYPE,        0xD1D0),
    SET_PID_LPF_CURRENT =                   SET_COMMEND_CODE(FLOAT_TYPE,        0xD1D1),
    GET_LQR_LPF_CURRENT =                   GET_COMMEND_CODE(FLOAT_TYPE,        0xD1D2),
    SET_LQR_LPF_CURRENT =                   SET_COMMEND_CODE(FLOAT_TYPE,        0xD1D3),
    GET_CUR_LPF_CURRENT =                   GET_COMMEND_CODE(FLOAT_TYPE,        0xD1D4),
    SET_CUR_LPF_CURRENT =                   SET_COMMEND_CODE(FLOAT_TYPE,        0xD1D5),
    GET_PID_LPF_VELOCITY =                  GET_COMMEND_CODE(FLOAT_TYPE,        0xD1D6),
    SET_PID_LPF_VELOCITY =                  SET_COMMEND_CODE(FLOAT_TYPE,        0xD1D7),
    GET_LQR_LPF_VELOCITY =                  GET_COMMEND_CODE(FLOAT_TYPE,        0xD1D8),
    SET_LQR_LPF_VELOCITY =                  SET_COMMEND_CODE(FLOAT_TYPE,        0xD1D9),
    GET_CUR_LPF_VELOCITY =                  GET_COMMEND_CODE(FLOAT_TYPE,        0xD1DA),
    SET_CUR_LPF_VELOCITY =                  SET_COMMEND_CODE(FLOAT_TYPE,        0xD1DB),


    ////////// Stiffness ///////////////////////////
    GET_STIFFNESS_CONSTANT =                GET_COMMEND_CODE(FLOAT_TYPE,        0xD230),
    SET_STIFFNESS_CONSTANT =                SET_COMMEND_CODE(FLOAT_TYPE,        0xD231),
    GET_STIFFNESS_CURRENT =                 GET_COMMEND_CODE(FLOAT_TYPE,        0xD240),
    SET_STIFFNESS_CURRENT =                 SET_COMMEND_CODE(FLOAT_TYPE,        0xD241),
    ///////////Damping////////////////////////////
    GET_DAMPING_VELOCITY =                  GET_COMMEND_CODE(FLOAT_TYPE,        0xD1F2),
    SET_DAMPING_VELOCITY =                  SET_COMMEND_CODE(FLOAT_TYPE,        0xD1F3),
    GET_DAMPING_CONSTANT =                  GET_COMMEND_CODE(FLOAT_TYPE,        0xD1F4),
    SET_DAMPING_CONSTANT =                  SET_COMMEND_CODE(FLOAT_TYPE,        0xD1F5),

    GET_FRICTION_THRESHOLD =                GET_COMMEND_CODE(FLOAT_TYPE,        0xD1F6),
    SET_FRICTION_THRESHOLD =                SET_COMMEND_CODE(FLOAT_TYPE,        0xD1F7),
    GET_FRICTION_COMPENSATION_GAIN =        GET_COMMEND_CODE(FLOAT_TYPE,        0xD220),
    SET_FRICTION_COMPENSATION_GAIN =        SET_COMMEND_CODE(FLOAT_TYPE,        0xD221),
    GET_FRICTION_COULOMB =                  GET_COMMEND_CODE(FLOAT_TYPE,        0xD1F8),
    SET_FRICTION_COULOMB =                  SET_COMMEND_CODE(FLOAT_TYPE,        0xD1F9),
    GET_FRICTION_VISCOUS =                  GET_COMMEND_CODE(FLOAT_TYPE,        0xD1FA),
    SET_FRICTION_VISCOUS =                  SET_COMMEND_CODE(FLOAT_TYPE,        0xD1FB),
    GET_FRICTION_EFFICINCY =                GET_COMMEND_CODE(FLOAT_TYPE,        0xD1FC),
    SET_FRICTION_EFFICINCY =                SET_COMMEND_CODE(FLOAT_TYPE,        0xD1FD),
    

        /////////////중력보상///////////////////////////
    GET_GRAVITY_COMPENSATION_GAIN =         GET_COMMEND_CODE(FLOAT_TYPE,        0xD200),
    SET_GRAVITY_COMPENSATION_GAIN =         SET_COMMEND_CODE(FLOAT_TYPE,        0xD201),
    GET_GRAVITY_COMPENSATION_OFFSET =       GET_COMMEND_CODE(FLOAT_TYPE,        0xD210),
    SET_GRAVITY_COMPENSATION_OFFSET =       SET_COMMEND_CODE(FLOAT_TYPE,        0xD211),
    GET_SPRING_INTERCEPT =                  GET_COMMEND_CODE(FLOAT_TYPE,        0xD244),
    SET_SPRING_INTERCEPT =                  SET_COMMEND_CODE(FLOAT_TYPE,        0xD245),
    GET_SPRING_SLOPE =                      GET_COMMEND_CODE(FLOAT_TYPE,        0xD242),
    SET_SPRING_SLOPE =                      SET_COMMEND_CODE(FLOAT_TYPE,        0xD243),

    ////////// Stiffness Sonund Control//////////
    SET_STIFFNESS_SOUND_ONFF =              SET_COMMEND_CODE(UINT32_TYPE,       0xD251),
    ////////////////////////////////////////////////

        // Get RFID Tag infomation
    GET_INFINITE_RFID =                     COMMEND_CODE(NONE_TYPE,             CHAR_TYPE_ARRAY,    0xE0D0),// TODO:
    SET_INFINITE_RFID =                     COMMEND_CODE(CHAR_TYPE_ARRAY,       CHAR_TYPE_ARRAY,    0xE0D1),// TODO:

    // Add RFID Kind
//            SET_INFINITE_RFID_KIND =                     SET_COMMEND_CODE(UINT32_TYPE,      0xE0D3),

    GET_GATHERING_INFO =                    GET_COMMEND_CODE(GATHERING_TYPE,    0x1020),
    SET_GATHERING_INFO =                    SET_COMMEND_CODE(GATHERING_TYPE,    0x1021),
    GATHERING_DATA =                        COMMEND_CODE(UINT32_TYPE,           GATHERING_TYPE,     0x1050),
    START_GATHERING =                       COMMEND_CODE(NONE_TYPE,             NONE_TYPE,          0x1031),
    STOP_GATHERING =                        COMMEND_CODE(NONE_TYPE,             NONE_TYPE,          0x1041),
    START_DATA_PORT =                       COMMEND_CODE(UINT32_TYPE,           NONE_TYPE,          0x1051),
    START_EVENT_PORT =                      COMMEND_CODE(NONE_TYPE,             NONE_TYPE,          0x1061),
    /// For Debugging
    GET_DEBUG_FLOAT_VALUE =                 GET_COMMEND_CODE(FLOAT_TYPE,        0xF000),
    SET_DEBUG_FLOAT_VALUE =                 SET_COMMEND_CODE(FLOAT_TYPE,        0xF001),
    GET_DEBUG_INT32_VALUE =                 GET_COMMEND_CODE(INT32_TYPE,        0xF010),
    SET_DEBUG_INT32_VALUE =                 SET_COMMEND_CODE(INT32_TYPE,        0xF011),
    GET_DEBUG_UINT32_VALUE =                GET_COMMEND_CODE(UINT32_TYPE,       0xF020),
    SET_DEBUG_UINT32_VALUE =                SET_COMMEND_CODE(UINT32_TYPE,       0xF021),

        //////////////////////////////////////// Motion Playback //////////////////////////////////////////////////
    GET_MOTION_PLAYBACK_STATUS =            GET_COMMEND_CODE(MOTION_PLAYBACK_TYPE,0xF0A0),  //  Get Play Status/Loop Count/Servo/Trip/Enable/From/To
    SET_MOTION_PLAYBACK_PLAY =              SET_COMMEND_CODE(INT32_TYPE,        0xF0A1),    // Set Stop/Homing/Pause/Play
    SET_MOTION_PLAYBACK_SETUP =             SET_COMMEND_CODE(UINT32_TYPE,       0xF0A3),    // Set Trip(One way/Round Trip)/Command Cycle Time(1ms~10ms)/Loop Count(Current/Total)/Loop Range(From/TO)/Enable
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    GET_FAULT_COUNT =                       GET_COMMEND_CODE(UINT32_TYPE,       0xF0CE),
    SET_FAULT_COUNT =                       SET_COMMEND_CODE(UINT32_TYPE,       0xF0CF),
    // Network alive notification for Energy Device
    // TODO:
    SET_VISION_NETWORK_ALIVE    =           SET_COMMEND_CODE(UINT32_TYPE,       0xF0B1),
    GET_MOBILE_NETWORK_ALIVE    =           GET_COMMEND_CODE(UINT32_TYPE,       0xF0C0),
    GET_NETWORK_ALIVE           =           GET_COMMEND_CODE(UINT32_TYPE,       0xF0C2),
    GET_NETWORK_TIMEOUT_LIMIT   =           GET_COMMEND_CODE(UINT32_TYPE,       0xF0C4),
    SET_NETWORK_TIMEOUT_LIMIT   =           SET_COMMEND_CODE(UINT32_TYPE,       0xF0C5),

    // Unused code
    GET_TRAJECTORY_GENERATION_MODE =        GET_COMMEND_CODE(UINT32_TYPE,       0x20A0),
    SET_TRAJECTORY_GENERATION_MODE =        SET_COMMEND_CODE(UINT32_TYPE,       0x20A1),
    SET_MOTION_STOP =                       SET_COMMEND_CODE(UINT32_TYPE,       0x2081),
    GET_PTP_RATIO =                         GET_COMMEND_CODE(FLOAT_TYPE,        0xD1B0),
    SET_PTP_RATIO =                         SET_COMMEND_CODE(FLOAT_TYPE,        0xD1B1),
    GET_SMOOTH_STOP_RATIO =                 GET_COMMEND_CODE(FLOAT_TYPE,        0xD1C0),
    SET_SMOOTH_STOP_RATIO =                 SET_COMMEND_CODE(FLOAT_TYPE,        0xD1C1),
    GET_POWER_BITWISE =                     GET_COMMEND_CODE(UINT32_TYPE,       0xAF10),
    SET_POWER_VALUE =                       SET_COMMEND_CODE(UINT32_TYPE,       0xAF11),
    GET_INCREMENTAL_ENCODER =               GET_COMMEND_CODE(INT32_TYPE,        0xAE20),
    SET_INCREMENTAL_ENCODER =               SET_COMMEND_CODE(INT32_TYPE,        0xAE21),
//            SET_ENERGY_MONOPOLAR_CUT =              SET_COMMEND_CODE(UINT32_TYPE,       0xB031),
//            SET_ENERGY_MONOPOLAR_COAG =             SET_COMMEND_CODE(UINT32_TYPE,       0xB041),
//            SET_ENERGY_BIPOLAR =                    SET_COMMEND_CODE(UINT32_TYPE,       0xB051),
//            SET_ENERGY_PK =                         SET_COMMEND_CODE(UINT32_TYPE,       0xB061),
//            SET_ENERGY_HARMONIC_MIN =               SET_COMMEND_CODE(UINT32_TYPE,       0xB071),
//            SET_ENERGY_HARMONIC_MAX =               SET_COMMEND_CODE(UINT32_TYPE,       0xB081),

                
    //Controller Event Error
    ERR_MOTION_CONTROLLER =                 ERROR_CODE(InfNotify,  COMMEND_CODE(ERROR_TYPE_ARRAY, ERROR_TYPE_ARRAY, 0x0B000000)), // TODO: check Code Range

    //Code with 0x1x is Warnning Level
    WRN_ALREADY_SETTING     =               ERROR_CODE(InfWarning, 0x01000000),
    WRN_ALREADY_RUNNING     =               ERROR_CODE(InfWarning, 0x02000000),

    // ERROR RESPONSE
    ERR_UNSUPPORTED_CODE =                  ERROR_CODE(InfError,   0X01000000),
    ERR_INVALID_PACKET =                    ERROR_CODE(InfError,   0X02000000),
    ERR_UNKNOWN =                           ERROR_CODE(InfError,   0X03000000),
    ERR_UKNOWN_CODE =                       ERROR_CODE(InfError,   0X04000000),
    ERR_INVALID_DATA =                      ERROR_CODE(InfError,   0X05000000),
    ERR_INVALID_MOTOR_DATA =                ERROR_CODE(InfError,   0X06000000),
    ERR_NOT_AVAILABLE_CHANNEL =             ERROR_CODE(InfError,   0X07000000),
    // Parameter 값이 유효하지 않을때 사용.
    ERR_UNSUPPORTED_PARAM =                 ERROR_CODE(InfError,   0X08000000),
    ERR_DEVICE_COMMUNICATION =              ERROR_CODE(InfError,   0X09000000),
    ERR_INFINITE_SYSTEM =                   ERROR_CODE(InfError,   0X0A000000),
    //Standby stage일때 특정명령어(SetMotorEncoder,SetServo on/off,GetAbsoluteEncoder)등은 거절한다.
    ERR_REJECT_COMMAND =                    ERROR_CODE(InfError,   0X0B000000),
    //Bias offset이 300이상 일때
    ERR_BIAS_SETTING =                      ERROR_CODE(InfError,   0x0C000000),
} CommandCode;

#endif  /* __COMMAND_LIST_H__ */