// -*- C++ -*-
/*!
 * @file  RobotArmAutomaticController.cpp
 * @brief ModuleDescription
 * @date $Date$
 *
 * $Id$
 */

#include "RobotArmAutomaticController.h"
#include<iostream>
#include<fstream>
using namespace std;

int autoSignal = 0;
int timeCount = 0;
int allNum[3];
int dataNum[3];
double value[3][1000];
double moveInterval[3];
double posX[3][333];
double posY[3][333];
double posZ[3][333];
int sendNum = 0;

// Module specification
// <rtc-template block="module_spec">
static const char* robotarmautomaticcontroller_spec[] =
  {
    "implementation_id", "RobotArmAutomaticController",
    "type_name",         "RobotArmAutomaticController",
    "description",       "ModuleDescription",
    "version",           "1.0.0",
    "vendor",            "VenderName",
    "category",          "Category",
    "activity_type",     "PERIODIC",
    "kind",              "DataFlowComponent",
    "max_instance",      "1",
    "language",          "C++",
    "lang_type",         "compile",
    ""
  };
// </rtc-template>

/*!
 * @brief constructor
 * @param manager Maneger Object
 */
RobotArmAutomaticController::RobotArmAutomaticController(RTC::Manager* manager)
    // <rtc-template block="initializer">
  : RTC::DataFlowComponentBase(manager),
    m_autoSignal_inputIn("autoSignal_input", m_autoSignal_input),
    m_targetPos_outputOut("targetPos_output", m_targetPos_output)

    // </rtc-template>
{
}

/*!
 * @brief destructor
 */
RobotArmAutomaticController::~RobotArmAutomaticController()
{
}



RTC::ReturnCode_t RobotArmAutomaticController::onInitialize()
{
  // Registration: InPort/OutPort/Service
  // <rtc-template block="registration">
  // Set InPort buffers
  addInPort("autoSignal_input", m_autoSignal_inputIn);
  
  // Set OutPort buffer
  addOutPort("targetPos_output", m_targetPos_outputOut);
  
  // Set service provider to Ports
  
  // Set service consumers to Ports
  
  // Set CORBA Service Ports
  
  // </rtc-template>

  // <rtc-template block="bind_config">
  // </rtc-template>
  
  return RTC::RTC_OK;
}

/*
RTC::ReturnCode_t RobotArmAutomaticController::onFinalize()
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t RobotArmAutomaticController::onStartup(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t RobotArmAutomaticController::onShutdown(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/


RTC::ReturnCode_t RobotArmAutomaticController::onActivated(RTC::UniqueId ec_id)
{
    m_targetPos_output.data.length(1);
    m_targetPos_output.data[0] = 3;//データファイルの数をGUIコンポーネントに送る
    m_targetPos_outputOut.write();

    ifstream file1("data1.dat");
    while (file1 >> value[0][allNum[0]]) {// スペースで区切られた値を読み込む
        allNum[0]++;
    }
    ifstream file2("data2.dat");
    while (file2 >> value[1][allNum[1]]) {
        allNum[1]++;
    }
    ifstream file3("data3.dat");
    while (file3 >> value[2][allNum[2]]) {
        allNum[2]++;
    }

    for (int i = 0; i < 3; i++) {
        dataNum[i] = (allNum[i] - 1) / 3;
        moveInterval[i] = value[i][0];
        moveInterval[i] = int(moveInterval[i] * 60 / 1000);
        for (int j = 0; j < dataNum[i]; j++) {
            posX[i][j] = value[i][j * 3 + 1];
            posY[i][j] = value[i][j * 3 + 2];
            posZ[i][j] = value[i][j * 3 + 3];
        }
    }

  return RTC::RTC_OK;
}


RTC::ReturnCode_t RobotArmAutomaticController::onDeactivated(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t RobotArmAutomaticController::onExecute(RTC::UniqueId ec_id)
{
    //GUIコンポーネントからデータを受け取る
    if (m_autoSignal_inputIn.isNew()) {
        m_autoSignal_inputIn.read();
        autoSignal = m_autoSignal_input.data;

        if (autoSignal > 0) {
            m_targetPos_output.data.length(3);
            if (timeCount == 0) {
                m_targetPos_output.data[0] = posX[autoSignal - 1][sendNum];
                m_targetPos_output.data[1] = posY[autoSignal - 1][sendNum];
                m_targetPos_output.data[2] = posZ[autoSignal - 1][sendNum];
                sendNum++;
            }
            timeCount++;
            if (timeCount >= moveInterval[autoSignal - 1])timeCount = 0;
            if (sendNum > dataNum[autoSignal - 1]) {
                m_targetPos_output.data[0] = 1000;
                m_targetPos_output.data[1] = 1000;
                m_targetPos_output.data[2] = 1000;
            }
            m_targetPos_outputOut.write();
        }
        else {
            timeCount = 0;
            sendNum = 0;
        }
    }

  return RTC::RTC_OK;
}

/*
RTC::ReturnCode_t RobotArmAutomaticController::onAborting(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t RobotArmAutomaticController::onError(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t RobotArmAutomaticController::onReset(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t RobotArmAutomaticController::onStateUpdate(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t RobotArmAutomaticController::onRateChanged(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/



extern "C"
{
 
  void RobotArmAutomaticControllerInit(RTC::Manager* manager)
  {
    coil::Properties profile(robotarmautomaticcontroller_spec);
    manager->registerFactory(profile,
                             RTC::Create<RobotArmAutomaticController>,
                             RTC::Delete<RobotArmAutomaticController>);
  }
  
};


