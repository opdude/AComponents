#ifndef RGBLEDCOMPONENT
#define RGBLEDCOMPONENT
#include <StandardCplusplus.h>
#include <vector>
#include "LEDComponent.h"

using namespace std;

// Simple Struct for containing RGB Info
class RGBValue {
public:
	//Positioning of RGB in the array
	static const int RPOS = 0;
	static const int GPOS = 1;
	static const int BPOS = 2;

	int red;
	int green;
	int blue;

	RGBValue() : red(0), green(0), blue(0) {}

	RGBValue(int red, int green, int blue) :
		red(red), green(green), blue(blue) { }

	RGBValue(int value) :
		red(value), green(value), blue(value) { }

	std::vector<int> getRGBArray() {
		vector<int> arr;
		arr.push_back(red);
		arr.push_back(green);
		arr.push_back(blue);
		return arr;
	}

	void setValue(int value) {
		this->red = this->green = this->blue = value;
	}

	void setRGBValues(int red, int green, int blue) {
		this->red = red;
		this->green = green;
		this->blue = blue;
	}

	void setRGBArray(vector<int> values) {
		if (values.size() == 3) {
			red = values[RPOS];
			green = values[GPOS];
			blue = values[BPOS];
		}
	}

	void setRGBValue(RGBValue value) {
		red = value.red;
		green = value.green;
		blue = value.blue;
	}
};

class RGBLEDComponent: public ACLEDComponent {
private:

	int pins[3];
	RGBValue values;
	RGBValue desiredValues;

	//Fade
	RGBValue beginFadeValues;

public:
	RGBLEDComponent(int redPin, int greenPin, int bluePin, bool usePWM);
	void SetRGBLightValue(RGBValue value);
	virtual void SetLightValue(int value);

	virtual int GetLightValue(); //Returns the average colour between the RGB
	RGBValue GetRGBLightValue();

	virtual void Update(long miliseconds);
};
#endif
