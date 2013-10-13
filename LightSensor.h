#ifndef LIGHTSENSOR
#define LIGHTSENSOR
#include "ACManager.h"

class ACLightSensor : public ACComponent {
private:
	bool calibrated;
	int calibratedLow;
	int calibratedHigh;
public:
	ACLightSensor(int pin);
	void Calibrate(ACManager* manager);
	int GetValue();
	
	void Update(long milliseconds) {}
	
	bool isCalibrated() {
		return true;
	}	
	int getCalibratedLow() {
		return calibratedLow;
	}
	
	int getCalibratedHigh() {
		return calibratedHigh;
	}
	
	void setCalibratedLow(int low) {
		calibratedLow = low;
	}
	
	void setCalibratedHigh(int high) {
		calibratedHigh = high;
	}
	
	void setCalibrated(bool val) {
		calibrated = val;
	}
};
#endif