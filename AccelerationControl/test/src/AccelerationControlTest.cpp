// -*- C++ -*-
/*!
 * @file  AccelerationControlTest.cpp
 * @brief ModuleDescription
 * @date $Date$
 *
 * $Id$
 */

#include "AccelerationControlTest.h"

// Module specification
// <rtc-template block="module_spec">
static const char* accelerationcontrol_spec[] =
  {
    "implementation_id", "AccelerationControlTest",
    "type_name",         "AccelerationControlTest",
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
    "conf.default.maxSpeed", "10",

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
AccelerationControlTest::AccelerationControlTest(RTC::Manager* manager)
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
AccelerationControlTest::~AccelerationControlTest()
{
}



RTC::ReturnCode_t AccelerationControlTest::onInitialize()
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
  bindParameter("maxSpeed", m_maxSpeed, "10");
  // </rtc-template>
  
  return RTC::RTC_OK;
}

/*
RTC::ReturnCode_t AccelerationControlTest::onFinalize()
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t AccelerationControlTest::onStartup(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t AccelerationControlTest::onShutdown(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/


RTC::ReturnCode_t AccelerationControlTest::onActivated(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t AccelerationControlTest::onDeactivated(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t AccelerationControlTest::onExecute(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}

/*
RTC::ReturnCode_t AccelerationControlTest::onAborting(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t AccelerationControlTest::onError(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t AccelerationControlTest::onReset(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t AccelerationControlTest::onStateUpdate(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t AccelerationControlTest::onRateChanged(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/



extern "C"
{
 
  void AccelerationControlTestInit(RTC::Manager* manager)
  {
    coil::Properties profile(accelerationcontrol_spec);
    manager->registerFactory(profile,
                             RTC::Create<AccelerationControlTest>,
                             RTC::Delete<AccelerationControlTest>);
  }
  
};


