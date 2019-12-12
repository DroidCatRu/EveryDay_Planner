#include "pch.h"
#include "SearchPageModel.h"

#include <string>
#include <algorithm>
#include <locale>
#include <codecvt>

using namespace EveryDay;
using namespace EveryDay::ViewModels;

void SearchPageModel::Cal::set(Calendar^ Cal) {
	this->calendar = Cal;
	OnPropertyChanged("Cal");
}

IObservableVector<InboxEvent^>^ SearchPageModel::InboxEvents::get() {
	Vector<InboxEvent^>^ result = ref new Vector<InboxEvent^>;
	String^ searchPhrase = this->calendar->SearchPhrase;

	std::wstring wsstr(searchPhrase->Data());

	//setup converter
	using convert_type = std::codecvt_utf8<wchar_t>;
	std::wstring_convert<convert_type, wchar_t> converter;

	//use converter (.to_bytes: wstr->str, .from_bytes: str->wstr)
	std::string phrase = converter.to_bytes(wsstr);
	std::transform(phrase.begin(), phrase.end(), phrase.begin(), ::toupper);

	for (int i = 0; i < this->calendar->InboxEvents->Size; i++) {

		std::wstring titlestr(this->calendar->InboxEvents->GetAt(i)->Title->Data());
		std::string title = converter.to_bytes(titlestr);
		std::transform(title.begin(), title.end(), title.begin(), ::toupper);

		if (title.find(phrase) != std::string::npos) {
			result->Append(this->calendar->InboxEvents->GetAt(i));
		}
	}

	return result;
}

IObservableVector<PlannedEvent^>^ SearchPageModel::PlannedEvents::get() {
	Vector<PlannedEvent^>^ result = ref new Vector<PlannedEvent^>;
	String^ searchPhrase = this->calendar->SearchPhrase;

	std::wstring wsstr(searchPhrase->Data());

	//setup converter
	using convert_type = std::codecvt_utf8<wchar_t>;
	std::wstring_convert<convert_type, wchar_t> converter;

	//use converter (.to_bytes: wstr->str, .from_bytes: str->wstr)
	std::string phrase = converter.to_bytes(wsstr);
	std::transform(phrase.begin(), phrase.end(), phrase.begin(), ::toupper);

	for (int i = 0; i < this->calendar->PlannedEvents->Size; i++) {

		std::wstring titlestr(this->calendar->PlannedEvents->GetAt(i)->Title->Data());
		std::string title = converter.to_bytes(titlestr);
		std::transform(title.begin(), title.end(), title.begin(), ::toupper);

		int d = this->calendar->PlannedEvents->GetAt(i)->Date % 100;
		int m = (this->calendar->PlannedEvents->GetAt(i)->Date % 10000 - d) / 100;
		int y = this->calendar->PlannedEvents->GetAt(i)->Date / 10000;

		String^ evDate = d + L"." + m + L"." + y;
		std::wstring datestr(evDate->Data());
		std::string date = converter.to_bytes(datestr);

		if (title.find(phrase) != std::string::npos || date.compare(phrase) == 0) {
			result->Append(this->calendar->PlannedEvents->GetAt(i));
		}
	}

	return result;
}