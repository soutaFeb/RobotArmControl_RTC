// -*- C++ -*-
/*!
 * @file  RobotArmGUITest.cpp
 * @brief ModuleDescription
 * @date $Date$
 *
 * $Id$
 */

#include "RobotArmGUITest.h"

// Module specification
// <rtc-template block="module_spec">
static const char* robotarmgui_spec[] =
  {
    "implementation_id", "RobotArmGUITest",
    "type_name",         "RobotArmGUITest",
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
    "conf.default.upperArmLength", "300.0",
    "conf.default.lowerArmLength", "300.0",
    "conf.default.outerLimitRadius", "500.0",
    "conf.default.innerLimitRadius", "100.0",
    "conf.default.showSideView", "1",
    "conf.default.showCoordinates", "1",
    "conf.default.showCoordinateAxes", "1",
    "conf.default.showAutoButton", "1",
    "conf.default.auxiliaryLineNum", "3",
    "conf.default.auxiliaryArcNum", "3",
    "conf.default.wheelRate", "10.0",
    "conf.default.switchWheelDirection", "0",
    "conf.default.accentColor_R", "255",
    "conf.default.accentColor_G", "0",
    "conf.default.accentColor_B", "0",
    "conf.default.backgroundBrightness", "0",
    "conf.default.arcBrightness", "50",

    // Widget
    "conf.__widget__.upperArmLength", "text",
    "conf.__widget__.lowerArmLength", "text",
    "conf.__widget__.outerLimitRadius", "text",
    "conf.__widget__.innerLimitRadius", "text",
    "conf.__widget__.showSideView", "text",
    "conf.__widget__.showCoordinates", "text",
    "conf.__widget__.showCoordinateAxes", "text",
    "conf.__widget__.showAutoButton", "text",
    "conf.__widget__.auxiliaryLineNum", "text",
    "conf.__widget__.auxiliaryArcNum", "text",
    "conf.__widget__.wheelRate", "text",
    "conf.__widget__.switchWheelDirection", "text",
    "conf.__widget__.accentColor_R", "text",
    "conf.__widget__.accentColor_G", "text",
    "conf.__widget__.accentColor_B", "text",
    "conf.__widget__.backgroundBrightness", "text",
    "conf.__widget__.arcBrightness", "text",
    // Constraints

    "conf.__type__.upperArmLength", "double",
    "conf.__type__.lowerArmLength", "double",
    "conf.__type__.outerLimitRadius", "double",
    "conf.__type__.innerLimitRadius", "double",
    "conf.__type__.showSideView", "int",
    "conf.__type__.showCoordinates", "int",
    "conf.__type__.showCoordinateAxes", "int",
    "conf.__type__.showAutoButton", "int",
    "conf.__type__.auxiliaryLineNum", "int",
    "conf.__type__.auxiliaryArcNum", "int",
    "conf.__type__.wheelRate", "double",
    "conf.__type__.switchWheelDirection", "int",
    "conf.__type__.accentColor_R", "int",
    "conf.__type__.accentColor_G", "int",
    "conf.__type__.accentColor_B", "int",
    "conf.__type__.backgroundBrightness", "int",
    "conf.__type__.arcBrightness", "int",

    ""
  };
// </rtc-template>

/*!
 * @brief constructor
 * @param manager Maneger Object
 */
RobotArmGUITest::RobotArmGUITest(RTC::Manager* manager)
    // <rtc-template block="initializer">
  : RTC::DataFlowComponentBase(manager),
    m_targetPos_inputIn("targetPos_input", m_targetPos_input),
    m_position_inputIn("position_input", m_position_input),
    m_autoSignal_outputOut("autoSignal_output", m_autoSignal_output),
    m_angle_outputOut("angle_output", m_angle_output),
    m_targetPos_outputOut("targetPos_output", m_targetPos_output)

    // </rtc-template>
{
}

/*!
 * @brief destructor
 */
RobotArmGUITest::~RobotArmGUITest()
{
}



RTC::ReturnCode_t RobotArmGUITest::onInitialize()
{
  // Registration: InPort/OutPort/Service
  // <rtc-template block="registration">
  // Set InPort buffers
  addInPort("autoSignal_output", m_autoSignal_outputIn);
  addInPort("angle_output", m_angle_outputIn);
  addInPort("targetPos_output", m_targetPos_outputIn);
  
  // Set OutPort buffer
  addOutPort("targetPos_input", m_targetPos_inputOut);
  addOutPort("position_input", m_position_inputOut);
  
  // Set service provider to Ports
  
  // Set service consumers to Ports
  
  // Set CORBA Service Ports
  
  // </rtc-template>

  // <rtc-template block="bind_config">
  // Bind variables and configuration variable
  bindParameter("upperArmLength", m_upperArmLength, "300.0");
  bindParameter("lowerArmLength", m_lowerArmLength, "300.0");
  bindParameter("outerLimitRadius", m_outerLimitRadius, "500.0");
  bindParameter("innerLimitRadius", m_innerLimitRadius, "100.0");
  bindParameter("showSideView", m_showSideView, "1");
  bindParameter("showCoordinates", m_showCoordinates, "1");
  bindParameter("showCoordinateAxes", m_showCoordinateAxes, "1");
  bindParameter("showAutoButton", m_showAutoButton, "1");
  bindParameter("auxiliaryLineNum", m_auxiliaryLineNum, "3");
  bindParameter("auxiliaryArcNum", m_auxiliaryArcNum, "3");
  bindParameter("wheelRate", m_wheelRate, "10.0");
  bindParameter("switchWheelDirection", m_switchWheelDirection, "0");
  bindParameter("accentColor_R", m_accentColor_R, "255");
  bindParameter("accentColor_G", m_accentColor_G, "0");
  bindParameter("accentColor_B", m_accentColor_B, "0");
  bindParameter("backgroundBrightness", m_backgroundBrightness, "0");
  bindParameter("arcBrightness", m_arcBrightness, "50");
  // </rtc-template>
  
  return RTC::RTC_OK;
}

/*
RTC::ReturnCode_t RobotArmGUITest::onFinalize()
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t RobotArmGUITest::onStartup(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t RobotArmGUITest::onShutdown(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/


RTC::ReturnCode_t RobotArmGUITest::onActivated(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t RobotArmGUITest::onDeactivated(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t RobotArmGUITest::onExecute(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}

/*
RTC::ReturnCode_t RobotArmGUITest::onAborting(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t RobotArmGUITest::onError(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t RobotArmGUITest::onReset(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t RobotArmGUITest::onStateUpdate(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t RobotArmGUITest::onRateChanged(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/



extern "C"
{
 
  void RobotArmGUITestInit(RTC::Manager* manager)
  {
    coil::Properties profile(robotarmgui_spec);
    manager->registerFactory(profile,
                             RTC::Create<RobotArmGUITest>,
                             RTC::Delete<RobotArmGUITest>);
  }
  
};


