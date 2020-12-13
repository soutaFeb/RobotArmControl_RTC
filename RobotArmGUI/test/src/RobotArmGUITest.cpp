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
    "conf.default.auxiliaryLineInterval", "45.0",
    "conf.default.auxiliaryArcInterval", "100.0",
    "conf.default.wheelRate", "10.0",
    "conf.default.switchWheelDirection", "0",
    "conf.default.accentColor_R", "255",
    "conf.default.accentColor_G", "0",
    "conf.default.accentColor_B", "0",
    "conf.default.backgroundBrightness", "0",
    "conf.default.arcBrightness", "50",
    "conf.default.button1_name", "Auto",
    "conf.default.button1_pressName", "Running",
    "conf.default.button1_choicesNum", "3",
    "conf.default.button1_alternateOperation", "1",
    "conf.default.button1_linkWithRightClick", "0",
    "conf.default.button2_name", "none",
    "conf.default.button2_pressName", "pressName",
    "conf.default.button2_choicesNum", "1",
    "conf.default.button2_alternateOperation", "0",
    "conf.default.button2_linkWithRightClick", "0",

    // Widget
    "conf.__widget__.upperArmLength", "text",
    "conf.__widget__.lowerArmLength", "text",
    "conf.__widget__.outerLimitRadius", "text",
    "conf.__widget__.innerLimitRadius", "text",
    "conf.__widget__.showSideView", "text",
    "conf.__widget__.showCoordinates", "text",
    "conf.__widget__.showCoordinateAxes", "text",
    "conf.__widget__.auxiliaryLineInterval", "text",
    "conf.__widget__.auxiliaryArcInterval", "text",
    "conf.__widget__.wheelRate", "text",
    "conf.__widget__.switchWheelDirection", "text",
    "conf.__widget__.accentColor_R", "text",
    "conf.__widget__.accentColor_G", "text",
    "conf.__widget__.accentColor_B", "text",
    "conf.__widget__.backgroundBrightness", "text",
    "conf.__widget__.arcBrightness", "text",
    "conf.__widget__.button1_name", "text",
    "conf.__widget__.button1_pressName", "text",
    "conf.__widget__.button1_choicesNum", "text",
    "conf.__widget__.button1_alternateOperation", "text",
    "conf.__widget__.button1_linkWithRightClick", "text",
    "conf.__widget__.button2_name", "text",
    "conf.__widget__.button2_pressName", "text",
    "conf.__widget__.button2_choicesNum", "text",
    "conf.__widget__.button2_alternateOperation", "text",
    "conf.__widget__.button2_linkWithRightClick", "text",
    // Constraints

    "conf.__type__.upperArmLength", "double",
    "conf.__type__.lowerArmLength", "double",
    "conf.__type__.outerLimitRadius", "double",
    "conf.__type__.innerLimitRadius", "double",
    "conf.__type__.showSideView", "int",
    "conf.__type__.showCoordinates", "int",
    "conf.__type__.showCoordinateAxes", "int",
    "conf.__type__.auxiliaryLineInterval", "double",
    "conf.__type__.auxiliaryArcInterval", "double",
    "conf.__type__.wheelRate", "double",
    "conf.__type__.switchWheelDirection", "int",
    "conf.__type__.accentColor_R", "int",
    "conf.__type__.accentColor_G", "int",
    "conf.__type__.accentColor_B", "int",
    "conf.__type__.backgroundBrightness", "int",
    "conf.__type__.arcBrightness", "int",
    "conf.__type__.button1_name", "string",
    "conf.__type__.button1_pressName", "string",
    "conf.__type__.button1_choicesNum", "int",
    "conf.__type__.button1_alternateOperation", "int",
    "conf.__type__.button1_linkWithRightClick", "int",
    "conf.__type__.button2_name", "string",
    "conf.__type__.button2_pressName", "string",
    "conf.__type__.button2_choicesNum", "int",
    "conf.__type__.button2_alternateOperation", "int",
    "conf.__type__.button2_linkWithRightClick", "int",

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
    m_button1_inputIn("button1_input", m_button1_input),
    m_button2_inputIn("button2_input", m_button2_input),
    m_displayVal_inputIn("displayVal_input", m_displayVal_input),
    m_targetPos_inputIn("targetPos_input", m_targetPos_input),
    m_position_inputIn("position_input", m_position_input),
    m_button1_outputOut("button1_output", m_button1_output),
    m_button2_outputOut("button2_output", m_button2_output),
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
  addInPort("button1_output", m_button1_outputIn);
  addInPort("button2_output", m_button2_outputIn);
  addInPort("angle_output", m_angle_outputIn);
  addInPort("targetPos_output", m_targetPos_outputIn);
  
  // Set OutPort buffer
  addOutPort("button1_input", m_button1_inputOut);
  addOutPort("button2_input", m_button2_inputOut);
  addOutPort("displayVal_input", m_displayVal_inputOut);
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
  bindParameter("auxiliaryLineInterval", m_auxiliaryLineInterval, "45.0");
  bindParameter("auxiliaryArcInterval", m_auxiliaryArcInterval, "100.0");
  bindParameter("wheelRate", m_wheelRate, "10.0");
  bindParameter("switchWheelDirection", m_switchWheelDirection, "0");
  bindParameter("accentColor_R", m_accentColor_R, "255");
  bindParameter("accentColor_G", m_accentColor_G, "0");
  bindParameter("accentColor_B", m_accentColor_B, "0");
  bindParameter("backgroundBrightness", m_backgroundBrightness, "0");
  bindParameter("arcBrightness", m_arcBrightness, "50");
  bindParameter("button1_name", m_button1_name, "Auto");
  bindParameter("button1_pressName", m_button1_pressName, "Running");
  bindParameter("button1_choicesNum", m_button1_choicesNum, "3");
  bindParameter("button1_alternateOperation", m_button1_alternateOperation, "1");
  bindParameter("button1_linkWithRightClick", m_button1_linkWithRightClick, "0");
  bindParameter("button2_name", m_button2_name, "none");
  bindParameter("button2_pressName", m_button2_pressName, "pressName");
  bindParameter("button2_choicesNum", m_button2_choicesNum, "1");
  bindParameter("button2_alternateOperation", m_button2_alternateOperation, "0");
  bindParameter("button2_linkWithRightClick", m_button2_linkWithRightClick, "0");
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


