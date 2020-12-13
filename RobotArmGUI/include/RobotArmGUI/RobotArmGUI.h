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
#include "ExtendedDataTypesStub.h"

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
   * - DefaultValue: 100.0
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
   * - Name:  button1_name
   * - DefaultValue: Auto
   */
  std::string m_button1_name;
  /*!
   * 
   * - Name:  button1_pressName
   * - DefaultValue: Running
   */
  std::string m_button1_pressName;
  /*!
   * 
   * - Name:  button1_choicesNum
   * - DefaultValue: 3
   */
  int m_button1_choicesNum;
  /*!
   * 
   * - Name:  button1_alternateOperation
   * - DefaultValue: 1
   */
  int m_button1_alternateOperation;
  /*!
   * 
   * - Name:  button1_linkWithRightClick
   * - DefaultValue: 0
   */
  int m_button1_linkWithRightClick;
  /*!
   * 
   * - Name:  button2_name
   * - DefaultValue: none
   */
  std::string m_button2_name;
  /*!
   * 
   * - Name:  button2_pressName
   * - DefaultValue: pressName
   */
  std::string m_button2_pressName;
  /*!
   * 
   * - Name:  button2_choicesNum
   * - DefaultValue: 1
   */
  int m_button2_choicesNum;
  /*!
   * 
   * - Name:  button2_alternateOperation
   * - DefaultValue: 0
   */
  int m_button2_alternateOperation;
  /*!
   * 
   * - Name:  button2_linkWithRightClick
   * - DefaultValue: 0
   */
  int m_button2_linkWithRightClick;

  // </rtc-template>

  // DataInPort declaration
  // <rtc-template block="inport_declare">
  RTC::TimedBoolean m_button1_input;
  /*!
   */
  RTC::InPort<RTC::TimedBoolean> m_button1_inputIn;
  RTC::TimedBoolean m_button2_input;
  /*!
   */
  RTC::InPort<RTC::TimedBoolean> m_button2_inputIn;
  RTC::TimedLong m_displayVal_input;
  /*!
   */
  RTC::InPort<RTC::TimedLong> m_displayVal_inputIn;
  RTC::TimedPoint3D m_targetPos_input;
  /*!
   * - Unit: m
   */
  RTC::InPort<RTC::TimedPoint3D> m_targetPos_inputIn;
  RTC::TimedPoint3D m_position_input;
  /*!
   * - Unit: m
   */
  RTC::InPort<RTC::TimedPoint3D> m_position_inputIn;
  
  // </rtc-template>


  // DataOutPort declaration
  // <rtc-template block="outport_declare">
  RTC::TimedLong m_button1_output;
  /*!
   */
  RTC::OutPort<RTC::TimedLong> m_button1_outputOut;
  RTC::TimedLong m_button2_output;
  /*!
   */
  RTC::OutPort<RTC::TimedLong> m_button2_outputOut;
  RTC::TimedDoubleSeq m_angle_output;
  /*!
   */
  RTC::OutPort<RTC::TimedDoubleSeq> m_angle_outputOut;
  RTC::TimedPoint3D m_targetPos_output;
  /*!
   * - Unit: m
   */
  RTC::OutPort<RTC::TimedPoint3D> m_targetPos_outputOut;
  
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
