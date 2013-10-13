#ifndef ACLEDCOMPONENT
#define ACLEDCOMPONENT
#include <Arduino.h>
#include "ACComponent.h"

class ACLEDComponent : public ACComponent{
protected:
	bool useFade;

	//Fade variables
	int beginFadeValue; 
	int desiredValue;
	long fadeStart; 
	long fadePeriod;
public:
	ACLEDComponent(int pin, bool usingPWM);
	void SetFading(bool shouldFade);
	void SetFadeTime(long milliseconds);
	void SetLightValue(int value);

	int GetLightValue();
	virtual void Update(long milliseconds);
};

#endif