//Tests our libray
#include <StandardCplusplus.h>
#include "MemoryFree.h"
#include "LEDComponent.h"
#include "LightSensor.h"
#include "RGBLEDComponent.h"
#include "ArduinoUtils.h"
#include "ACManager.h"

int redLED = 11;
int greenLED = 9;
int blueLED = 10;

int sensorPin = A0;

ACManager *acManager;
RGBLEDComponent* rgbLED;
ACLightSensor* lightSensor;

void setup()
{
	acManager = new ACManager();

	rgbLED = new RGBLEDComponent(redLED, greenLED, blueLED, true);
	acManager->addComponent(rgbLED);

	lightSensor = new ACLightSensor(sensorPin);
	acManager->addComponent(lightSensor);
	lightSensor->Calibrate(acManager);

	Test1(NULL, millis());
}

void loop() {
	long ms = millis();


	if (lightSensor->isCalibrated()) {
		int val = lightSensor->GetValue();
		int x  = 1;
	}

	//Update all things managed by the manager
	acManager->update(ms);
}

void Test1(ACTimer* timer, long ms) {

	//Test #1 Max on Max Off
	rgbLED->SetFading(false);
	rgbLED->SetLightValue(255);
	acManager->addTimer(new ACTimer(2000, SetLightOff));
	acManager->addTimer(new ACTimer(2500, Test2));
}

void Test2(ACTimer* timer, long ms) {
	//Test #2 Max on Max Off with fade
	rgbLED->SetFading(true);
	rgbLED->SetFadeTime(500);
	SetLightOn(NULL, ms);
	acManager->addTimer(new ACTimer(750, SetLightOff));
	acManager->addTimer(new ACTimer(1500, Test3));
}

void Test3(ACTimer* timer, long ms) {
	//Individual RGB Lights
	rgbLED->SetFading(true);
	rgbLED->SetFadeTime(500);
	acManager->addTimer(new ACTimerObj<RGBValue>(750, RGBValue(255,0,0), SetRGBValue));
	acManager->addTimer(new ACTimer(1500, SetLightOff));
	acManager->addTimer(new ACTimerObj<RGBValue>(2250, RGBValue(0,255,0), SetRGBValue));
	acManager->addTimer(new ACTimer(3000, SetLightOff));
	acManager->addTimer(new ACTimerObj<RGBValue>(3750, RGBValue(0,0,255), SetRGBValue));
	acManager->addTimer(new ACTimer(4500, SetLightOff));
	acManager->addTimer(new ACTimer(5250, Test4));
}

void Test4(ACTimer* timer, long ms) {
	rgbLED->SetFading(true);
	rgbLED->SetFadeTime(500);

	const int delayPeriod = 1000;
	const int lightSensorLoops = 5;
	for (int i=0; i < lightSensorLoops; i++) {
		acManager->addTimer(new ACTimerObj<ACLightSensor*>((delayPeriod * (i + 1)), lightSensor, SetLightWithSensor));
	}

	acManager->addTimer(new ACTimer(delayPeriod * (lightSensorLoops + 1), Test1));
}

void SetLightWithSensor(ACTimer* timer, long ms) {
	ACTimerObj<ACLightSensor*>* timerObj = ((ACTimerObj<ACLightSensor*>*)timer);
	int val = timerObj->object->GetValue();
	rgbLED->SetLightValue(val / 4);
}

void SetRGBValue(ACTimer* timer, long ms) {
	ACTimerObj<RGBValue>* timerObj = ((ACTimerObj<RGBValue>*)timer);
	
	if (timerObj != NULL) {
		rgbLED->SetRGBLightValue(timerObj->object);
	}
}

void SetLightOn(ACTimer* timer, long ms) {
	rgbLED->SetLightValue(255);
}

void SetLightOff(ACTimer* timer, long ms) {
	rgbLED->SetLightValue(0);
}