#include "RGBLEDComponent.h"
#include "ArduinoMath.h"
#include "ArduinoUtils.h"


RGBLEDComponent::RGBLEDComponent(int redPin, int greenPin, int bluePin, bool usePWM) : ACLEDComponent::ACLEDComponent(-1, usePWM) {
	pins[RGBValue::RPOS] = redPin;
	pins[RGBValue::GPOS] = greenPin;
	pins[RGBValue::BPOS] = bluePin;

	for (int i=0; i < 3; i++) {
		pinMode(pins[i], OUTPUT);
		beginFadeValues = RGBValue(0);
		desiredValues = RGBValue(0);
		values = RGBValue(0);
	}
}

void RGBLEDComponent::SetRGBLightValue(RGBValue value) {
	if (usingPWM) {
		vector<int> rgbArray = value.getRGBArray();
		for (int i=0; i <= RGBValue::BPOS; i++) {
			rgbArray[i] = constrain(rgbArray[i], 0, 255);
		}
		value.setRGBArray(rgbArray);
	}
	else {
		vector<int> rgbArray = value.getRGBArray();
		for (int i=0; i <= RGBValue::BPOS; i++) {
			rgbArray[i] = constrain(rgbArray[i], LOW, HIGH);
		}
		value.setRGBArray(rgbArray);
	}

	if (useFade) {
		fadeStart = millis();

		beginFadeValues.setRGBValue(values);
		desiredValues.setRGBValue(value);
	}
	else {
		values.setRGBValue(value);
	}
}

void RGBLEDComponent::SetLightValue(int value) {
	if (usingPWM) {
		value = constrain(value, 0, 255);
	}
	else {
		value = constrain(value, LOW, HIGH);
	}

	if (useFade) {
		fadeStart = millis();
		beginFadeValues.setRGBValue(values);
		desiredValues.setValue(value);
	}
	else {
		values.red = values.green = values.blue = value;
	}
}

void RGBLEDComponent::Update(long milliseconds) {
	vector<int> rgbArray = values.getRGBArray();
	vector<int> desiredRGBArray = desiredValues.getRGBArray();
	vector<int> beginFadeArray = beginFadeValues.getRGBArray();

	for (int i=0; i <= RGBValue::BPOS; i++) {
		if (useFade && rgbArray[i] != desiredRGBArray[i]) {
			long timeDiff = milliseconds - fadeStart;
			float t = map(timeDiff, 0, fadePeriod, 0, 100) / 100.0;
			rgbArray[i] = ArduinoMath::Lerp(beginFadeArray[i], desiredRGBArray[i], t);
			if (usingPWM) {
				rgbArray[i] = constrain(rgbArray[i], 0, 255);
			}
			else {
				rgbArray[i] = constrain(rgbArray[i], 0, 1);
			}
		}

		if (this->usingPWM) {
			analogWrite(pins[i], rgbArray[i]);
		}
		else {
			digitalWrite(pins[i], rgbArray[i]);
		}
	}

	values.setRGBArray(rgbArray);
}

int RGBLEDComponent::GetLightValue() {
	return (values.red + values.green + values.blue) / 3;
}

RGBValue RGBLEDComponent::GetRGBLightValue() {
	return values;
}