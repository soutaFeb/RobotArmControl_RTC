// -*- C++ -*-
/*!
 * @file  AccelerationControllerTest.cpp
 * @brief ModuleDescription
 * @date $Date$
 *
 * $Id$
 */

#include "AccelerationControllerTest.h"

// Module specification
// <rtc-template block="module_spec">
static const char* accelerationcontroller_spec[] =
  {
    "implementation_id", "AccelerationControllerTest",
    "type_name",         "AccelerationControllerTest",
    "description",       "ModuleDescription",
    "version",           "1.0.0",
    "vendor",            "VenderName",
    "category",          "Category",
    "activity_type",     "PERIODIC",
    "kind",              "DataFlowComponent",
    "max_instance",      "1",
    "language",          "C++",
    "lang_type",         "compile",
    // Configuration variables
    "conf.default.accel", "0.2",
    "conf.default.maxSpeed", "20",

    // Widget
    "conf.__widget__.accel", "text",
    "conf.__widget__.maxSpeed", "text",
    // Constraints

    "conf.__type__.accel", "double",
    "conf.__type__.maxSpeed", "double",

    ""
  };
// </rtc-template>

/*!
 * @brief constructor
 * @param manager Maneger Object
 */
AccelerationControllerTest::AccelerationControllerTest(RTC::Manager* manager)
    // <rtc-template block="initializer">
  : RTC::DataFlowComponentBase(manager),
    m_targetPos_inputIn("targetPos_input", m_targetPos_input),
    m_position_outputOut("position_output", m_position_output)

    // </rtc-template>
{
}

/*!
 * @brief destructor
 */
AccelerationControllerTest::~AccelerationControllerTest()
{
}



RTC::ReturnCode_t AccelerationControllerTest::onInitialize()
{
  // Registration: InPort/OutPort/Service
  // <rtc-template block="registration">
  // Set InPort buffers
  addInPort("position_output", m_position_outputIn);
  
  // Set OutPort buffer
  addOutPort("targetPos_input", m_targetPos_inputOut);
  
  // Set service provider to Ports
  
  // Set service consumers to Ports
  
  // Set CORBA Service Ports
  
  // </rtc-template>

  // <rtc-template block="bind_config">
  // Bind variables and configuration variable
  bindParameter("accel", m_accel, "0.2");
  bindParameter("maxSpeed", m_maxSpeed, "20");
  // </rtc-template>
  
  return RTC::RTC_OK;
}

/*
RTC::ReturnCode_t AccelerationControllerTest::onFinalize()
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t AccelerationControllerTest::onStartup(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t AccelerationControllerTest::onShutdown(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/


RTC::ReturnCode_t AccelerationControllerTest::onActivated(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t AccelerationControllerTest::onDeactivated(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t AccelerationControllerTest::onExecute(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}

/*
RTC::ReturnCode_t AccelerationControllerTest::onAborting(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t AccelerationControllerTest::onError(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t AccelerationControllerTest::onReset(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t AccelerationControllerTest::onStateUpdate(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t AccelerationControllerTest::onRateChanged(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/



extern "C"
{
 
  void AccelerationControllerTestInit(RTC::Manager* manager)
  {
    coil::Properties profile(accelerationcontroller_spec);
    manager->registerFactory(profile,
                             RTC::Create<AccelerationControllerTest>,
                             RTC::Delete<AccelerationControllerTest>);
  }
  
};


