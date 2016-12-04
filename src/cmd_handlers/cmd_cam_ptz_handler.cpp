//
//  Copyright © 2016 VXG Inc. All rights reserved.
//  Contact: https://www.videoexpertsgroup.com/contact-vxg/
//  This file is part of the demonstration of the VXG Cloud Platform.
//
//  Commercial License Usage
//  Licensees holding valid commercial VXG licenses may use this file in
//  accordance with the commercial license agreement provided with the
//  Software or, alternatively, in accordance with the terms contained in
//  a written agreement between you and VXG Inc. For further information
//  use the contact form at https://www.videoexpertsgroup.com/contact-vxg/
//

#include <QFile>
#include <QTextStream>
#include "cmd_cam_ptz_handler.h"

QString CmdCamPtzHandler::cmd(){
	return "cam_ptz";
}

void CmdCamPtzHandler::handle(QJsonObject obj, IWebSocketClient *wsc){
	if(obj.contains("action")){
		QString action = obj["action"].toString();
		
		int mPinA1 = wsc->settings()->drivers_PIN_A1();
		int mPinA2 = wsc->settings()->drivers_PIN_A2();
		int mPinB1 = wsc->settings()->drivers_PIN_B1();
		int mPinB2 = wsc->settings()->drivers_PIN_B2();
		
		if(action == "left"){
			setPinValue(mPinA1, wsc->settings()->drivers_turnleft_A1());
			setPinValue(mPinA2, wsc->settings()->drivers_turnleft_A2());
			setPinValue(mPinB1, wsc->settings()->drivers_turnleft_B1());
			setPinValue(mPinB2, wsc->settings()->drivers_turnleft_B2());
		}else if(action == "right"){
			setPinValue(mPinA1, wsc->settings()->drivers_turnright_A1());
			setPinValue(mPinA2, wsc->settings()->drivers_turnright_A2());
			setPinValue(mPinB1, wsc->settings()->drivers_turnright_B1());
			setPinValue(mPinB2, wsc->settings()->drivers_turnright_B2());
		}else if(action == "top"){
			setPinValue(mPinA1, wsc->settings()->drivers_forward_A1());
			setPinValue(mPinA2, wsc->settings()->drivers_forward_A2());
			setPinValue(mPinB1, wsc->settings()->drivers_forward_B1());
			setPinValue(mPinB2, wsc->settings()->drivers_forward_B2());			
		}else if(action == "bottom"){
			setPinValue(mPinA1, wsc->settings()->drivers_backward_A1());
			setPinValue(mPinA2, wsc->settings()->drivers_backward_A2());
			setPinValue(mPinB1, wsc->settings()->drivers_backward_B1());
			setPinValue(mPinB2, wsc->settings()->drivers_backward_B2());
		}else if(action == "stop"){
			setPinValue(mPinA1, 0);
			setPinValue(mPinA2, 0);
			setPinValue(mPinB1, 0);
			setPinValue(mPinB2, 0);
		}
		
		// TODO
		// wsc->sendMessage(wsc->makeCommandDone(cmd(), obj["msgid"].toInt(), "OK"));	
	}
	
	// "action": "left"
	
}

void CmdCamPtzHandler::setPinValue(int pin, int value){
	QFile file("/sys/class/gpio/gpio" + QString::number(pin) + "/value");
	if (file.open(QIODevice::ReadWrite)){
		QTextStream stream( &file );
		stream << QString::number(value) << endl;
		qDebug() << "Set value " << value << " to " << pin;
	}
}
