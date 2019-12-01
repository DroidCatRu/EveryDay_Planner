#include "pch.h"
#include "Helpers\InboxEvent.h"

using namespace EveryDay;

InboxEvent::InboxEvent() {
	title = nullptr;
	color = nullptr;
	id = -1;
	isDone = false;
}

InboxEvent::InboxEvent(InboxEvent^ ev) {
	this->title = ev->Title;
	this->color = ev->Color;
	this->id = ev->Id;
	this->isDone = ev->IsDone;
}

InboxEvent::InboxEvent(Platform::String^ Title,
	Platform::String^ Color,
	long long Id,
	bool IsDone) :
	title{ Title },
	color{ Color },
	id{ Id },
	isDone{ IsDone }{}
