// -*- C++ -*-
/*!
 * @file  RobotArmCUI.cpp
 * @brief ModuleDescription
 * @date $Date$
 *
 * $Id$
 */

#include "RobotArmCUI.h"

// Module specification
// <rtc-template block="module_spec">
static const char* robotarmcui_spec[] =
  {
    "implementation_id", "RobotArmCUI",
    "type_name",         "RobotArmCUI",
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
RobotArmCUI::RobotArmCUI(RTC::Manager* manager)
    // <rtc-template block="initializer">
  : RTC::DataFlowComponentBase(manager),
    m_targetPos_outputOut("targetPos_output", m_targetPos_output)

    // </rtc-template>
{
}

/*!
 * @brief destructor
 */
RobotArmCUI::~RobotArmCUI()
{
}



RTC::ReturnCode_t RobotArmCUI::onInitialize()
{
  // Registration: InPort/OutPort/Service
  // <rtc-template block="registration">
  // Set InPort buffers
  
  // Set OutPort buffer
  addOutPort("targetPos_output", m_targetPos_outputOut);
  
  // Set service provider to Ports
  
  // Set service consumers to Ports
  
  // Set CORBA Service Ports
  
  // </rtc-template>

  // <rtc-template block="bind_config">
  // </rtc-template>

  std::cout << "RobotArmCUI ready!" << std::endl;
  
  return RTC::RTC_OK;
}

/*
RTC::ReturnCode_t RobotArmCUI::onFinalize()
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t RobotArmCUI::onStartup(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t RobotArmCUI::onShutdown(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/


RTC::ReturnCode_t RobotArmCUI::onActivated(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t RobotArmCUI::onDeactivated(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t RobotArmCUI::onExecute(RTC::UniqueId ec_id)
{
    std::cout << "" << std::endl;
    std::cout << "Please input target coordinates: " << std::endl;

    using std::string;
    string x;
    string y;
    string z;
    int signX = 1;
    int signY = 1;
    int signZ = 1;
    bool xFlag = false;
    bool yFlag = false;
    bool zFlag = false;
    std::cout << " X : ";
    std::cin >> x;
    if (x[0] == '-') {
        x = x.replace(0, 1, "");
        signX = -1;
    }
    if (std::all_of(x.cbegin(), x.cend(), isdigit) && x.size() > 0) {
        m_targetPos_output.data.x = 0.001 * signX * std::stod(x);
        xFlag = true;
    }
    if (xFlag) {
        std::cout << " Y : ";
        std::cin >> y;
        if (y[0] == '-') {
            y = y.replace(0, 1, "");
            signY = -1;
        }
        if (std::all_of(y.cbegin(), y.cend(), isdigit) && y.size() > 0) {
            m_targetPos_output.data.y = 0.001 * signY * std::stod(y);
            yFlag = true;
        }
    }
    if (xFlag && yFlag) {
        std::cout << " Z : ";
        std::cin >> z;
        if (z[0] == '-') {
            z = z.replace(0, 1, "");
            signZ = -1;
        }
        if (std::all_of(z.cbegin(), z.cend(), isdigit) && z.size() > 0) {
            m_targetPos_output.data.z = 0.001 * signZ * std::stod(z);
            zFlag = true;
        }
    }
    if (xFlag && yFlag && zFlag) {
        m_targetPos_outputOut.write();
    }
    else {
        std::cout << "Canceled " << std::endl;
        xFlag = false;
        yFlag = false;
        zFlag = false;
    }

  return RTC::RTC_OK;
}

/*
RTC::ReturnCode_t RobotArmCUI::onAborting(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t RobotArmCUI::onError(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t RobotArmCUI::onReset(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t RobotArmCUI::onStateUpdate(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t RobotArmCUI::onRateChanged(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/



extern "C"
{
 
  void RobotArmCUIInit(RTC::Manager* manager)
  {
    coil::Properties profile(robotarmcui_spec);
    manager->registerFactory(profile,
                             RTC::Create<RobotArmCUI>,
                             RTC::Delete<RobotArmCUI>);
  }
  
};


