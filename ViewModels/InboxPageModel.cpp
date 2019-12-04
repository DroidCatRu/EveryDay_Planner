#include "pch.h"
#include "InboxPageModel.h"

using namespace EveryDay;
using namespace EveryDay::ViewModels;

Vector<InboxEvent^>^ InboxPageModel::sortById(Vector<InboxEvent^>^ eventsdata, int left, int right) {

	int i = left, j = right;
	InboxEvent^ pivot = eventsdata->GetAt((left + right) / 2);

	int start;
	int pivotstart = pivot->Id;

	while (i <= j) {

		start = eventsdata->GetAt(i)->Id;

		while (start > pivotstart) {
			i++;
			start = eventsdata->GetAt(i)->Id;
		}

		start = eventsdata->GetAt(j)->Id;

		while (start < pivotstart) {
			j--;
			start = eventsdata->GetAt(j)->Id;
		}

		if (i <= j) {
			InboxEvent^ buff = eventsdata->GetAt(i);
			eventsdata->SetAt(i, eventsdata->GetAt(j));
			eventsdata->SetAt(j, buff);
			i++;
			j--;
		}
	}

	if (left < j)
		eventsdata = sortById(eventsdata, left, j);

	if (i < right)
		eventsdata = sortById(eventsdata, i, right);

	return eventsdata;
}

void InboxPageModel::Cal::set(Calendar^ Cal) {
	this->calendar = Cal;
	this->inboxEvents->Clear();

	for (int i = 0; i < Cal->getInboxEventsSize(); i++) {
		this->inboxEvents->Append(Cal->getInboxEventAt(i));
	}
	
	if (this->inboxEvents->Size > 1) {
		this->inboxEvents = sortById(this->inboxEvents, 0, this->inboxEvents->Size - 1);
	}

	OnPropertyChanged("EventsByDate");
}