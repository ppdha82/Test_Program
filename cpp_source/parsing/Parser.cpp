/*
 * =====================================================================================
 *
 *       Filename:  parsingData.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2025년 05월 28일 13시 39분 22초
 *       Revision:  none
 *       Compiler:  g++
 *
 *         Author:  Deuk Hyun Park (ppdha82), ppdha82@gmail.com
 *        Company:  Private
 *
 * =====================================================================================
 */


#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <stdint.h>

#include "commandList.h"

using namespace std;

class Parser
{
public:
    void checkCommand(ofstream &out, vector<uint32_t> &result)
    {
        for(size_t i = 0;i < result.size();i++)
        {
            if(result.at(i) == GET_DEVICE_INFORMATION)
            {
                out << " GET_DEVICE_INFORMATION";
            }
            else if(result.at(i) == SET_NETWORK_TIMEOUT)
            {
                out << " SET_NETWORK_TIMEOUT";
            }
            else if(result.at(i) == GET_CALIBRATION_BIAS)
            {
                out << " GET_CALIBRATION_BIAS";
            }
            else if(result.at(i) == SET_CALIBRATION_BIAS)
            {
                out << " SET_CALIBRATION_BIAS";
            }
            else if(result.at(i) == GET_MOTOR_TYPE)
            {
                out << " GET_MOTOR_TYPE";
            }
            else if(result.at(i) == SET_MOTOR_TYPE)
            {
                out << " SET_MOTOR_TYPE";
            }
            else if(result.at(i) == GET_MOTOR_STATUS)
            {
                out << " GET_MOTOR_STATUS";
            }
            else if(result.at(i) == GET_SERVO_STATUS)
            {
                out << " GET_SERVO_STATUS";
            }
            else if(result.at(i) == SET_SERVO_STATUS)
            {
                out << " SET_SERVO_STATUS";
            }
            else if(result.at(i) == GET_CONTROL_MODE)
            {
                out << " GET_CONTROL_MODE";
            }
            else if(result.at(i) == SET_CONTROL_MODE)
            {
                out << " SET_CONTROL_MODE";
            }
            else if(result.at(i) == SET_SAVE_DATALOG)
            {
                out << " SET_SAVE_DATALOG";
            }
            else if(result.at(i) == GET_SAVE_DATALOG)
            {
                out << " GET_SAVE_DATALOG";
            }
            else if(result.at(i) == GET_MOTOR_DATA)
            {
                out << " GET_MOTOR_DATA";
            }
            else if(result.at(i) == GET_CONTROL_MODE)
            {
                out << " GET_CONTROL_MODE";
            }
            else if(result.at(i) == GET_DESIRED_CURRENT)
            {
                out << " GET_DESIRED_CURRENT";
            }
            else if(result.at(i) == SET_DESIRED_CURRENT)
            {
                out << " SET_DESIRED_CURRENT";
            }
            else if(result.at(i) == GET_ACTUAL_CURRENT)
            {
                out << " GET_ACTUAL_CURRENT";
            }
            else if(result.at(i) == GET_TOTAL_DESIRED_CURRENT)
            {
                out << " GET_TOTAL_DESIRED_CURRENT";
            }
            else if(result.at(i) == GET_DESIRED_VELOCITY)
            {
                out << " GET_DESIRED_VELOCITY";
            }
            else if(result.at(i) == GET_DESIRED_CURRENT)
            {
                out << " GET_DESIRED_CURRENT";
            }
            else if(result.at(i) == SET_DESIRED_VELOCITY)
            {
                out << " SET_DESIRED_VELOCITY";
            }
            else if(result.at(i) == GET_ACTUAL_VELOCITY)
            {
                out << " GET_ACTUAL_VELOCITY";
            }
            else if(result.at(i) == GET_DESIRED_VOLTAGE)
            {
                out << " GET_DESIRED_VOLTAGE";
            }
            else if(result.at(i) == SET_DESIRED_VOLTAGE)
            {
                out << " SET_DESIRED_VOLTAGE";
            }
            else if(result.at(i) == GET_ACTUAL_VOLTAGE)
            {
                out << " GET_ACTUAL_VOLTAGE";
            }
            else if(result.at(i) == GET_DESIRED_POSITION)
            {
                out << " GET_DESIRED_POSITION";
            }
            else if(result.at(i) == SET_DESIRED_POSITION)
            {
                out << " SET_DESIRED_POSITION";
            }
            else if(result.at(i) == GET_MOTOR_ENCODER)
            {
                out << " GET_MOTOR_ENCODER";
            }
            else if(result.at(i) == SET_MOTOR_ENCODER)
            {
                out << " SET_MOTOR_ENCODER";
            }
            else if(result.at(i) == GET_TRAJECTORY_POSITION)
            {
                out << " GET_TRAJECTORY_POSITION";
            }
            else if(result.at(i) == GET_CONSOLEBASE_POSITION)
            {
                out << " GET_CONSOLEBASE_POSITION";
            }
            else if(result.at(i) == SET_CONSOLEBASE_POSITION)
            {
                out << " SET_CONSOLEBASE_POSITION";
            }
            else if(result.at(i) == GET_DIGITAL_INPUT)
            {
                out << " GET_DIGITAL_INPUT";
            }
            else if(result.at(i) == GET_DIGITAL_OUTPUT)
            {
                out << " GET_DIGITAL_OUTPUT";
            }
            else if(result.at(i) == SET_DIGITAL_OUTPUT)
            {
                out << " SET_DIGITAL_OUTPUT";
            }
            else if(result.at(i) == GET_LED_FLICKER)
            {
                out << " GET_LED_FLICKER";
            }
            else if(result.at(i) == SET_LED_FLICKER)
            {
                out << " SET_LED_FLICKER";
            }
            else if(result.at(i) == GET_GRIPPER_PARAM)
            {
                out << " GET_GRIPPER_PARAM";
            }
            else if(result.at(i) == SET_GRIPPER_PARAM)
            {
                out << " SET_GRIPPER_PARAM";
            }
            else if(result.at(i) == GET_ABSOLUTE_ENCODER)
            {
                out << " GET_ABSOLUTE_ENCODER";
            }
            else if(result.at(i) == GET_ANALOG_INPUT)
            {
                out << " GET_ANALOG_INPUT";
            }
            else if(result.at(i) == GET_TEMPERATURE)
            {
                out << " GET_TEMPERATURE";
            }
            else if(result.at(i) == GET_MAIN_FPGA_REGISTER)
            {
                out << " GET_MAIN_FPGA_REGISTER";
            }
            else if(result.at(i) == SET_MAIN_FPGA_REGISTER)
            {
                out << " SET_MAIN_FPGA_REGISTER";
            }
            else if(result.at(i) == GET_SUB_FPGA_REGISTER)
            {
                out << " GET_SUB_FPGA_REGISTER";
            }
            else if(result.at(i) == SET_SUB_FPGA_REGISTER)
            {
                out << " SET_SUB_FPGA_REGISTER";
            }
            else if(result.at(i) == GET_MOBILE_BATTERY_LEVEL)
            {
                out << " GET_MOBILE_BATTERY_LEVEL";
            }
            else if(result.at(i) == GET_MOBILE_BATTERY_STATUS)
            {
                out << " GET_MOBILE_BATTERY_STATUS";
            }
            else if(result.at(i) == GET_LOCK)
            {
                out << " GET_LOCK";
            }
            else if(result.at(i) == SET_LOCK)
            {
                out << " SET_LOCK";
            }
            else if(result.at(i) == GET_STAGE)
            {
                out << " GET_STAGE";
            }
            else if(result.at(i) == SET_STAGE)
            {
                out << " SET_STAGE";
            }
            else if(result.at(i) == GET_INFINITE_POWER_BUTTON)
            {
                out << " GET_INFINITE_POWER_BUTTON";
            }
            else if(result.at(i) == GET_CURRENT_KP_GAIN)
            {
                out << " GET_CURRENT_KP_GAIN";
            }
            else if(result.at(i) == SET_CURRENT_KP_GAIN)
            {
                out << " SET_CURRENT_KP_GAIN";
            }
            else if(result.at(i) == GET_CURRENT_KI_GAIN)
            {
                out << " GET_CURRENT_KI_GAIN";
            }
            else if(result.at(i) == SET_CURRENT_KI_GAIN)
            {
                out << " SET_CURRENT_KI_GAIN";
            }
            else if(result.at(i) == GET_CURRENT_KA_GAIN)
            {
                out << " GET_CURRENT_KA_GAIN";
            }
            else if(result.at(i) == SET_CURRENT_KA_GAIN)
            {
                out << " SET_CURRENT_KA_GAIN";
            }
            else if(result.at(i) == GET_CURRENT_KFF_GAIN)
            {
                out << " GET_CURRENT_KFF_GAIN";
            }
            else if(result.at(i) == SET_CURRENT_KFF_GAIN)
            {
                out << " SET_CURRENT_KFF_GAIN";
            }
            else if(result.at(i) == GET_LQR_VELOCITY_GAIN)
            {
                out << " GET_LQR_VELOCITY_GAIN";
            }
            else if(result.at(i) == SET_LQR_VELOCITY_GAIN)
            {
                out << " SET_LQR_VELOCITY_GAIN";
            }
            else if(result.at(i) == GET_LQR_POSITION_GAIN)
            {
                out << " GET_LQR_POSITION_GAIN";
            }
            else if(result.at(i) == SET_LQR_POSITION_GAIN)
            {
                out << " SET_LQR_POSITION_GAIN";
            }
            else if(result.at(i) == GET_LQR_CURRENT_GAIN)
            {
                out << " GET_LQR_CURRENT_GAIN";
            }
            else if(result.at(i) == SET_LQR_CURRENT_GAIN)
            {
                out << " SET_LQR_CURRENT_GAIN";
            }
            else if(result.at(i) == GET_LQR_POS_INT_GAIN)
            {
                out << " GET_LQR_POS_INT_GAIN";
            }
            else if(result.at(i) == SET_LQR_POS_INT_GAIN)
            {
                out << " SET_LQR_POS_INT_GAIN";
            }
            else if(result.at(i) == GET_POS_P_GAIN)
            {
                out << " GET_POS_P_GAIN";
            }
            else if(result.at(i) == SET_POS_P_GAIN)
            {
                out << " SET_POS_P_GAIN";
            }
            else if(result.at(i) == GET_POS_I_GAIN)
            {
                out << " GET_POS_I_GAIN";
            }
            else if(result.at(i) == SET_POS_I_GAIN)
            {
                out << " SET_POS_I_GAIN";
            }
            else if(result.at(i) == GET_POS_D_GAIN)
            {
                out << " GET_POS_D_GAIN";
            }
            else if(result.at(i) == SET_POS_D_GAIN)
            {
                out << " SET_POS_D_GAIN";
            }
            else if(result.at(i) == GET_VEL_P_GAIN)
            {
                out << " GET_VEL_P_GAIN";
            }
            else if(result.at(i) == SET_VEL_P_GAIN)
            {
                out << " SET_VEL_P_GAIN";
            }
            else if(result.at(i) == GET_VEL_I_GAIN)
            {
                out << " GET_VEL_I_GAIN";
            }
            else if(result.at(i) == SET_VEL_I_GAIN)
            {
                out << " SET_VEL_I_GAIN";
            }
            else if(result.at(i) == GET_ACCELERATION_LIMIT)
            {
                out << " GET_ACCELERATION_LIMIT";
            }
            else if(result.at(i) == SET_ACCELERATION_LIMIT)
            {
                out << " SET_ACCELERATION_LIMIT";
            }
            else if(result.at(i) == GET_VELOCITY_LIMIT)
            {
                out << " GET_VELOCITY_LIMIT";
            }
            else if(result.at(i) == SET_VELOCITY_LIMIT)
            {
                out << " SET_VELOCITY_LIMIT";
            }
            else if(result.at(i) == GET_CURRENT_LIMIT)
            {
                out << " GET_CURRENT_LIMIT";
            }
            else if(result.at(i) == SET_CURRENT_LIMIT)
            {
                out << " SET_CURRENT_LIMIT";
            }
            else if(result.at(i) == GET_CURRENT_MAX_VOLT_LIMIT)
            {
                out << " GET_CURRENT_MAX_VOLT_LIMIT";
            }
            else if(result.at(i) == SET_CURRENT_MAX_VOLT_LIMIT)
            {
                out << " SET_CURRENT_MAX_VOLT_LIMIT";
            }
            else if(result.at(i) == GET_LQR_MAX_VOLT_LIMIT)
            {
                out << " GET_LQR_MAX_VOLT_LIMIT";
            }
            else if(result.at(i) == SET_LQR_MAX_VOLT_LIMIT)
            {
                out << " SET_LQR_MAX_VOLT_LIMIT";
            }
            else if(result.at(i) == GET_TRAJECTORY_GAP_LIMIT)
            {
                out << " GET_TRAJECTORY_GAP_LIMIT";
            }
            else if(result.at(i) == SET_TRAJECTORY_GAP_LIMIT)
            {
                out << " SET_TRAJECTORY_GAP_LIMIT";
            }
            else if(result.at(i) == GET_ABSOLUTE_ZERO_COUNT)
            {
                out << " GET_ABSOLUTE_ZERO_COUNT";
            }
            else if(result.at(i) == SET_ABSOLUTE_ZERO_COUNT)
            {
                out << " SET_ABSOLUTE_ZERO_COUNT";
            }
            else if(result.at(i) == GET_ABSOLUTE_MADV)
            {
                out << " GET_ABSOLUTE_MADV";
            }
            else if(result.at(i) == SET_ABSOLUTE_MADV)
            {
                out << " SET_ABSOLUTE_MADV";
            }
            else if(result.at(i) == GET_MOTOR_MADV)
            {
                out << " GET_MOTOR_MADV";
            }
            else if(result.at(i) == SET_MOTOR_MADV)
            {
                out << " SET_MOTOR_MADV";
            }
            else if(result.at(i) == GET_ENCODER_DIFF_ERROR_LIMIT)
            {
                out << " GET_ENCODER_DIFF_ERROR_LIMIT";
            }
            else if(result.at(i) == SET_ENCODER_DIFF_ERROR_LIMIT)
            {
                out << " SET_ENCODER_DIFF_ERROR_LIMIT";
            }
            else if(result.at(i) == GET_STALL_DETECTION_RATIO)
            {
                out << " GET_STALL_DETECTION_RATIO";
            }
            else if(result.at(i) == SET_STALL_DETECTION_RATIO)
            {
                out << " SET_STALL_DETECTION_RATIO";
            }
            else if(result.at(i) == GET_OVER_CURRENT_RATIO)
            {
                out << " GET_OVER_CURRENT_RATIO";
            }
            else if(result.at(i) == SET_OVER_CURRENT_RATIO)
            {
                out << " SET_OVER_CURRENT_RATIO";
            }
            else if(result.at(i) == GET_JOINT_LIMIT_MIN)
            {
                out << " GET_JOINT_LIMIT_MIN";
            }
            else if(result.at(i) == SET_JOINT_LIMIT_MIN)
            {
                out << " SET_JOINT_LIMIT_MIN";
            }
            else if(result.at(i) == GET_JOINT_LIMIT_MAX)
            {
                out << " GET_JOINT_LIMIT_MAX";
            }
            else if(result.at(i) == SET_JOINT_LIMIT_MAX)
            {
                out << " SET_JOINT_LIMIT_MAX";
            }
            else if(result.at(i) == GET_OVER_VELOCITY_RATIO)
            {
                out << " GET_OVER_VELOCITY_RATIO";
            }
            else if(result.at(i) == SET_OVER_VELOCITY_RATIO)
            {
                out << " SET_OVER_VELOCITY_RATIO";
            }
            else if(result.at(i) == GET_UNDER_CURRENT_VOLT_RATIO)
            {
                out << " GET_UNDER_CURRENT_VOLT_RATIO";
            }
            else if(result.at(i) == SET_UNDER_CURRENT_VOLT_RATIO)
            {
                out << " SET_UNDER_CURRENT_VOLT_RATIO";
            }
            else if(result.at(i) == GET_UNDER_CURRENT_CUR_RATIO)
            {
                out << " GET_UNDER_CURRENT_CUR_RATIO";
            }
            else if(result.at(i) == SET_UNDER_CURRENT_CUR_RATIO)
            {
                out << " SET_UNDER_CURRENT_CUR_RATIO";
            }
            else if(result.at(i) == GET_MAX_JUMP_RANGE)
            {
                out << " GET_MAX_JUMP_RANGE";
            }
            else if(result.at(i) == SET_MAX_JUMP_RANGE)
            {
                out << " SET_MAX_JUMP_RANGE";
            }
            else if(result.at(i) == GET_CURRENT_GAP_RATIO)
            {
                out << " GET_CURRENT_GAP_RATIO";
            }
            else if(result.at(i) == SET_CURRENT_GAP_RATIO)
            {
                out << " SET_CURRENT_GAP_RATIO";
            }
            else if(result.at(i) == GET_VEL_LPF_TAU)
            {
                out << " GET_VEL_LPF_TAU";
            }
            else if(result.at(i) == SET_VEL_LPF_TAU)
            {
                out << " SET_VEL_LPF_TAU";
            }
            else if(result.at(i) == GET_PID_LPF_CURRENT)
            {
                out << " GET_PID_LPF_CURRENT";
            }
            else if(result.at(i) == SET_PID_LPF_CURRENT)
            {
                out << " SET_PID_LPF_CURRENT";
            }
            else if(result.at(i) == GET_LQR_LPF_CURRENT)
            {
                out << " GET_LQR_LPF_CURRENT";
            }
            else if(result.at(i) == SET_LQR_LPF_CURRENT)
            {
                out << " SET_LQR_LPF_CURRENT";
            }
            else if(result.at(i) == GET_CUR_LPF_CURRENT)
            {
                out << " GET_CUR_LPF_CURRENT";
            }
            else if(result.at(i) == SET_CUR_LPF_CURRENT)
            {
                out << " SET_CUR_LPF_CURRENT";
            }
            else if(result.at(i) == GET_PID_LPF_VELOCITY)
            {
                out << " GET_PID_LPF_VELOCITY";
            }
            else if(result.at(i) == SET_PID_LPF_VELOCITY)
            {
                out << " SET_PID_LPF_VELOCITY";
            }
            else if(result.at(i) == GET_LQR_LPF_VELOCITY)
            {
                out << " GET_LQR_LPF_VELOCITY";
            }
            else if(result.at(i) == SET_LQR_LPF_VELOCITY)
            {
                out << " SET_LQR_LPF_VELOCITY";
            }
            else if(result.at(i) == GET_CUR_LPF_VELOCITY)
            {
                out << " GET_CUR_LPF_VELOCITY";
            }
            else if(result.at(i) == SET_CUR_LPF_VELOCITY)
            {
                out << " SET_CUR_LPF_VELOCITY";
            }
            else if(result.at(i) == GET_STIFFNESS_CONSTANT)
            {
                out << " GET_STIFFNESS_CONSTANT";
            }
            else if(result.at(i) == SET_STIFFNESS_CONSTANT)
            {
                out << " SET_STIFFNESS_CONSTANT";
            }
            else if(result.at(i) == GET_STIFFNESS_CURRENT)
            {
                out << " GET_STIFFNESS_CURRENT";
            }
            else if(result.at(i) == SET_STIFFNESS_CURRENT)
            {
                out << " SET_STIFFNESS_CURRENT";
            }
            else if(result.at(i) == GET_DAMPING_VELOCITY)
            {
                out << " GET_DAMPING_VELOCITY";
            }
            else if(result.at(i) == SET_DAMPING_VELOCITY)
            {
                out << " SET_DAMPING_VELOCITY";
            }
            else if(result.at(i) == GET_DAMPING_CONSTANT)
            {
                out << " GET_DAMPING_CONSTANT";
            }
            else if(result.at(i) == SET_DAMPING_CONSTANT)
            {
                out << " SET_DAMPING_CONSTANT";
            }
            else if(result.at(i) == GET_FRICTION_THRESHOLD)
            {
                out << " GET_FRICTION_THRESHOLD";
            }
            else if(result.at(i) == GET_FRICTION_COMPENSATION_GAIN)
            {
                out << " GET_FRICTION_COMPENSATION_GAIN";
            }
            else if(result.at(i) == SET_FRICTION_COMPENSATION_GAIN)
            {
                out << " SET_FRICTION_COMPENSATION_GAIN";
            }
            else if(result.at(i) == GET_FRICTION_COULOMB)
            {
                out << " GET_FRICTION_COULOMB";
            }
            else if(result.at(i) == SET_FRICTION_COULOMB)
            {
                out << " SET_FRICTION_COULOMB";
            }
            else if(result.at(i) == GET_FRICTION_VISCOUS)
            {
                out << " GET_FRICTION_VISCOUS";
            }
            else if(result.at(i) == SET_FRICTION_VISCOUS)
            {
                out << " SET_FRICTION_VISCOUS";
            }
            else if(result.at(i) == GET_FRICTION_EFFICINCY)
            {
                out << " GET_FRICTION_EFFICINCY";
            }
            else if(result.at(i) == SET_FRICTION_EFFICINCY)
            {
                out << " SET_FRICTION_EFFICINCY";
            }
            else if(result.at(i) == GET_GRAVITY_COMPENSATION_GAIN)
            {
                out << " GET_GRAVITY_COMPENSATION_GAIN";
            }
            else if(result.at(i) == SET_GRAVITY_COMPENSATION_GAIN)
            {
                out << " SET_GRAVITY_COMPENSATION_GAIN";
            }
            else if(result.at(i) == GET_GRAVITY_COMPENSATION_OFFSET)
            {
                out << " GET_GRAVITY_COMPENSATION_OFFSET";
            }
            else if(result.at(i) == SET_GRAVITY_COMPENSATION_OFFSET)
            {
                out << " SET_GRAVITY_COMPENSATION_OFFSET";
            }
            else if(result.at(i) == GET_SPRING_INTERCEPT)
            {
                out << " GET_SPRING_INTERCEPT";
            }
            else if(result.at(i) == SET_SPRING_INTERCEPT)
            {
                out << " SET_SPRING_INTERCEPT";
            }
            else if(result.at(i) == GET_SPRING_SLOPE)
            {
                out << " GET_SPRING_SLOPE";
            }
            else if(result.at(i) == SET_SPRING_SLOPE)
            {
                out << " SET_SPRING_SLOPE";
            }
            else if(result.at(i) == SET_STIFFNESS_SOUND_ONFF)
            {
                out << " SET_STIFFNESS_SOUND_ONFF";
            }
            else if(result.at(i) == GET_INFINITE_RFID)
            {
                out << " GET_INFINITE_RFID";
            }
            else if(result.at(i) == SET_INFINITE_RFID)
            {
                out << " SET_INFINITE_RFID";
            }
            else if(result.at(i) == GET_GATHERING_INFO)
            {
                out << " GET_GATHERING_INFO";
            }
            else if(result.at(i) == SET_GATHERING_INFO)
            {
                out << " SET_GATHERING_INFO";
            }
            else if(result.at(i) == GATHERING_DATA)
            {
                out << " GATHERING_DATA";
            }
            else if(result.at(i) == START_GATHERING)
            {
                out << " START_GATHERING";
            }
            else if(result.at(i) == STOP_GATHERING)
            {
                out << " STOP_GATHERING";
            }
            else if(result.at(i) == START_DATA_PORT)
            {
                out << " START_DATA_PORT";
            }
            else if(result.at(i) == START_EVENT_PORT)
            {
                out << " START_EVENT_PORT";
            }
            else if(result.at(i) == GET_DEBUG_FLOAT_VALUE)
            {
                out << " GET_DEBUG_FLOAT_VALUE";
            }
            else if(result.at(i) == SET_DEBUG_FLOAT_VALUE)
            {
                out << " SET_DEBUG_FLOAT_VALUE";
            }
            else if(result.at(i) == GET_DEBUG_INT32_VALUE)
            {
                out << " GET_DEBUG_INT32_VALUE";
            }
            else if(result.at(i) == SET_DEBUG_INT32_VALUE)
            {
                out << " SET_DEBUG_INT32_VALUE";
            }
            else if(result.at(i) == GET_DEBUG_UINT32_VALUE)
            {
                out << " GET_DEBUG_UINT32_VALUE";
            }
            else if(result.at(i) == SET_DEBUG_UINT32_VALUE)
            {
                out << " SET_DEBUG_UINT32_VALUE";
            }
            else if(result.at(i) == GET_MOTION_PLAYBACK_STATUS)
            {
                out << " GET_MOTION_PLAYBACK_STATUS";
            }
            else if(result.at(i) == SET_MOTION_PLAYBACK_PLAY)
            {
                out << " SET_MOTION_PLAYBACK_PLAY";
            }
            else if(result.at(i) == SET_MOTION_PLAYBACK_SETUP)
            {
                out << " SET_MOTION_PLAYBACK_SETUP";
            }
            else if(result.at(i) == GET_FAULT_COUNT)
            {
                out << " GET_FAULT_COUNT";
            }
            else if(result.at(i) == SET_FAULT_COUNT)
            {
                out << " SET_FAULT_COUNT";
            }
            else if(result.at(i) == SET_VISION_NETWORK_ALIVE)
            {
                out << " SET_VISION_NETWORK_ALIVE";
            }
            else if(result.at(i) == GET_MOBILE_NETWORK_ALIVE)
            {
                out << " GET_MOBILE_NETWORK_ALIVE";
            }
            else if(result.at(i) == GET_NETWORK_ALIVE)
            {
                out << " GET_NETWORK_ALIVE";
            }
            else if(result.at(i) == GET_NETWORK_TIMEOUT_LIMIT)
            {
                out << " GET_NETWORK_TIMEOUT_LIMIT";
            }
            else if(result.at(i) == SET_NETWORK_TIMEOUT_LIMIT)
            {
                out << " SET_NETWORK_TIMEOUT_LIMIT";
            }
            else if(result.at(i) == GET_TRAJECTORY_GENERATION_MODE)
            {
                out << " GET_TRAJECTORY_GENERATION_MODE";
            }
            else if(result.at(i) == SET_TRAJECTORY_GENERATION_MODE)
            {
                out << " SET_TRAJECTORY_GENERATION_MODE";
            }
            else if(result.at(i) == SET_MOTION_STOP)
            {
                out << " SET_MOTION_STOP";
            }
            else if(result.at(i) == GET_PTP_RATIO)
            {
                out << " GET_PTP_RATIO";
            }
            else if(result.at(i) == SET_PTP_RATIO)
            {
                out << " SET_PTP_RATIO";
            }
            else if(result.at(i) == GET_SMOOTH_STOP_RATIO)
            {
                out << " GET_SMOOTH_STOP_RATIO";
            }
            else if(result.at(i) == SET_SMOOTH_STOP_RATIO)
            {
                out << " SET_SMOOTH_STOP_RATIO";
            }
            else if(result.at(i) == GET_POWER_BITWISE)
            {
                out << " GET_POWER_BITWISE";
            }
            else if(result.at(i) == SET_POWER_VALUE)
            {
                out << " SET_POWER_VALUE";
            }
            else if(result.at(i) == GET_INCREMENTAL_ENCODER)
            {
                out << " GET_INCREMENTAL_ENCODER";
            }
            else if(result.at(i) == SET_INCREMENTAL_ENCODER)
            {
                out << " SET_INCREMENTAL_ENCODER";
            }
            else
            {
                out << " UNKNOWN";
            }
        }
    }

    Parser()
    {
        init();
    }

    enum
    {
        BYTE_OFFSET = 4,
        DATA_OFFSET = 3,
    };

    void init()
    {
        ifstream in("dump.txt");

        if(in.is_open())
        {
            ofstream out("result.txt");
            string strKey("tPacket");
            string inLine;
            int commandCount = 0;
            size_t keyPos;
            vector<uint32_t> result;

            out << std::hex;

            while(getline(in, inLine))
            {
                keyPos = inLine.find(strKey);
                readAndProcess(out, result, commandCount, keyPos, inLine, strKey);
            }

            in.close();
            out.close();
        }
    }

private:
    void readAndProcess(ofstream& out, vector<uint32_t>& result, int& commandCount, size_t keyPos, string inLine, string strKey)
    {
        int lineCount = 0;
        if(keyPos != string::npos)
        {
            istringstream ssTemp(inLine.substr(keyPos + strKey.length()));
            string token;
            vector<uint8_t> bytes;

            while(ssTemp >> token)
            {
                uint8_t byte = stoi(token, NULL, 16);
                bytes.push_back(byte);
            }

            for(int i = 0;i < bytes.size();i += BYTE_OFFSET)
            {
                recordData(out, i, commandCount, bytes, result);
            }

            cout << std::hex << "lineCount[" << lineCount << "] keyPos = 0x" << keyPos << "; inLine = " << inLine.substr(keyPos + strKey.length()) << "\n";
        }
        lineCount++;
    }

    void recordData(ofstream& out, int index, int& count, vector<uint8_t>& bytes, vector<uint32_t>& result)
    {
        if(count % DATA_OFFSET == 0)
        {
            out << "\ncommandCount [" << count << "]";
        }
        uint32_t value = 0;
        value = makeUint32(index, bytes);
        out << " 0x" << value;
        result.push_back(value);

        count++;
        if(count % DATA_OFFSET == 0)
        {
            checkCommand(out, result);
            result.clear();
        }
    }

    uint32_t makeUint32(int index, vector<uint8_t>& bytes)
    {
        uint32_t value = 0;
        if(bytes.empty())
        {
            return 0;
        }
        value |= (static_cast<uint32_t>(bytes[index]));
        value |= (static_cast<uint32_t>(bytes[index + 1]) << 8);
        value |= (static_cast<uint32_t>(bytes[index + 2]) << 16);
        value |= (static_cast<uint32_t>(bytes[index + 3]) << 24);
        return value;
    }
};

int main (void)
{
    Parser parser;

	return 0;
}
