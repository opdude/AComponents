#ifndef ACMANAGER
#define ACMANAGER
#include <StandardCplusplus.h>
#include <Vector>
#include "ACTimer.h"
#include "ACComponent.h"

using namespace std;

class ACManager {
private:
	vector<ACTimer*> timers;
	vector<ACComponent*> components;
public:
	ACManager();
	void addComponent(ACComponent* component);
	void addTimer(ACTimer* timer);

	void update(long ms);
};

#endif