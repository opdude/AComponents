#include "ACManager.h"

ACManager::ACManager() {
}

void ACManager::addTimer(ACTimer *timer) {
	timers.push_back(timer);
}

void ACManager::update(long ms) {

	for (vector<ACComponent*>::iterator it = components.begin(); it != components.end(); it++) {
		ACComponent* c = *it;
		c->Update(ms);
	}

	for (vector<ACTimer*>::iterator it = timers.begin(); it != timers.end(); ++it) {
		ACTimer* t = *it;
		t->loop(ms);

		if (t->shouldRemove(ms)) {
			delete t;
			it = timers.erase(it);
			
			if (it == timers.end()) 
				break;
		}
	}
}

void ACManager::addComponent(ACComponent* component) {
	components.push_back(component);
}