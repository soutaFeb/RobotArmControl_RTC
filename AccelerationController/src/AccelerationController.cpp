// -*- C++ -*-
/*!
 * @file  AccelerationController.cpp
 * @brief ModuleDescription
 * @date $Date$
 *
 * $Id$
 */

#include "AccelerationController.h"

 //２点間距離を求める関数
double Dist(double x1, double y1, double z1, double x2, double y2, double z2) {
    return sqrt(pow((x1 - x2), 2) + pow(y1 - y2, 2) + pow(z1 - z2, 2));
}

double targetPx = 0.0;
double targetPy = 0.0;
double targetPz = 0.0;
double px = 0.0;
double py = 0.0;
double pz = 0.0;

double speed = 0.0;

// Module specification
// <rtc-template block="module_spec">
static const char* accelerationcontroller_spec[] =
  {
    "implementation_id", "AccelerationController",
    "type_name",         "AccelerationController",
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
AccelerationController::AccelerationController(RTC::Manager* manager)
    // <rtc-template block="initializer">
  : RTC::DataFlowComponentBase(manager),
    m_targetPos_inputIn("targetPos_input", m_targetPos_input),
    m_position_outputOut("position_output", m_position_output)

    // </rtc-template>
{
    AccelerationController::m_accel = 0.0;
    AccelerationController::m_maxSpeed = 0.0;
}

/*!
 * @brief destructor
 */
AccelerationController::~AccelerationController()
{
}



RTC::ReturnCode_t AccelerationController::onInitialize()
{
  // Registration: InPort/OutPort/Service
  // <rtc-template block="registration">
  // Set InPort buffers
  addInPort("targetPos_input", m_targetPos_inputIn);
  
  // Set OutPort buffer
  addOutPort("position_output", m_position_outputOut);
  
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
RTC::ReturnCode_t AccelerationController::onFinalize()
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t AccelerationController::onStartup(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t AccelerationController::onShutdown(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/


RTC::ReturnCode_t AccelerationController::onActivated(RTC::UniqueId ec_id)
{
    while (1) {
        if (m_targetPos_inputIn.isNew()) {
            m_targetPos_inputIn.read();
            px = m_targetPos_input.data[0];
            py = m_targetPos_input.data[1];
            pz = m_targetPos_input.data[2];
            break;
        }
    }

  return RTC::RTC_OK;
}


RTC::ReturnCode_t AccelerationController::onDeactivated(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t AccelerationController::onExecute(RTC::UniqueId ec_id)
{
    m_targetPos_input.data.length(3);

    if (m_targetPos_inputIn.isNew()) {
        m_targetPos_inputIn.read();
        targetPx = m_targetPos_input.data[0];
        targetPy = m_targetPos_input.data[1];
        targetPz = m_targetPos_input.data[2];

        double stopLength = 0;//現在の速度から逆方向に加速度をかけて止まるまでに進む距離
        double S = speed;//target方向への現在の速度
        while (S > m_accel) {
            stopLength += S;
            S -= m_accel;
        }
        double targetDist2D = Dist(px, py, pz, targetPx, targetPy, targetPz);
        if (targetDist2D < speed) {
            speed = 0;
            px = targetPx;
            py = targetPy;
            pz = targetPz;
        }
        if (stopLength > targetDist2D - speed)speed -= m_accel;
        if (stopLength < targetDist2D - speed)speed += m_accel;

        //最大速度を設定
        if (speed > m_maxSpeed)speed = m_maxSpeed;

        double angleXY = atan2(targetPy - py, targetPx - px);
        double angleZ = atan2(targetPz - pz, Dist(targetPx, targetPy, 0, px, py, 0));

        px += speed * cos(angleXY) * abs(cos(angleZ));
        py += speed * sin(angleXY) * abs(cos(angleZ));
        pz += speed * sin(angleZ);

        m_position_output.data.length(3);
        m_position_output.data[0] = px;
        m_position_output.data[1] = py;
        m_position_output.data[2] = pz;
        m_position_outputOut.write();

    }

  return RTC::RTC_OK;
}

/*
RTC::ReturnCode_t AccelerationController::onAborting(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t AccelerationController::onError(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t AccelerationController::onReset(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t AccelerationController::onStateUpdate(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t AccelerationController::onRateChanged(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/



extern "C"
{
 
  void AccelerationControllerInit(RTC::Manager* manager)
  {
    coil::Properties profile(accelerationcontroller_spec);
    manager->registerFactory(profile,
                             RTC::Create<AccelerationController>,
                             RTC::Delete<AccelerationController>);
  }
  
};


