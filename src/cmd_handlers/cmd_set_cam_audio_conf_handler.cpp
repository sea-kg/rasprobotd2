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

#include "cmd_set_cam_audio_conf_handler.h"
#include <QFile>
#include <QTextStream>
#include <QThread>
#include <QElapsedTimer>

QString CmdSetCamAudioConfHandler::cmd(){
	return "set_cam_audio_conf";
}

void CmdSetCamAudioConfHandler::handle(QJsonObject obj, IWebSocketClient *wsc){

	int nCamid = 0;
	if(obj.contains("cam_id")){
		nCamid = obj["cam_id"].toInt();
	}

	if(obj.contains("spkr_mute")){
		bool sprk_mute = obj["spkr_mute"].toBool();
		wsc->settings()->audioconf_spkr_mute(sprk_mute);
		
		if(sprk_mute == false){
			if(obj.contains("spkr_vol")){
				int spkr_vol = obj["spkr_vol"].toInt();
				int min = 1100; // 0
				int max = 2200; // 100
				int k = (2200 - 1100) / 100;
				wsc->settings()->audioconf_spkr_vol(spkr_vol);
				int mPinD1 = wsc->settings()->drivers_PIN_D1();
				pwmPin(mPinD1, 1100 + spkr_vol*k);
			}
		}
	}
	
	if(obj.contains("mic_mute")){
		wsc->settings()->audioconf_mic_mute(obj["mic_mute"].toBool());
	}
	
	if(obj.contains("mic_gain")){
		wsc->settings()->audioconf_mic_gain(obj["mic_gain"].toInt());
	}

	wsc->sendMessage(wsc->makeCommandDone(cmd(), obj["msgid"].toInt(), "OK"));	
}

// ---------------------------------------------------------------------

void CmdSetCamAudioConfHandler::setPinValue(int pin, int value){
	QFile file("/sys/class/gpio/gpio" + QString::number(pin) + "/value");
	if (file.open(QIODevice::ReadWrite)){
		QTextStream stream( &file );
		stream << QString::number(value) << endl;
	}
}

// ---------------------------------------------------------------------

void CmdSetCamAudioConfHandler::pwmPin(int pin, qint64 width_signal_usec){
	QFile file("/sys/class/gpio/gpio" + QString::number(pin) + "/value");
	if (file.open(QIODevice::ReadWrite)){
		QTextStream stream( &file );
		int counter = 0;
		QElapsedTimer timer;
		qint64 elapsed;
		while(true){
			timer.restart();
			stream << QString::number(1) << endl;
			elapsed = timer.nsecsElapsed()/1000;
			QThread::usleep(width_signal_usec);
			stream << QString::number(0) << endl;
			elapsed = timer.nsecsElapsed()/1000;
			QThread::usleep(20000 - elapsed);
			counter++;
			if(counter > 21){
				break;
				return;
			}
		}
	}
}
