#include "pch.h"
#include "Helpers\PlannedEvent.h"

using namespace EveryDay;

PlannedEvent::PlannedEvent() {
	title = nullptr;
	start = -1;
	date = -1;
	id = -1;
	isDone = false;
}

PlannedEvent::PlannedEvent(InboxEvent^ ev, int Start, int Date) {
	this->title = ev->Title;
	this->start = Start;
	this->date = Date;
	this->id = ev->Id;
	this->isDone = ev->IsDone;
}

PlannedEvent::PlannedEvent(Platform::String^ Title,
	int Start,
	int Date,
	long long Id,
	bool IsDone) :
	title{ Title },
	start{ Start },
	date{ Date },
	id{ Id },
	isDone{ IsDone } {}
