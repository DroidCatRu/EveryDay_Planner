#include "pch.h"
#include "WeekPageModel.h"

#include <ctime>

using namespace EveryDay;
using namespace EveryDay::ViewModels;

void WeekPageModel::Cal::set(Calendar^ Cal) {
	this->calendar = Cal;

	OnPropertyChanged("Monday");
	OnPropertyChanged("Tuesday");
	OnPropertyChanged("Wednesday");
	OnPropertyChanged("Thursday");
	OnPropertyChanged("Friday");
	OnPropertyChanged("Saturday");
	OnPropertyChanged("Sunday");
	OnPropertyChanged("Cal");
}

IObservableVector<PlannedEvent^>^ WeekPageModel::Monday::get() {
	Vector<PlannedEvent^>^ events = ref new Vector<PlannedEvent^>;

	int nowdate = getDateIncreased(0);

	for (unsigned int i = 0; i < this->calendar->PlannedEvents->Size; i++) {
		PlannedEvent^ ev = this->calendar->PlannedEvents->GetAt(i);
		if (ev->Date == nowdate) {
			events->Append(ev);
		}
	}

	if (events->Size > 1) {
		events = sortByTime(events, 0, events->Size - 1);
	}

	return events;
}

IObservableVector<PlannedEvent^>^ WeekPageModel::Tuesday::get() {
	Vector<PlannedEvent^>^ events = ref new Vector<PlannedEvent^>;

	int nowdate = getDateIncreased(1);

	for (unsigned int i = 0; i < this->calendar->PlannedEvents->Size; i++) {
		PlannedEvent^ ev = this->calendar->PlannedEvents->GetAt(i);
		if (ev->Date == nowdate) {
			events->Append(ev);
		}
	}

	if (events->Size > 1) {
		events = sortByTime(events, 0, events->Size - 1);
	}

	return events;
}

IObservableVector<PlannedEvent^>^ WeekPageModel::Wednesday::get() {
	Vector<PlannedEvent^>^ events = ref new Vector<PlannedEvent^>;

	int nowdate = getDateIncreased(2);

	for (unsigned int i = 0; i < this->calendar->PlannedEvents->Size; i++) {
		PlannedEvent^ ev = this->calendar->PlannedEvents->GetAt(i);
		if (ev->Date == nowdate) {
			events->Append(ev);
		}
	}

	if (events->Size > 1) {
		events = sortByTime(events, 0, events->Size - 1);
	}

	return events;
}

IObservableVector<PlannedEvent^>^ WeekPageModel::Thursday::get() {
	Vector<PlannedEvent^>^ events = ref new Vector<PlannedEvent^>;
	
	int nowdate = getDateIncreased(3);

	for (unsigned int i = 0; i < this->calendar->PlannedEvents->Size; i++) {
		PlannedEvent^ ev = this->calendar->PlannedEvents->GetAt(i);
		if (ev->Date == nowdate) {
			events->Append(ev);
		}
	}

	if (events->Size > 1) {
		events = sortByTime(events, 0, events->Size - 1);
	}

	return events;
}

IObservableVector<PlannedEvent^>^ WeekPageModel::Friday::get() {
	Vector<PlannedEvent^>^ events = ref new Vector<PlannedEvent^>;

	int nowdate = getDateIncreased(4);

	for (unsigned int i = 0; i < this->calendar->PlannedEvents->Size; i++) {
		PlannedEvent^ ev = this->calendar->PlannedEvents->GetAt(i);
		if (ev->Date == nowdate) {
			events->Append(ev);
		}
	}

	if (events->Size > 1) {
		events = sortByTime(events, 0, events->Size - 1);
	}

	return events;
}

IObservableVector<PlannedEvent^>^ WeekPageModel::Saturday::get() {
	Vector<PlannedEvent^>^ events = ref new Vector<PlannedEvent^>;

	int nowdate = getDateIncreased(5);

	for (unsigned int i = 0; i < this->calendar->PlannedEvents->Size; i++) {
		PlannedEvent^ ev = this->calendar->PlannedEvents->GetAt(i);
		if (ev->Date == nowdate) {
			events->Append(ev);
		}
	}

	if (events->Size > 1) {
		events = sortByTime(events, 0, events->Size - 1);
	}

	return events;
}

IObservableVector<PlannedEvent^>^ WeekPageModel::Sunday::get() {
	Vector<PlannedEvent^>^ events = ref new Vector<PlannedEvent^>;

	int nowdate = getDateIncreased(6);

	for (unsigned int i = 0; i < this->calendar->PlannedEvents->Size; i++) {
		PlannedEvent^ ev = this->calendar->PlannedEvents->GetAt(i);
		if (ev->Date == nowdate) {
			events->Append(ev);
		}
	}

	if (events->Size > 1) {
		events = sortByTime(events, 0, events->Size - 1);
	}

	return events;
}

IObservableVector<PlannedEvent^>^ WeekPageModel::OverdueEvents::get() {
	Vector<PlannedEvent^>^ overdueEvents = ref new Vector<PlannedEvent^>;

	int nowdate = getDateIncreased(0);

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

int WeekPageModel::getDateIncreased(int n) {
	std::time_t t = std::time(0);
	std::tm now;
	localtime_s(&now, &t);

	int d = now.tm_mday, m = now.tm_mon + 1, y = now.tm_year + 1900;

	for (int i = 0; i < n; i++) {
		if (d == this->calendar->getNumberOfDays(m, y)) {
			if (m < 12) {
				m += 1;
				d = 1;
			}
			else {
				m = 1;
				d = 1;
			}
		}
		else {
			d++;
		}
	}

	return y * 10000 + m * 100 + d;;
}

Vector<PlannedEvent^>^ WeekPageModel::sortByTime(Vector<PlannedEvent^>^ events, int left, int right) {

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