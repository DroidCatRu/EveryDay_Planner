#include "pch.h"
#include "Helpers\InboxEvent.h"

using namespace EveryDay;

InboxEvent::InboxEvent() {
	title = nullptr;
	id = -1;
	isDone = false;
}

InboxEvent::InboxEvent(InboxEvent^ ev) {
	this->title = ev->Title;
	this->id = ev->Id;
	this->isDone = ev->IsDone;
}

InboxEvent::InboxEvent(Platform::String^ Title,
	long long Id,
	bool IsDone) :
	title{ Title },
	id{ Id },
	isDone{ IsDone }{}
