#include <Arduino.h>
#include "ACTimer.h"

ACTimer::ACTimer(long ms, ACTimerCallback callback) {
	this->miliStart = millis();
	this->timeout = ms;
	this->callback = callback;
	this->continous = false;
}

bool ACTimer::shouldTrigger(long ms) {
	return ((ms - miliStart) >= timeout);
}

bool ACTimer::shouldRemove(long ms) {
	if (!continous)
		return ((ms - miliStart) >= timeout);

	return false;
}

void ACTimer::loop(long ms) {
	if (shouldTrigger(ms)) {
		int i =0;
		callback(this, ms);
	}
}