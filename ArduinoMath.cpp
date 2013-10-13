#include <Arduino.h>
#import "ArduinoMath.h"


 float ArduinoMath::Lerp(float valueA, float valueB, float time) {
	time = constrain(time, 0.0f,1.0f);
	return valueA + time * (valueB - valueA);
 }