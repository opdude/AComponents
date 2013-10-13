/* 
* ACComponent.h
*
* Created: 12/10/2013 15:27:00
* Author: Opdude
*/


#ifndef __ACCOMPONENT_H__
#define __ACCOMPONENT_H__


class ACComponent
{
//variables
public:
protected:
	int pin;
	int value;
	bool usingPWM;
private:

//functions
public:
	virtual void Update(long milliseconds);
	int getPin() {
		return pin;
	}
protected:
private:

}; //ACComponent

#endif //__ACCOMPONENT_H__
