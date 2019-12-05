#include "pch.h"
#include "Calendar.h"

using namespace EveryDay;
using namespace concurrency;

void Calendar::loadFromFile() {

	StorageFolder^ folder = ApplicationData::Current->LocalFolder;
	String^ filename = "events.json";

	create_task(folder->CreateFileAsync(filename, CreationCollisionOption::OpenIfExists))
		.then([this](task<StorageFile^> task) mutable {
		StorageFile^ file = task.get();
		eventsFile = file;

		return FileIO::ReadTextAsync(file);
			}, task_continuation_context::use_default())
		.then([this](task<String^> task) mutable {
				String^ str = task.get();
				if (str->Length() == 0) {
					str = getJsonedStr();
				}
				getFromStr(str);
			});
}

void Calendar::getFromStr(String^ str) {

	if (str->Length() > 0) {
		Vector<InboxEvent^>^ inboxEventsNew = ref new Vector<InboxEvent^>;
		Vector<PlannedEvent^>^ plannedEventsNew = ref new Vector<PlannedEvent^>;

		JsonObject^ jsonCalendar = JsonObject::Parse(str);

		JsonArray^ jsonInbox = jsonCalendar->GetNamedArray("inbox");
		JsonArray^ jsonPlanned = jsonCalendar->GetNamedArray("planned");

		for (unsigned int i = 0; i < jsonInbox->Size; i++) {
			InboxEvent^ event = ref new InboxEvent;
			JsonObject^ gotObject = jsonInbox->GetObjectAt(i);

			event->Title = gotObject->GetNamedString("title");
			event->IsDone = gotObject->GetNamedBoolean("isDone");
			event->Id = gotObject->GetNamedNumber("id");

			inboxEventsNew->Append(event);
		}

		if (this->inboxEvents->Size > 1) {
			this->inboxEvents = sortById(inboxEventsNew, 0, inboxEventsNew->Size - 1);
		}
		else {
			this->inboxEvents = inboxEventsNew;
		}

		for (unsigned int i = 0; i < jsonPlanned->Size; i++) {
			PlannedEvent^ event = ref new PlannedEvent;
			JsonObject^ gotObject = jsonPlanned->GetObjectAt(i);

			event->Title = gotObject->GetNamedString("title");
			event->IsDone = gotObject->GetNamedBoolean("isDone");
			event->Id = gotObject->GetNamedNumber("id");
			event->Date = gotObject->GetNamedNumber("date");
			event->Start = gotObject->GetNamedNumber("start");

			plannedEventsNew->Append(event);
		}

		this->plannedEvents = plannedEventsNew;
	}
}

void Calendar::save() {
	if (eventsFile != nullptr) {
		String^ str = getJsonedStr();

		create_task(FileIO::WriteTextAsync(eventsFile, str));
	}
}

String^ Calendar::getJsonedStr() {
	JsonObject^ jsonCalendar = ref new JsonObject;

	JsonArray^ jsonInbox = ref new JsonArray;
	JsonArray^ jsonPlanned = ref new JsonArray;
	
	for (unsigned int i = 0; i < inboxEvents->Size; i++) {
		JsonObject^ ev = ref new JsonObject();
		ev->Insert("title", JsonValue::CreateStringValue(inboxEvents->GetAt(i)->Title));
		ev->Insert("id", JsonValue::CreateNumberValue(inboxEvents->GetAt(i)->Id));
		ev->Insert("isDone", JsonValue::CreateBooleanValue(inboxEvents->GetAt(i)->IsDone));

		jsonInbox->Append(ev);
	}

	for (unsigned int i = 0; i < plannedEvents->Size; i++) {
		JsonObject^ ev = ref new JsonObject();
		ev->Insert("title", JsonValue::CreateStringValue(plannedEvents->GetAt(i)->Title));
		ev->Insert("id", JsonValue::CreateNumberValue(plannedEvents->GetAt(i)->Id));
		ev->Insert("isDone", JsonValue::CreateBooleanValue(plannedEvents->GetAt(i)->IsDone));
		ev->Insert("date", JsonValue::CreateNumberValue(plannedEvents->GetAt(i)->Date));
		ev->Insert("start", JsonValue::CreateNumberValue(plannedEvents->GetAt(i)->Start));

		jsonPlanned->Append(ev);
	}

	jsonCalendar->Insert("inbox", jsonInbox);
	jsonCalendar->Insert("planned", jsonPlanned);

	return jsonCalendar->Stringify();
}

void Calendar::setEventsFile(StorageFile^ Events) {
	this->eventsFile = Events;
}

Object^ Calendar::getEvent(long long id) {
	for (int i = 0; i < this->getInboxEventsSize(); i++) {
		if (this->getInboxEventAt(i)->Id == id) {
			return this->getInboxEventAt(i);
		}
	}

	for (int i = 0; i < this->getPlannedEventsSize(); i++) {
		if (this->getPlannedEventAt(i)->Id == id) {
			return this->getPlannedEventAt(i);
		}
	}
}

void Calendar::setEventDone(long long id, bool done) {
	for (int i = 0; i < this->getInboxEventsSize(); i++) {
		if (this->getInboxEventAt(i)->Id == id) {
			this->getInboxEventAt(i)->IsDone = done;
			return;
		}
	}

	for (int i = 0; i < this->getPlannedEventsSize(); i++) {
		if (this->getPlannedEventAt(i)->Id == id) {
			this->getPlannedEventAt(i)->IsDone = done;
			return;
		}
	}

}

void Calendar::removeEventWithId(long long id) {
	bool removed = false;
	for (int i = 0; i < inboxEvents->Size; i++) {
		if (inboxEvents->GetAt(i)->Id == id) {
			inboxEvents->RemoveAt(i);
			removed = true;
			OnPropertyChanged("InboxEvents");
		}
	}

	if (removed == false) {
		for (int i = 0; i < plannedEvents->Size; i++) {
			if (plannedEvents->GetAt(i)->Id == id) {
				plannedEvents->RemoveAt(i);
				removed = true;
				OnPropertyChanged("PlannedEvents");
			}
		}
	}
}

long long Calendar::getNewId() {
	long long lastId = 0;

	for (int i = 0; i < inboxEvents->Size; i++) {
		if (inboxEvents->GetAt(i)->Id > lastId) {
			lastId = inboxEvents->GetAt(i)->Id;
		}
	}

	for (int i = 0; i < plannedEvents->Size; i++) {
		if (plannedEvents->GetAt(i)->Id > lastId) {
			lastId = plannedEvents->GetAt(i)->Id;
		}
	}

	return lastId + 1;
}

Vector<InboxEvent^>^ Calendar::sortById(Vector<InboxEvent^>^ eventsdata, int left, int right) {

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