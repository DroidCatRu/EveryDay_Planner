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
			event->Color = gotObject->GetNamedString("color");
			event->IsDone = gotObject->GetNamedBoolean("isDone");
			event->Id = gotObject->GetNamedNumber("id");

			inboxEventsNew->Append(event);
		}

		this->inboxEvents = inboxEventsNew;

		for (unsigned int i = 0; i < jsonPlanned->Size; i++) {
			PlannedEvent^ event = ref new PlannedEvent;
			JsonObject^ gotObject = jsonPlanned->GetObjectAt(i);

			event->Title = gotObject->GetNamedString("title");
			event->Color = gotObject->GetNamedString("color");
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

		create_task(FileIO::WriteTextAsync(eventsFile, str))
		.then([this, str](task<void> task) mutable {
			task.get();
		});
	}
}

String^ Calendar::getJsonedStr() {
	JsonObject^ jsonCalendar = ref new JsonObject;

	JsonArray^ jsonInbox = ref new JsonArray;
	JsonArray^ jsonPlanned = ref new JsonArray;
	
	for (unsigned int i = 0; i < inboxEvents->Size; i++) {
		JsonObject^ ev = ref new JsonObject();
		ev->Insert("title", JsonValue::CreateStringValue(inboxEvents->GetAt(i)->Title));
		ev->Insert("color", JsonValue::CreateStringValue(inboxEvents->GetAt(i)->Color));
		ev->Insert("id", JsonValue::CreateNumberValue(inboxEvents->GetAt(i)->Id));
		ev->Insert("isDone", JsonValue::CreateBooleanValue(inboxEvents->GetAt(i)->IsDone));

		jsonInbox->Append(ev);
	}

	for (unsigned int i = 0; i < plannedEvents->Size; i++) {
		JsonObject^ ev = ref new JsonObject();
		ev->Insert("title", JsonValue::CreateStringValue(plannedEvents->GetAt(i)->Title));
		ev->Insert("color", JsonValue::CreateStringValue(plannedEvents->GetAt(i)->Color));
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