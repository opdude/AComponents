#include <Arduino.h>
#include "LightSensor.h"
#include "ACTimer.h"
#include "ACManager.h"

ACLightSensor::ACLightSensor(int pin) {
	this->pin = pin;
	calibrated = false;
	this->calibratedHigh = 0;
	this->calibratedLow = 1023;
}

void finishedCalibrating(ACTimer* timer, long ms) {
	ACLightSensor *ls = ((ACTimerObj<ACLightSensor*>*)timer)->object;
	ls->setCalibrated(true);
}

void CalibrateLoop(ACTimer *timer, long ms) {
	ACLightSensor *ls = ((ACTimerObj<ACLightSensor*>*)timer)->object;
	int val = analogRead(ls->getPin());
	if (val < ls->getCalibratedLow()) {
		ls->setCalibratedLow(val);
	}
	else if (val > ls->getCalibratedHigh()) {
		ls->setCalibratedHigh(val);
	}
}

void ACLightSensor::Calibrate(ACManager *manager) {
	if (!calibrated) {
		const int calibrateDelay = 250;
		const int calibrateNumber = 50;
		
		for (int i=1; i <= calibrateNumber; i++) {
			manager->addTimer(new ACTimerObj<ACLightSensor*>((calibrateDelay * i), this , CalibrateLoop));
		}
		
		manager->addTimer(new ACTimerObj<ACLightSensor*>(calibrateDelay * (calibrateNumber + 1), this, finishedCalibrating));
	}
}

int ACLightSensor::GetValue() {
	int val = analogRead(pin);
	if (calibrated) {
		return map(val, calibratedLow, calibratedHigh, 0, 1023);
	}
	
	return val;
}