// -*- C++ -*-
/*!
 * @file  SerialOutAngle.cpp
 * @brief ModuleDescription
 * @date $Date$
 *
 * $Id$
 */

#include "SerialOutAngle.h"
#include <stdio.h>
#include <stdlib.h>
#include <tchar.h>

HANDLE arduino;
BYTE data = 0;
int angU_upper = 0;
int angU_lower = 0;
int angL_upper = 0;
int angL_lower = 0;
int angS_upper = 0;
int angS_lower = 0;

// Module specification
// <rtc-template block="module_spec">
static const char* serialoutangle_spec[] =
  {
    "implementation_id", "SerialOutAngle",
    "type_name",         "SerialOutAngle",
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
    "conf.default.portName", "COM1",

    // Widget
    "conf.__widget__.portName", "text",
    // Constraints

    "conf.__type__.portName", "string",

    ""
  };
// </rtc-template>

/*!
 * @brief constructor
 * @param manager Maneger Object
 */
SerialOutAngle::SerialOutAngle(RTC::Manager* manager)
    // <rtc-template block="initializer">
  : RTC::DataFlowComponentBase(manager),
    m_angle_inputIn("angle_input", m_angle_input)

    // </rtc-template>
{
}

/*!
 * @brief destructor
 */
SerialOutAngle::~SerialOutAngle()
{
}



RTC::ReturnCode_t SerialOutAngle::onInitialize()
{
  // Registration: InPort/OutPort/Service
  // <rtc-template block="registration">
  // Set InPort buffers
  addInPort("angle_input", m_angle_inputIn);
  
  // Set OutPort buffer
  
  // Set service provider to Ports
  
  // Set service consumers to Ports
  
  // Set CORBA Service Ports
  
  // </rtc-template>

  // <rtc-template block="bind_config">
  // Bind variables and configuration variable
  bindParameter("portName", m_portName, "COM1");
  // </rtc-template>

  std::cout << "SerialOutAngle ready!" << std::endl;
  
  return RTC::RTC_OK;
}

/*
RTC::ReturnCode_t SerialOutAngle::onFinalize()
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t SerialOutAngle::onStartup(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t SerialOutAngle::onShutdown(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/


RTC::ReturnCode_t SerialOutAngle::onActivated(RTC::UniqueId ec_id)
{

  return RTC::RTC_OK;
}


RTC::ReturnCode_t SerialOutAngle::onDeactivated(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t SerialOutAngle::onExecute(RTC::UniqueId ec_id)
{
	m_angle_input.data.length(3);
	if (m_angle_inputIn.isNew()) {
		m_angle_inputIn.read();
		angU_upper = int(m_angle_input.data[0] / 10);
		angL_upper = int(m_angle_input.data[1] / 10);
		angS_upper = int(m_angle_input.data[2] / 10);
		angU_lower = int(m_angle_input.data[0] * 10) % 100;
		angL_lower = int(m_angle_input.data[1] * 10) % 100;
		angS_lower = int(m_angle_input.data[2] * 10) % 100;

		for (int i = 0; i < 6; i++) {
			//ポートをオープン
			char name[50] = {};
			for (int i = 0; i < 50; i++) {
				if (i < m_portName.length())name[i] = m_portName[i];
				else name[i] = NULL;
			}
			arduino = CreateFile(_T(name), GENERIC_WRITE, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
			if (arduino == INVALID_HANDLE_VALUE) {
				printf("Port could not open...\n");
				RTC::RTC_ERROR;
			}

			//送受信バッファ初期化
			SetupComm(arduino, 1024, 1024);
			PurgeComm(arduino, PURGE_TXABORT | PURGE_RXABORT | PURGE_TXCLEAR | PURGE_RXCLEAR);

			//基本通信条件の設定
			DCB dcb;
			GetCommState(arduino, &dcb);
			dcb.DCBlength = sizeof(DCB);
			dcb.BaudRate = 9600;
			dcb.fBinary = TRUE;
			dcb.ByteSize = 8;
			dcb.fParity = NOPARITY;
			dcb.StopBits = ONESTOPBIT;

			SetCommState(arduino, &dcb);

			switch (i) {
			case 0:data = angU_upper; break;
			case 1:data = angU_lower; break;
			case 2:data = angL_upper; break;
			case 3:data = angL_lower; break; 
			case 4:data = angS_upper; break;
			case 5:data = angS_lower; break;
			}

			//送信
			DWORD dwSendSize;
			WriteFile(arduino, &data, sizeof(data), &dwSendSize, NULL);

			CloseHandle(arduino);

		}
	}

  return RTC::RTC_OK;
}

/*
RTC::ReturnCode_t SerialOutAngle::onAborting(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t SerialOutAngle::onError(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t SerialOutAngle::onReset(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t SerialOutAngle::onStateUpdate(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t SerialOutAngle::onRateChanged(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/



extern "C"
{
 
  void SerialOutAngleInit(RTC::Manager* manager)
  {
    coil::Properties profile(serialoutangle_spec);
    manager->registerFactory(profile,
                             RTC::Create<SerialOutAngle>,
                             RTC::Delete<SerialOutAngle>);
  }
  
};


