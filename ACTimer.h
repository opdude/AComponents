#ifndef ACTIMER
#define ACTIMER

class ACTimer;
typedef void ACTimerCallback(ACTimer*, long);

class ACTimer {
protected:
	long miliStart;
	long timeout;
	bool continous;
	ACTimerCallback* callback;

	bool shouldTrigger(long ms);
public:
	ACTimer(long ms, ACTimerCallback);
	
	void loop(long ms);

	bool shouldRemove(long ms);
};

template <class T>
class ACTimerObj: public ACTimer {
public:
	T object;
	ACTimerObj(long ms, T object, ACTimerCallback callback) : ACTimer(ms, callback) {
		this->object = object;
	};	
};

#endif