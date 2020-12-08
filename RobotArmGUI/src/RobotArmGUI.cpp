// -*- C++ -*-
/*!
 * @file  RobotArmGUI.cpp
 * @brief ModuleDescription
 * @date $Date$
 *
 * $Id$
 */

#include "RobotArmGUI.h"
#include <DxLib.h>
#include <stdio.h>
#include <math.h>
#include <cmath>

//渡された数値をある範囲から別の範囲に変更する関数
double Map(double value, double start1, double end1, double start2, double end2) {
    return start2 + (end2 - start2) * ((value - start1) / (end1 - start1));
}

//２点間距離を求める関数
double Dist(double x1, double y1, double z1, double x2, double y2, double z2) {
    return sqrt(pow((x1 - x2), 2) + pow(y1 - y2, 2) + pow(z1 - z2, 2));
}

const int jointSize = 30;//関節の大きさ（ピクセル）

const int windowWidth = 640;
const int arcRadius = 300;
const int borderHeight = 10;//境界線の太さ
const int blankSpace = 50;//境界線から操作部（半円部分）までの空間の距離
const int sideViewHeight = arcRadius;//windowWidth * 0.5;
int windowHeight = 0;

//GUI上での各関節位置など
double lengthMag = 0.0;
double outerRadius = 0.0;
double innerRadius = 0.0;
double upperLength = 0.0;
double lowerLength = 0.0;
double targetP2x = 0.0;
double targetP2y = 0.0;
double targetP2z = 0.0;
double p2x = 0.0, p2y = 0.0, p2z = 0.0;
double p1x = 0.0, p1y = 0.0, p1z = 0.0;
double p0x = 0.0, p0y = 0.0, p0z = 0.0;
double angU = 0.0, angL = 0.0, angS = 0.0;

double sideTargetX = 0.0;
double sideTargetY = 0.0;
double side0x = 0.0, side0y = 0.0;
double side1x = 0.0, side1y = 0.0;
double side2x = 0.0, side2y = 0.0;

double trueP0x = 0.0, trueP0y = 0.0, trueP0z = 0.0;

const double PI = acos(-1);

int mouseX = 0, mouseY = 0, mouseWheel = 0;
const int ellipseDiff = 20;
const int targetSize = jointSize + ellipseDiff;
bool topDragg = false;
bool topDraggFlag = true;
bool sideDragg = false;
bool sideDraggFlag = true;
double draggDistX = 0.0;//ドラッグした際のマウスポインタと目標円中心の差（x方向）
double draggDistY = 0.0;//ドラッグした際のマウスポインタと目標円中心の差（y方向）

int autoStatus = 0;
int maxAutoStatus = 0;
bool autoClickFlag = true;
bool autoPush = false;
int autoX = 0;
int autoY = 0;
int autoRadius = 0;

int customOutputStatus = 0;
bool customClickFlag = true;
bool customPush = false;
int customX = 0;
int customY = 0;
int customRadius = 0;
bool customPress = false;//オルタネイト動作用

double realMag;

// Module specification
// <rtc-template block="module_spec">
static const char* robotarmgui_spec[] =
  {
    "implementation_id", "RobotArmGUI",
    "type_name",         "RobotArmGUI",
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
    "conf.default.showAutoButton", "1",
    "conf.default.showCustomButton", "0",
    "conf.default.custom_name", "custom",
    "conf.default.custom_alternateOperation", "0",
    "conf.default.custom_linkWithRightClick", "0",
    "conf.default.custom_pushVal", "1",
    "conf.default.custom_pressVal", "2",
    "conf.default.custom_releaseVal", "3",
    "conf.default.custom_showInputVal", "0",

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
    "conf.__widget__.showAutoButton", "text",
    "conf.__widget__.showCustomButton", "text",
    "conf.__widget__.custom_name", "text",
    "conf.__widget__.custom_alternateOperation", "text",
    "conf.__widget__.custom_linkWithRightClick", "text",
    "conf.__widget__.custom_pushVal", "text",
    "conf.__widget__.custom_pressVal", "text",
    "conf.__widget__.custom_releaseVal", "text",
    "conf.__widget__.custom_showInputVal", "text",
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
    "conf.__type__.showAutoButton", "int",
    "conf.__type__.showCustomButton", "int",
    "conf.__type__.custom_name", "string",
    "conf.__type__.custom_alternateOperation", "int",
    "conf.__type__.custom_linkWithRightClick", "int",
    "conf.__type__.custom_pushVal", "int",
    "conf.__type__.custom_pressVal", "int",
    "conf.__type__.custom_releaseVal", "int",
    "conf.__type__.custom_showInputVal", "int",

    ""
  };
// </rtc-template>

/*!
 * @brief constructor
 * @param manager Maneger Object
 */
RobotArmGUI::RobotArmGUI(RTC::Manager* manager)
    // <rtc-template block="initializer">
  : RTC::DataFlowComponentBase(manager),
    m_targetPos_inputIn("targetPos_input", m_targetPos_input),
    m_customVal_inputIn("customVal_input", m_customVal_input),
    m_position_inputIn("position_input", m_position_input),
    m_autoSignal_outputOut("autoSignal_output", m_autoSignal_output),
    m_customSignal_outputOut("customSignal_output", m_customSignal_output),
    m_angle_outputOut("angle_output", m_angle_output),
    m_targetPos_outputOut("targetPos_output", m_targetPos_output)

    // </rtc-template>
{
    RobotArmGUI::m_upperArmLength = 0.0;
    RobotArmGUI::m_lowerArmLength = 0.0;
    RobotArmGUI::m_outerLimitRadius = 0.0;
    RobotArmGUI::m_innerLimitRadius = 0.0;
    RobotArmGUI::m_showSideView = 0;
    RobotArmGUI::m_showCoordinates = 0;
    RobotArmGUI::m_showCoordinateAxes = 0;
    RobotArmGUI::m_auxiliaryLineInterval = 0;
    RobotArmGUI::m_auxiliaryArcInterval = 0;
    RobotArmGUI::m_wheelRate = 0.0;
    RobotArmGUI::m_switchWheelDirection = 0;
    RobotArmGUI::m_accentColor_R = 0;
    RobotArmGUI::m_accentColor_G = 0;
    RobotArmGUI::m_accentColor_B = 0;
    RobotArmGUI::m_backgroundBrightness = 0;
    RobotArmGUI::m_arcBrightness = 0;
    RobotArmGUI::m_showCustomButton = 0;
    RobotArmGUI::m_custom_name = "";
    RobotArmGUI::m_custom_alternateOperation = 0;
    RobotArmGUI::m_custom_linkWithRightClick = 0;
    RobotArmGUI::m_custom_pushVal = 0;
    RobotArmGUI::m_custom_pressVal = 0;
    RobotArmGUI::m_custom_releaseVal = 0;
    RobotArmGUI::m_custom_showInputVal = 0;
}

/*!
 * @brief destructor
 */
RobotArmGUI::~RobotArmGUI()
{
}



RTC::ReturnCode_t RobotArmGUI::onInitialize()
{
  // Registration: InPort/OutPort/Service
  // <rtc-template block="registration">
  // Set InPort buffers
  addInPort("targetPos_input", m_targetPos_inputIn);
  addInPort("customVal_input", m_customVal_inputIn);
  addInPort("position_input", m_position_inputIn);
  
  // Set OutPort buffer
  addOutPort("autoSignal_output", m_autoSignal_outputOut);
  addOutPort("customSignal_output", m_customSignal_outputOut);
  addOutPort("angle_output", m_angle_outputOut);
  addOutPort("targetPos_output", m_targetPos_outputOut);
  
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
  bindParameter("showAutoButton", m_showAutoButton, "1");
  bindParameter("showCustomButton", m_showCustomButton, "0");
  bindParameter("custom_name", m_custom_name, "custom");
  bindParameter("custom_alternateOperation", m_custom_alternateOperation, "0");
  bindParameter("custom_linkWithRightClick", m_custom_linkWithRightClick, "0");
  bindParameter("custom_pushVal", m_custom_pushVal, "1");
  bindParameter("custom_pressVal", m_custom_pressVal, "2");
  bindParameter("custom_releaseVal", m_custom_releaseVal, "3");
  bindParameter("custom_showInputVal", m_custom_showInputVal, "0");
  // </rtc-template>

  std::cout << "RobotArmGUI ready!" << std::endl;
  
  return RTC::RTC_OK;
}

/*
RTC::ReturnCode_t RobotArmGUI::onFinalize()
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t RobotArmGUI::onStartup(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t RobotArmGUI::onShutdown(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/


RTC::ReturnCode_t RobotArmGUI::onActivated(RTC::UniqueId ec_id)
{
    realMag = (m_upperArmLength + m_lowerArmLength) / arcRadius;

    windowHeight = (m_showSideView * (int)(borderHeight + sideViewHeight)) + blankSpace + arcRadius;
    lengthMag = m_upperArmLength / m_lowerArmLength;
    outerRadius = m_outerLimitRadius / realMag;
    innerRadius = m_innerLimitRadius / realMag;
    upperLength = m_upperArmLength / realMag;
    lowerLength = m_lowerArmLength / realMag;
    targetP2x = (double)(windowWidth * 0.5);
    targetP2y = windowHeight - arcRadius * 0.5;
    targetP2z = arcRadius * 0.25;
    p2x = targetP2x;
    p2y = targetP2y;
    p2z = targetP2z;
    p0x = windowWidth * 0.5;
    p0y = windowHeight;
    p0z = 0.0;

    side0x = windowWidth * 0.75;
    side0y = sideViewHeight - jointSize * 0.5;

    autoX = 48;
    autoY = windowHeight - arcRadius - 2;
    autoRadius = 35;

    customX = autoX + 83;
    customY = windowHeight - arcRadius - 2;
    customRadius = 35;

    //加速度制御コンポーネントに手先の初期座標を送る
    m_targetPos_output.data.x = 0.001 * targetP2x * realMag;
    m_targetPos_output.data.y = 0.001 * targetP2y * realMag;
    m_targetPos_output.data.z = 0.001 * targetP2z * realMag;
    m_targetPos_outputOut.write();

    m_autoSignal_output.data = 0;
    m_autoSignal_outputOut.write();

    //自動制御コンポーネントからデータを受け取る
    if (m_showAutoButton > 0) {
        while (1) {
            if (m_targetPos_inputIn.isNew()) {
                m_targetPos_inputIn.read();
                maxAutoStatus = int(m_targetPos_input.data.x);
                break;
            }
        }
    }

    SetMainWindowText("RobotArmGUI");//タイトルバーの名前を設定
    SetBackgroundColor(m_backgroundBrightness, m_backgroundBrightness, m_backgroundBrightness);
    ChangeWindowMode(TRUE);//非全画面にセット
    SetGraphMode(windowWidth, windowHeight, 32);//画面サイズ指定
    SetOutApplicationLogValidFlag(FALSE);//Log.txtを生成しないように設定
    SetAlwaysRunFlag(TRUE);//ウィンドウが非アクティブ時でも画面が更新されるようにする


    ChangeFontType(DX_FONTTYPE_ANTIALIASING);

    DxLib_Init();

  return RTC::RTC_OK;
}


RTC::ReturnCode_t RobotArmGUI::onDeactivated(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t RobotArmGUI::onExecute(RTC::UniqueId ec_id)
{
    ClearDrawScreen();//裏画面消す
    SetDrawScreen(DX_SCREEN_BACK);//描画先を裏画面に


    //加速度制御コンポーネントからデータを受け取る
    if (m_position_inputIn.isNew()) {
        m_position_inputIn.read();
        p2x = 1000 * m_position_input.data.x / realMag;
        p2y = 1000 * m_position_input.data.y / realMag;
        p2z = 1000 * m_position_input.data.z / realMag;
    }
    side1x = side0x - lowerLength * cos(angL);
    side1y = side0y - p1z;
    side2x = side0x - Dist(p2x, p2y, 0, windowWidth * 0.5, windowHeight, 0);
    side2y = side0y - p2z;
    sideTargetX = side0x - Dist(targetP2x, targetP2y, 0, windowWidth * 0.5, windowHeight, 0);
    sideTargetY = side0y - targetP2z;

    //CUIコンポーネントまたは自動制御コンポーネントからデータを受け取る
    if (m_targetPos_inputIn.isNew()) {
        m_targetPos_inputIn.read();
        if (m_targetPos_input.data.x > 999 && m_targetPos_input.data.y > 999 && m_targetPos_input.data.z > 999) {
            m_autoSignal_output.data = 0;
        }
        else {
            targetP2x = (1000 * m_targetPos_input.data.x) / realMag + windowWidth * 0.5;
            targetP2y = windowHeight - (1000 * m_targetPos_input.data.y) / realMag;
            targetP2z = (1000 * m_targetPos_input.data.z) / realMag;
        }
    }

    GetMousePoint(&mouseX, &mouseY);
    mouseWheel = GetMouseWheelRotVol();
    int mouseInput = GetMouseInput();
    bool mouseLEFT = false;
    bool mouseRIGHT = false;
    if (mouseInput & MOUSE_INPUT_LEFT)mouseLEFT = true;
    if (mouseInput & MOUSE_INPUT_RIGHT)mouseRIGHT = true;

    //ドラッグ処理
    if (topDragg) {//上視点のドラッグ処理
        targetP2x = mouseX - draggDistX;
        targetP2y = mouseY - draggDistY;
    }
    if (sideDragg && m_showSideView) {//横視点のドラッグ処理
        targetP2x = windowWidth * 0.5 + (side0x - mouseX + draggDistX) * cos(angS);
        targetP2y = windowHeight - (side0x - (mouseX - draggDistX)) * sin(angS);
        targetP2z = side0y - (mouseY - draggDistY);
    }
    if (mouseLEFT) {
        if (topDraggFlag && Dist(targetP2x, targetP2y, 0, mouseX, mouseY, 0) < targetSize * 0.5) {
            topDragg = true;
            topDraggFlag = false;
            draggDistX = mouseX - targetP2x;
            draggDistY = mouseY - targetP2y;
        }
        if (sideDraggFlag && Dist(sideTargetX, sideTargetY, 0, mouseX, mouseY, 0) < targetSize * 0.5) {
            sideDragg = true;
            sideDraggFlag = false;
            draggDistX = mouseX - sideTargetX;
            draggDistY = mouseY - sideTargetY;
        }
    }
    if (mouseInput == 0) {
        topDragg = false;
        topDraggFlag = true;
        sideDragg = false;
        sideDraggFlag = true;
    }
    //目標座標と現在の座標が操作範囲外に出ないようにする
    double targetDist = Dist(targetP2x, targetP2y, 0, windowWidth * 0.5, windowHeight, 0);
    if (outerRadius < targetDist) {
        double targetAng = atan2(windowHeight - targetP2y, targetP2x - windowWidth * 0.5);
        targetP2x = windowWidth * 0.5 + outerRadius * cos(targetAng);
        targetP2y = windowHeight - outerRadius * sin(targetAng);
    }
    if (targetDist < innerRadius || targetP2y > windowHeight) {
        if (abs(targetP2x - windowWidth * 0.5) < innerRadius) {
            targetP2y = windowHeight - sqrt(pow(innerRadius, 2) - pow((targetP2x - windowWidth * 0.5), 2));
        }
        else targetP2y = windowHeight;
    }
    double currentDist = Dist(p2x, p2y, 0, windowWidth * 0.5, windowHeight, 0);
    if (outerRadius < currentDist) {
        double currentAng = atan2(windowHeight - p2y, p2x - windowWidth * 0.5);
        p2x = windowWidth * 0.5 + outerRadius * cos(currentAng);
        p2y = windowHeight - outerRadius * sin(currentAng);
    }
    if (currentDist < innerRadius || p2y > windowHeight) {
        if (abs(p2x - windowWidth * 0.5) < innerRadius) {
            p2y = windowHeight - sqrt(pow(innerRadius, 2) - pow((p2x - windowWidth * 0.5), 2));
        }
        else p2y = windowHeight;
    }
    if (Dist(mouseX, mouseY, 0, autoX, autoY, 0) > autoRadius) {//マウスポインタがAutoボタンの上にないときは、マウスホイールでz座標を操作出来る
        targetP2z -= mouseWheel * m_wheelRate / realMag * ((double)m_switchWheelDirection * (-2) + 1);
    }
    double maxTargetP2z = sqrt(pow((upperLength + lowerLength), 2) - pow(sqrt(pow(targetP2x - windowWidth * 0.5, 2) + pow(windowHeight - targetP2y, 2)), 2));
    bool maxZflag = false;
    if (targetP2z < 0)targetP2z = 0;
    if (targetP2z > maxTargetP2z) {
        targetP2z = maxTargetP2z;
        maxZflag = true;
    }

    //各関節角度計算--------------------------------------------------
    double calL = Dist(windowWidth * 0.5, windowHeight, 0, p2x, p2y, p2z);
    double calGamma = asin(p2z / calL);
    double calVal = (pow(calL, 2) + pow(upperLength, 2) - pow(lowerLength, 2)) / (2 * calL);
    double calAlpha = acos((calL - calVal) / lowerLength);
    double calBeta = acos(calVal / upperLength);
    angL = calAlpha + calGamma;
    angU = PI / 2 - (calBeta - calGamma);
    angS = abs(atan2(p2y - p0y, p2x - p0x));
    p1x = p0x + cos(angL) * lowerLength * cos(angS);
    p1y = p0y - (cos(angL) * lowerLength * sin(angS));
    p1z = lowerLength * sin(angL);

    //線の色を設定
    int lineColor = GetColor(m_arcBrightness + 100, m_arcBrightness + 100, m_arcBrightness + 100);
    if (m_arcBrightness > 127)lineColor = GetColor(m_arcBrightness - 100, m_arcBrightness - 100, m_arcBrightness - 100);
    int characterColor = GetColor(m_backgroundBrightness + 100, m_backgroundBrightness + 100, m_backgroundBrightness + 100);
    if (m_backgroundBrightness > 127)characterColor = GetColor(m_backgroundBrightness - 100, m_backgroundBrightness - 100, m_backgroundBrightness - 100);
    int accentColor = GetColor(m_accentColor_R, m_accentColor_G, m_accentColor_B);
    int backgroundColor = GetColor(m_backgroundBrightness, m_backgroundBrightness, m_backgroundBrightness);
    int arcColor = GetColor(m_arcBrightness, m_arcBrightness, m_arcBrightness);

    //Autoボタン
    if (m_showAutoButton > 0) {
        bool autoMouseOn = false;
        if (Dist(mouseX, mouseY, 0, double(autoX), double(autoY), 0) < autoRadius)autoMouseOn = true;
        if (autoMouseOn) {
            if (mouseLEFT && autoClickFlag) {//押した瞬間
                autoPush = true;
                //autoClickFlag = false;
            }
            if (mouseInput == 0 && autoPush) {//離した瞬間
                if (m_autoSignal_output.data == 0)m_autoSignal_output.data = autoStatus;
                else m_autoSignal_output.data = 0;
            }
            if (m_autoSignal_output.data == 0) {
                autoStatus -= mouseWheel;
                if (autoStatus < 1)autoStatus = 1;
                if (autoStatus > maxAutoStatus)autoStatus = maxAutoStatus;
            }
        }
        else if (!autoPush && m_autoSignal_output.data == 0)autoStatus = 1;
        if (mouseLEFT)autoClickFlag = false;
        else {
            autoClickFlag = true;
            autoPush = false;
        }
        if (autoPush)DrawCircle(autoX, autoY, autoRadius, GetColor(int(m_accentColor_R * 0.5), int(m_accentColor_G * 0.5), int(m_accentColor_B * 0.5)), true);//Autoボタン塗りつぶし
        if (m_autoSignal_output.data > 0) {
            if (!autoPush)DrawCircle(autoX, autoY, autoRadius, accentColor, true);//Autoボタン塗りつぶし
            SetFontSize(12);
            DrawFormatString(autoX - 24, autoY - 13, characterColor, "Running");
            SetFontSize(20);
            DrawFormatString(autoX - 24, autoY - 2, characterColor, "data%d", m_autoSignal_output.data);
        }
        else {
            if (autoMouseOn || autoPush) {
                SetFontSize(12);
                DrawFormatString(autoX - 24, autoY - 13, characterColor, "Select");
                SetFontSize(20);
                DrawFormatString(autoX - 24, autoY - 2, characterColor, "data%d", autoStatus);
            }
            else {
                SetFontSize(20);
                DrawFormatString(autoX - 20, autoY - 8, characterColor, "Auto");
            }
        }
        DrawCircleAA(float(autoX), float(autoY), float(autoRadius), 64, characterColor, false, 2.0);//Autoボタン枠線
    }

    //Customボタン
    if (m_showCustomButton == 1) {
        if (customPush || customPress)m_customSignal_output.data = m_custom_pressVal;//押されているとき
        else m_customSignal_output.data = m_custom_pressVal;
        bool customMouseOn = false;
        if (Dist(mouseX, mouseY, 0, double(customX), double(customY), 0) < customRadius)customMouseOn = true;
        if (m_custom_alternateOperation == 0) {//モーメンタリ動作スイッチ
            if (m_custom_linkWithRightClick == 1) {//右クリックと同期
                if (mouseRIGHT && customClickFlag) {//押した瞬間
                    customPush = true;
                    //customClickFlag = false;
                    m_customSignal_output.data = m_custom_pushVal;
                }
                if (mouseInput == 0 && customPush) {//離した瞬間
                    m_customSignal_output.data = m_custom_releaseVal;
                }
            }
            else {//右クリックと同期しない
                if (customMouseOn) {
                    if (mouseLEFT && customClickFlag) {//押した瞬間
                        customPush = true;
                        //customClickFlag = false;
                        m_customSignal_output.data = m_custom_pushVal;
                    }
                    if (mouseInput == 0 && customPush) {//離した瞬間
                        m_customSignal_output.data = m_custom_releaseVal;
                    }
                }
            }
            if (mouseRIGHT)customClickFlag = false;
            else {
                customClickFlag = true;
                customPush = false;
            }
        }
        if (m_custom_alternateOperation == 1) {//オルタネイト動作スイッチ
            if (m_custom_linkWithRightClick == 1) {//右クリックと同期
                if (mouseRIGHT && customClickFlag) {//押した瞬間
                    customPush = true;
                    //customClickFlag = false;
                    m_customSignal_output.data = m_custom_pushVal;
                }
                if (mouseInput == 0 && customPush) {//離した瞬間
                    m_customSignal_output.data = m_custom_releaseVal;
                    customPush = false;
                    if (customPress)customPress = false;
                    else customPress = true;
                }
            }
            else {//右クリックと同期しない
                if (customMouseOn) {
                    if (mouseLEFT && customClickFlag) {//押した瞬間
                        customPush = true;
                        //customClickFlag = false;
                        m_customSignal_output.data = m_custom_pushVal;
                    }
                    if (mouseInput == 0 && customPush) {//離した瞬間
                        m_customSignal_output.data = m_custom_releaseVal;
                        customPush = false;
                        if (customPress)customPress = false;
                        else customPress = true;
                    }
                }
            }
            if (mouseRIGHT)customClickFlag = false;
            else customClickFlag = true;
        }

        if (customPush || customPress)DrawCircle(customX, customY, customRadius, accentColor, true);//Customボタン塗りつぶし
        else DrawCircle(customX, customY, customRadius, backgroundColor, true);//Customボタン塗りつぶし
        if (m_custom_showInputVal) {
            SetFontSize(15);
            DrawFormatString(customX - 15, customY + 10, characterColor, " %d", autoStatus);
        }
        char name[50] = {};
        for (int i = 0; i < 50; i++) {
            if (i < m_custom_name.length())name[i] = m_custom_name[i];
            else name[i] = NULL;
        }
        SetFontSize(18);
        DrawFormatString(customX - 30, customY - 8, characterColor, _T(name));
        DrawCircleAA(float(customX), float(customY), float(customRadius), 64, characterColor, false, 2.0);//Autoボタン枠線
    }

    //自動制御コンポーネントにデータ番号を送る
    m_autoSignal_outputOut.write();

    //Costomボタンの状態を送る
    m_customSignal_outputOut.write();

    //加速度制御コンポーネントに手先の目標座標と現在の座標を送る
    m_targetPos_output.data.x = 0.001 * targetP2x * realMag;
    m_targetPos_output.data.y = 0.001 * targetP2y * realMag;
    m_targetPos_output.data.z = 0.001 * targetP2z * realMag;
    m_targetPos_outputOut.write();

    //シリアル通信コンポーネントに角度情報を送る
    m_angle_output.data.length(3);
    m_angle_output.data[0] = angU * 180 / PI;
    m_angle_output.data[1] = angL * 180 / PI;
    m_angle_output.data[2] = angS * 180 / PI;
    m_angle_outputOut.write();


    //手先座標表示
    if (m_showCoordinates == 1) {
        trueP0x = (p2x - windowWidth * 0.5) * realMag;
        trueP0y = (windowHeight - p2y) * realMag;
        trueP0z = p2z * realMag;
        DrawRoundRectAA(float(windowWidth - 115), float(m_showSideView * (sideViewHeight + borderHeight) + 13), float(windowWidth - 15), float(m_showSideView * (sideViewHeight + borderHeight) + 93), 5.0, 5.0, 16, characterColor, false);
        SetFontSize(20);
        DrawFormatString(windowWidth - 105, m_showSideView * (sideViewHeight + borderHeight) + 23, characterColor, "X :%4.0f", trueP0x);
        DrawFormatString(windowWidth - 105, m_showSideView * (sideViewHeight + borderHeight) + 43, characterColor, "Y :%4.0f", trueP0y);
        DrawFormatString(windowWidth - 105, m_showSideView * (sideViewHeight + borderHeight) + 63, characterColor, "Z :%4.0f", trueP0z);
    }

    //図形表示（横からの視点）
    if (m_showSideView == 1) {
        side0x = windowWidth * 0.75;
        side0y = sideViewHeight - jointSize * 0.5;
        side1x = side0x - lowerLength * cos(angL);
        side1y = side0y - p1z;
        side2x = side0x - Dist(windowWidth * 0.5, windowHeight, 0, p2x, p2y, 0);
        side2y = side0y - p2z;
        DrawBox(int(side0x - arcRadius), 0, int(side0x), int(sideViewHeight), arcColor, true);
        if (m_auxiliaryArcInterval > 0) {
            for (int i = 0; i <= arcRadius / (m_auxiliaryArcInterval / realMag); i++) {//補助円
                DrawLineAA(float(side0x - m_auxiliaryArcInterval / realMag * i), 0, float(side0x - m_auxiliaryArcInterval / realMag * i), float(sideViewHeight), lineColor);//補助円（横視点）
            }
        }
        DrawLineAA(float(side0x - innerRadius), 0, float(side0x - innerRadius), float(sideViewHeight), accentColor);//動作範囲上限半径
        DrawLineAA(float(side0x - outerRadius), 0, float(side0x - outerRadius), float(sideViewHeight), accentColor);//動作範囲下限半径
        DrawLineAA(float(side0x), float(side0y), float(side1x), float(side1y), lineColor, 5);//下腕
        DrawLineAA(float(side1x), float(side1y), float(side2x), float(side2y), lineColor, 5);//上腕
        DrawCircleAA(float(side0x), float(side0y), float(jointSize * 0.5 - 1), 32, lineColor, true);
        DrawCircleAA(float(side1x), float(side1y), float(jointSize * 0.5 - 1), 32, lineColor, true);
        DrawCircleAA(float(side2x), float(side2y), float(jointSize * 0.5 - 1), 32, accentColor, true);
        DrawBox(0, int(sideViewHeight), windowWidth, int(sideViewHeight + borderHeight), characterColor, true);//上視点と横視点の境界線
        DrawCircleAA(float(sideTargetX), float(sideTargetY), float(targetSize * 0.5), 32, accentColor, false);//目標手先位置の円
    }

    //図形表示（上からの視点）
    DrawCircleAA(float(windowWidth * 0.5), float(windowHeight), float(arcRadius), 128, arcColor, true);//操作部（半円）
    DrawCircleAA(float(windowWidth * 0.5), float(windowHeight), float(arcRadius), 128, lineColor, false);//操作部（半円）枠線
    if (m_showCoordinateAxes == 1) {
        DrawFormatString(int(windowWidth * 0.5 + arcRadius + 5), int(windowHeight - 30), lineColor, "x");
        DrawFormatString(int(windowWidth * 0.5 + 10), int(windowHeight - arcRadius - 30), lineColor, "y");
        DrawTriangleAA(float(windowWidth * 0.5 + arcRadius + 20), float(windowHeight), float(windowWidth * 0.5 + arcRadius + 5), float(windowHeight), float(windowWidth * 0.5 + arcRadius + 5), float(windowHeight - 7 - 1), lineColor, true);// x軸矢印
        DrawTriangleAA(float(windowWidth * 0.5), float(windowHeight - arcRadius - 20), float(windowWidth * 0.5 + 7), float(windowHeight - arcRadius - 5), float(windowWidth * 0.5 - 7), float(windowHeight - arcRadius - 5), lineColor, true);//y軸矢印
        DrawLineAA(float(windowWidth * 0.5 - arcRadius - 10), float(windowHeight - 2), float(windowWidth * 0.5 + arcRadius + 10), float(windowHeight - 2), lineColor, 3);//x軸
        DrawLineAA(float(windowWidth * 0.5), float(windowHeight), float(windowWidth * 0.5), float(windowHeight - arcRadius - 10), lineColor, 3);//y軸
    }
    if (m_auxiliaryLineInterval > 0) {
        for (int i = 0; i <= 90 / m_auxiliaryLineInterval; i++) {//補助線
            double lineEdgeX = arcRadius * sin(m_auxiliaryLineInterval * PI / 180 * i);
            double lineEdgeY = arcRadius * cos(m_auxiliaryLineInterval * PI / 180 * i);
            DrawLineAA(float(windowWidth * 0.5), float(windowHeight), float(windowWidth * 0.5 + lineEdgeX), float(windowHeight - lineEdgeY), lineColor);
            DrawLineAA(float(windowWidth * 0.5), float(windowHeight), float(windowWidth * 0.5 - lineEdgeX), float(windowHeight - lineEdgeY), lineColor);
        }
    }
    if (m_auxiliaryArcInterval > 0) {
        for (int i = 1; i <= arcRadius / (m_auxiliaryArcInterval / realMag); i++) {//補助円
            DrawCircleAA(float(windowWidth * 0.5), float(windowHeight), float(m_auxiliaryArcInterval / realMag * i), 128, lineColor, false);
        }
    }

    DrawCircleAA(float(windowWidth * 0.5), float(windowHeight), float(outerRadius), 128, accentColor, false);//動作範囲上限半径
    DrawCircleAA(float(windowWidth * 0.5), float(windowHeight), float(innerRadius), 128, accentColor, false);//動作範囲下限半径
    DrawLineAA(float(p0x), float(p0y), float(p2x), float(p2y), lineColor, 5);//アームの線
    DrawCircleAA(float(targetP2x), float(targetP2y), float(targetSize * 0.5), 32, accentColor, false);//目標手先位置の円
    DrawLineAA(float(targetP2x - targetSize * 0.6), float(targetP2y), float(targetP2x + targetSize * 0.6), float(targetP2y), accentColor);
    DrawLineAA(float(targetP2x), float(targetP2y + targetSize * 0.6), float(targetP2x), float(targetP2y - targetSize * 0.6), accentColor);
    DrawCircleAA(float(targetP2x), float(targetP2y), float((jointSize + (ellipseDiff * targetP2z / (upperLength + lowerLength))) * 0.5), 32, accentColor, false);//高さ確認用円
    DrawCircleAA(float(p2x), float(p2y), float(jointSize * 0.5 - 1), 32, accentColor, true);//現在の手先位置の円
    DrawCircleAA(float(p1x), float(p1y), float(jointSize * 0.5 - 1), 32, lineColor, true);
    DrawCircleAA(float(p0x), float(p0y), float(jointSize * 0.5 - 1), 32, lineColor, true);

    //交点合わせ機能
    if (CheckHitKey(KEY_INPUT_LSHIFT) || CheckHitKey(KEY_INPUT_RSHIFT)) {
        double intersectionX = 10000.0;
        double intersectionY = 10000.0;
        if (m_auxiliaryArcInterval > 0 && m_auxiliaryLineInterval > 0) {
            for (int i = 1; i <= arcRadius / (m_auxiliaryArcInterval / realMag); i++) {//補助円
                for (int j = 0; j <= 90 / m_auxiliaryLineInterval; j++) {//補助線
                    double intersectionCalX = ((i * m_auxiliaryArcInterval / realMag) * sin(j * m_auxiliaryLineInterval * PI / 180)) + windowWidth * 0.5;
                    double intersectionCalY = windowHeight - ((i * m_auxiliaryArcInterval / realMag) * cos(j * m_auxiliaryLineInterval * PI / 180));
                    if (Dist(targetP2x, targetP2y, 0, intersectionCalX, intersectionCalY, 0) < Dist(targetP2x, targetP2y, 0, intersectionX, intersectionY, 0)) {
                        intersectionX = intersectionCalX;
                        intersectionY = intersectionCalY;
                    }
                    intersectionCalX = -((i * m_auxiliaryArcInterval / realMag) * sin(j * m_auxiliaryLineInterval * PI / 180)) + windowWidth * 0.5;
                    if (Dist(targetP2x, targetP2y, 0, intersectionCalX, intersectionCalY, 0) < Dist(targetP2x, targetP2y, 0, intersectionX, intersectionY, 0)) {
                        intersectionX = intersectionCalX;
                        intersectionY = intersectionCalY;
                    }
                }
            }
        }
        if (!topDragg && !sideDragg) {
            targetP2x = intersectionX;
            targetP2y = intersectionY;
        }
        DrawCircleAA(float(intersectionX), float(intersectionY), float(jointSize * 0.5 * 0.3), 32, accentColor, true);//手先xy座標が最も交点を表示
    }

    ScreenFlip();//裏画面を表画面にコピー

  return RTC::RTC_OK;
}

/*
RTC::ReturnCode_t RobotArmGUI::onAborting(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t RobotArmGUI::onError(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t RobotArmGUI::onReset(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t RobotArmGUI::onStateUpdate(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t RobotArmGUI::onRateChanged(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/



extern "C"
{
 
  void RobotArmGUIInit(RTC::Manager* manager)
  {
    coil::Properties profile(robotarmgui_spec);
    manager->registerFactory(profile,
                             RTC::Create<RobotArmGUI>,
                             RTC::Delete<RobotArmGUI>);
  }
  
};


