// -*- C++ -*-
/*!
 * @file  RobotArmGUI.h
 * @brief ModuleDescription
 * @date  $Date$
 *
 * $Id$
 */

#ifndef ROBOTARMGUI_H
#define ROBOTARMGUI_H

#include <rtm/idl/BasicDataTypeSkel.h>
#include <rtm/idl/ExtendedDataTypesSkel.h>
#include <rtm/idl/InterfaceDataTypesSkel.h>

// Service implementation headers
// <rtc-template block="service_impl_h">

// </rtc-template>

// Service Consumer stub headers
// <rtc-template block="consumer_stub_h">
#include "BasicDataTypeStub.h"

// </rtc-template>

#include <rtm/Manager.h>
#include <rtm/DataFlowComponentBase.h>
#include <rtm/CorbaPort.h>
#include <rtm/DataInPort.h>
#include <rtm/DataOutPort.h>

/*!
 * @class RobotArmGUI
 * @brief ModuleDescription
 *
 */
class RobotArmGUI
  : public RTC::DataFlowComponentBase
{
 public:
  /*!
   * @brief constructor
   * @param manager Maneger Object
   */
  RobotArmGUI(RTC::Manager* manager);

  /*!
   * @brief destructor
   */
  ~RobotArmGUI();

  // <rtc-template block="public_attribute">
  
  // </rtc-template>

  // <rtc-template block="public_operation">
  
  // </rtc-template>

  /***
   *
   * The initialize action (on CREATED->ALIVE transition)
   *
   * @return RTC::ReturnCode_t
   * 
   * 
   */
   virtual RTC::ReturnCode_t onInitialize();

  /***
   *
   * The finalize action (on ALIVE->END transition)
   *
   * @return RTC::ReturnCode_t
   * 
   * 
   */
  // virtual RTC::ReturnCode_t onFinalize();

  /***
   *
   * The startup action when ExecutionContext startup
   *
   * @param ec_id target ExecutionContext Id
   *
   * @return RTC::ReturnCode_t
   * 
   * 
   */
  // virtual RTC::ReturnCode_t onStartup(RTC::UniqueId ec_id);

  /***
   *
   * The shutdown action when ExecutionContext stop
   *
   * @param ec_id target ExecutionContext Id
   *
   * @return RTC::ReturnCode_t
   * 
   * 
   */
  // virtual RTC::ReturnCode_t onShutdown(RTC::UniqueId ec_id);

  /***
   *
   * The activated action (Active state entry action)
   *
   * @param ec_id target ExecutionContext Id
   *
   * @return RTC::ReturnCode_t
   * 
   * 
   */
   virtual RTC::ReturnCode_t onActivated(RTC::UniqueId ec_id);

  /***
   *
   * The deactivated action (Active state exit action)
   *
   * @param ec_id target ExecutionContext Id
   *
   * @return RTC::ReturnCode_t
   * 
   * 
   */
   virtual RTC::ReturnCode_t onDeactivated(RTC::UniqueId ec_id);

  /***
   *
   * The execution action that is invoked periodically
   *
   * @param ec_id target ExecutionContext Id
   *
   * @return RTC::ReturnCode_t
   * 
   * 
   */
   virtual RTC::ReturnCode_t onExecute(RTC::UniqueId ec_id);

  /***
   *
   * The aborting action when main logic error occurred.
   *
   * @param ec_id target ExecutionContext Id
   *
   * @return RTC::ReturnCode_t
   * 
   * 
   */
  // virtual RTC::ReturnCode_t onAborting(RTC::UniqueId ec_id);

  /***
   *
   * The error action in ERROR state
   *
   * @param ec_id target ExecutionContext Id
   *
   * @return RTC::ReturnCode_t
   * 
   * 
   */
  // virtual RTC::ReturnCode_t onError(RTC::UniqueId ec_id);

  /***
   *
   * The reset action that is invoked resetting
   *
   * @param ec_id target ExecutionContext Id
   *
   * @return RTC::ReturnCode_t
   * 
   * 
   */
  // virtual RTC::ReturnCode_t onReset(RTC::UniqueId ec_id);
  
  /***
   *
   * The state update action that is invoked after onExecute() action
   *
   * @param ec_id target ExecutionContext Id
   *
   * @return RTC::ReturnCode_t
   * 
   * 
   */
  // virtual RTC::ReturnCode_t onStateUpdate(RTC::UniqueId ec_id);

  /***
   *
   * The action that is invoked when execution context's rate is changed
   *
   * @param ec_id target ExecutionContext Id
   *
   * @return RTC::ReturnCode_t
   * 
   * 
   */
  // virtual RTC::ReturnCode_t onRateChanged(RTC::UniqueId ec_id);


 protected:
  // <rtc-template block="protected_attribute">
  
  // </rtc-template>

  // <rtc-template block="protected_operation">
  
  // </rtc-template>

  // Configuration variable declaration
  // <rtc-template block="config_declare">
  /*!
   * 
   * - Name:  upperArmLength
   * - DefaultValue: 300.0
   */
  double m_upperArmLength;
  /*!
   * 
   * - Name:  lowerArmLength
   * - DefaultValue: 300.0
   */
  double m_lowerArmLength;
  /*!
   * 
   * - Name:  outerLimitRadius
   * - DefaultValue: 500.0
   */
  double m_outerLimitRadius;
  /*!
   * 
   * - Name:  innerLimitRadius
   * - DefaultValue: 500.0
   */
  double m_innerLimitRadius;
  /*!
   * 
   * - Name:  showSideView
   * - DefaultValue: 1
   */
  int m_showSideView;
  /*!
   * 
   * - Name:  showCoordinates
   * - DefaultValue: 1
   */
  int m_showCoordinates;
  /*!
   * 
   * - Name:  showCoordinateAxes
   * - DefaultValue: 1
   */
  int m_showCoordinateAxes;
  /*!
   * 
   * - Name:  auxiliaryLineInterval
   * - DefaultValue: 45.0
   */
  double m_auxiliaryLineInterval;
  /*!
   * 
   * - Name:  auxiliaryArcInterval
   * - DefaultValue: 100.0
   */
  double m_auxiliaryArcInterval;
  /*!
   * 
   * - Name:  wheelRate
   * - DefaultValue: 10.0
   */
  double m_wheelRate;
  /*!
   * 
   * - Name:  switchWheelDirection
   * - DefaultValue: 0
   */
  int m_switchWheelDirection;
  /*!
   * 
   * - Name:  accentColor_R
   * - DefaultValue: 255
   */
  int m_accentColor_R;
  /*!
   * 
   * - Name:  accentColor_G
   * - DefaultValue: 0
   */
  int m_accentColor_G;
  /*!
   * 
   * - Name:  accentColor_B
   * - DefaultValue: 0
   */
  int m_accentColor_B;
  /*!
   * 
   * - Name:  backgroundBrightness
   * - DefaultValue: 0
   */
  int m_backgroundBrightness;
  /*!
   * 
   * - Name:  arcBrightness
   * - DefaultValue: 50
   */
  int m_arcBrightness;
  /*!
   * 
   * - Name:  showAutoButton
   * - DefaultValue: 1
   */
  int m_showAutoButton;
  /*!
   * 
   * - Name:  showCustomButton
   * - DefaultValue: 0
   */
  int m_showCustomButton;
  /*!
   * 
   * - Name:  custom_name
   * - DefaultValue: custom
   */
  std::string m_custom_name;
  /*!
   * 
   * - Name:  custom_alternateOperation
   * - DefaultValue: 0
   */
  int m_custom_alternateOperation;
  /*!
   * 
   * - Name:  custom_linkWithRightClick
   * - DefaultValue: 0
   */
  int m_custom_linkWithRightClick;
  /*!
   * 
   * - Name:  custom_pushVal
   * - DefaultValue: 1
   */
  int m_custom_pushVal;
  /*!
   * 
   * - Name:  custom_pressVal
   * - DefaultValue: 2
   */
  int m_custom_pressVal;
  /*!
   * 
   * - Name:  custom_releaseVal
   * - DefaultValue: 3
   */
  int m_custom_releaseVal;
  /*!
   * 
   * - Name:  custom_showInputVal
   * - DefaultValue: 0
   */
  int m_custom_showInputVal;

  // </rtc-template>

  // DataInPort declaration
  // <rtc-template block="inport_declare">
  RTC::TimedDoubleSeq m_targetPos_input;
  /*!
   */
  RTC::InPort<RTC::TimedDoubleSeq> m_targetPos_inputIn;
  RTC::TimedLong m_customVal_input;
  /*!
   */
  RTC::InPort<RTC::TimedLong> m_customVal_inputIn;
  RTC::TimedDoubleSeq m_position_input;
  /*!
   */
  RTC::InPort<RTC::TimedDoubleSeq> m_position_inputIn;
  
  // </rtc-template>


  // DataOutPort declaration
  // <rtc-template block="outport_declare">
  RTC::TimedLong m_autoSignal_output;
  /*!
   */
  RTC::OutPort<RTC::TimedLong> m_autoSignal_outputOut;
  RTC::TimedLong m_customSignal_output;
  /*!
   */
  RTC::OutPort<RTC::TimedLong> m_customSignal_outputOut;
  RTC::TimedDoubleSeq m_angle_output;
  /*!
   */
  RTC::OutPort<RTC::TimedDoubleSeq> m_angle_outputOut;
  RTC::TimedDoubleSeq m_targetPos_output;
  /*!
   */
  RTC::OutPort<RTC::TimedDoubleSeq> m_targetPos_outputOut;
  
  // </rtc-template>

  // CORBA Port declaration
  // <rtc-template block="corbaport_declare">
  
  // </rtc-template>

  // Service declaration
  // <rtc-template block="service_declare">
  
  // </rtc-template>

  // Consumer declaration
  // <rtc-template block="consumer_declare">
  
  // </rtc-template>

 private:
  // <rtc-template block="private_attribute">
  
  // </rtc-template>

  // <rtc-template block="private_operation">
  
  // </rtc-template>

};


extern "C"
{
  DLL_EXPORT void RobotArmGUIInit(RTC::Manager* manager);
};

#endif // ROBOTARMGUI_H
