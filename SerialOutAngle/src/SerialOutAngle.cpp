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
bool Ret;
BYTE data = 0;
int angU = 0;
int angL = 0;
int angS = 0;

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
		angU = m_angle_input.data[0];
		angL = m_angle_input.data[1];
		angS = m_angle_input.data[2];

		for (int i = 0; i < 3; i++) {
			//ポートをオープン
			char name[50] = {};
			for (int i = 0; i < 50; i++) {
				if (i < m_portName.length())name[i] = m_portName[i];
				else name[i] = NULL;
			}
			arduino = CreateFile(_T(name), GENERIC_WRITE, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
			if (arduino == INVALID_HANDLE_VALUE) {
				printf("PORT COULD NOT OPEN\n");
				//system("PAUSE");
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
			case 0:data = angU; break;
			case 1:data = angL; break;
			case 2:data = angS; break;
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


