#include <Arduino.h>
#include "LEDComponent.h"
#include "ArduinoMath.h"

ACLEDComponent::ACLEDComponent(int pin, bool usingPWM) {
	this->pin = pin;
	this->usingPWM = usingPWM;

	fadePeriod = 500;
	value = 0;
	useFade = false;

	pinMode(pin, OUTPUT);
}

void ACLEDComponent::SetFading(bool shouldFade) {
	useFade = shouldFade;
}

void ACLEDComponent::SetFadeTime(long milliseconds) {
	fadePeriod = milliseconds;
}

void ACLEDComponent::SetLightValue(int value) {
	if (usingPWM) {
		constrain(value, 0, 255);
	}
	else {
		constrain(value, 0, 1);
	}

	if (useFade) {
		fadeStart = millis();
		beginFadeValue = this->value;
		desiredValue = value;
	}
	else {
		this->value = value;
	}
}

int ACLEDComponent::GetLightValue() {
	return value;
}

void ACLEDComponent::Update(long milliseconds) {
	if (useFade && value != desiredValue) {
		long timeDiff = milliseconds - fadeStart;
		float t = map(timeDiff, 0, fadePeriod, 0, 100) / 100.0;
		value = ArduinoMath::Lerp(beginFadeValue, desiredValue, t);
	}

	if (this->usingPWM) {
		analogWrite(pin, value);
	}
	else {
		digitalWrite(pin, value);
	}
}