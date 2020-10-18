// -*- C++ -*-
/*!
 * @file  RobotArmAutomaticControllerTest.cpp
 * @brief ModuleDescription
 * @date $Date$
 *
 * $Id$
 */

#include "RobotArmAutomaticControllerTest.h"

// Module specification
// <rtc-template block="module_spec">
static const char* robotarmautomaticcontroller_spec[] =
  {
    "implementation_id", "RobotArmAutomaticControllerTest",
    "type_name",         "RobotArmAutomaticControllerTest",
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
RobotArmAutomaticControllerTest::RobotArmAutomaticControllerTest(RTC::Manager* manager)
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
RobotArmAutomaticControllerTest::~RobotArmAutomaticControllerTest()
{
}



RTC::ReturnCode_t RobotArmAutomaticControllerTest::onInitialize()
{
  // Registration: InPort/OutPort/Service
  // <rtc-template block="registration">
  // Set InPort buffers
  addInPort("targetPos_output", m_targetPos_outputIn);
  
  // Set OutPort buffer
  addOutPort("autoSignal_input", m_autoSignal_inputOut);
  
  // Set service provider to Ports
  
  // Set service consumers to Ports
  
  // Set CORBA Service Ports
  
  // </rtc-template>

  // <rtc-template block="bind_config">
  // </rtc-template>
  
  return RTC::RTC_OK;
}

/*
RTC::ReturnCode_t RobotArmAutomaticControllerTest::onFinalize()
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t RobotArmAutomaticControllerTest::onStartup(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t RobotArmAutomaticControllerTest::onShutdown(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/


RTC::ReturnCode_t RobotArmAutomaticControllerTest::onActivated(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t RobotArmAutomaticControllerTest::onDeactivated(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t RobotArmAutomaticControllerTest::onExecute(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}

/*
RTC::ReturnCode_t RobotArmAutomaticControllerTest::onAborting(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t RobotArmAutomaticControllerTest::onError(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t RobotArmAutomaticControllerTest::onReset(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t RobotArmAutomaticControllerTest::onStateUpdate(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t RobotArmAutomaticControllerTest::onRateChanged(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/



extern "C"
{
 
  void RobotArmAutomaticControllerTestInit(RTC::Manager* manager)
  {
    coil::Properties profile(robotarmautomaticcontroller_spec);
    manager->registerFactory(profile,
                             RTC::Create<RobotArmAutomaticControllerTest>,
                             RTC::Delete<RobotArmAutomaticControllerTest>);
  }
  
};


