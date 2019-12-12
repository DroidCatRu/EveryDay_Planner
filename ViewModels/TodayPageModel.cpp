#include "pch.h"
#include "TodayPageModel.h"

#include <ctime>

using namespace EveryDay;
using namespace EveryDay::ViewModels;

void TodayPageModel::Cal::set(Calendar^ Cal) {
	this->calendar = Cal;

	auto evs = this->calendar->PlannedEvents;
	OnPropertyChanged("TodayEvents");
	OnPropertyChanged("Cal");
}

IObservableVector<PlannedEvent^>^ TodayPageModel::TodayEvents::get() {
	Vector<PlannedEvent^>^ todayEvents = ref new Vector<PlannedEvent^>;

	std::time_t t = std::time(0);
	std::tm now;
	localtime_s(&now, &t);
	int nowdate = (now.tm_year + 1900) * 10000 + (now.tm_mon + 1) * 100 + now.tm_mday;

	for (unsigned int i = 0; i < this->calendar->PlannedEvents->Size; i++) {
		PlannedEvent^ ev = this->calendar->PlannedEvents->GetAt(i);
		if (ev->Date == nowdate) {
			todayEvents->Append(ev);
		}
	}

	if (todayEvents->Size > 1) {
		todayEvents = sortByTime(todayEvents, 0, todayEvents->Size - 1);
	}

	return todayEvents;
}

IObservableVector<PlannedEvent^>^ TodayPageModel::OverdueEvents::get() {
	Vector<PlannedEvent^>^ overdueEvents = ref new Vector<PlannedEvent^>;

	std::time_t t = std::time(0);
	std::tm now;
	localtime_s(&now, &t);
	int nowdate = (now.tm_year + 1900) * 10000 + (now.tm_mon + 1) * 100 + now.tm_mday;

	for (unsigned int i = 0; i < this->calendar->PlannedEvents->Size; i++) {
		PlannedEvent^ ev = this->calendar->PlannedEvents->GetAt(i);
		if (ev->Date < nowdate && ev->IsDone == false) {
			overdueEvents->Append(ev);
		}
	}

	this->hasOverdue = overdueEvents->Size > 0;
	OnPropertyChanged("HasOverdue");

	if (overdueEvents->Size > 1) {
		overdueEvents = sortByTime(overdueEvents, 0, overdueEvents->Size - 1);
	}

	return overdueEvents;
}

Vector<PlannedEvent^>^ TodayPageModel::sortByTime(Vector<PlannedEvent^>^ events, int left, int right) {

	int i = left, j = right;
	PlannedEvent^ pivot = events->GetAt((left + right) / 2);

	int start;
	int pivotstart = pivot->Start;

	while (i <= j) {

		start = events->GetAt(i)->Start;

		while (start < pivotstart) {
			i++;
			start = events->GetAt(i)->Start;
		}

		start = events->GetAt(j)->Start;

		while (start > pivotstart) {
			j--;
			start = events->GetAt(j)->Start;
		}

		if (i <= j) {
			PlannedEvent^ buff = events->GetAt(i);
			events->SetAt(i, events->GetAt(j));
			events->SetAt(j, buff);
			i++;
			j--;
		}
	}

	if (left < j)
		events = sortByTime(events, left, j);

	if (i < right)
		events = sortByTime(events, i, right);

	return events;
}