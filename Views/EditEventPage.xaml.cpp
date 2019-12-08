#include "pch.h"

#include <ctime>

#include "EditEventPage.xaml.h"
#include "InboxPage.xaml.h"
#include "MainPage.xaml.h"

using namespace EveryDay;

using namespace Platform;
using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;
using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Controls;
using namespace Windows::UI::Xaml::Controls::Primitives;
using namespace Windows::UI::Xaml::Data;
using namespace Windows::UI::Xaml::Input;
using namespace Windows::UI::Xaml::Media;
using namespace Windows::UI::Xaml::Navigation;


EditEventPage::EditEventPage() {
	InitializeComponent();
}

void EditEventPage::OnNavigatedTo(Windows::UI::Xaml::Navigation::NavigationEventArgs^ e) {
	if (e->Parameter != nullptr) {
		this->calendar = (Calendar^)e->Parameter;
		if (this->calendar->SelectedEventId > 0) {

			auto resourceLoader = Windows::ApplicationModel::Resources::ResourceLoader::GetForCurrentView();
			AddButton->Content = resourceLoader->GetString("SaveEvent");
			Object^ gotEvent = this->calendar->getEvent(this->calendar->SelectedEventId);

			if (gotEvent->GetType()->ToString() == InboxEvent::typeid->ToString()) {
				Titler->Text = ((InboxEvent^)gotEvent)->Title;
				isPlannedCheckBox->IsChecked = false;
			}
			else if (gotEvent->GetType()->ToString() == PlannedEvent::typeid->ToString()) {
				Titler->Text = ((PlannedEvent^)gotEvent)->Title;
				isPlannedCheckBox->IsChecked = true;

				TimeSpan t;
				t.Duration = (_int64)((_int64)((((PlannedEvent^)gotEvent)->Start / 100) * 60 + ((PlannedEvent^)gotEvent)->Start % 100) * (_int64)600000000);
				Starter->SelectedTime = t;

				std::tm inittime;
				inittime.tm_year = ((PlannedEvent^)gotEvent)->Date / 10000 - 1900;
				inittime.tm_mon = (((PlannedEvent^)gotEvent)->Date % 10000) / 100 - 1;
				inittime.tm_mday = ((PlannedEvent^)gotEvent)->Date % 100;
				inittime.tm_hour = 0;
				inittime.tm_min = 0;
				inittime.tm_sec = 0;
				std::time_t f = std::mktime(&inittime);

				DateTime initdate;
				initdate.UniversalTime = (f + 11644473600) * 10000000;
				Dater->Date = initdate;
			}
		}
		else {
			auto resourceLoader = Windows::ApplicationModel::Resources::ResourceLoader::GetForCurrentView();
			AddButton->Content = resourceLoader->GetString("AddEvent");
		}
	}
	else {
		this->calendar = ref new Calendar;
	}
}

void EveryDay::EditEventPage::CheckBox_Checked(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e) {
	DatePlan->Visibility = Windows::UI::Xaml::Visibility::Visible;
}

void EveryDay::EditEventPage::CheckBox_Unchecked(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e) {
	DatePlan->Visibility = Windows::UI::Xaml::Visibility::Collapsed;
	Starter->SelectedTime = nullptr;
	Dater->Date = nullptr;
}

void EveryDay::EditEventPage::AddButton_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e) {
	//TODO: add event to calendar or replace existing one by id and go back to previous screen
	Object^ newEvent;
	bool isEventSet = false;
	bool isPlannedEventSet = false;

	AlertMessage->Text = L"";

	if (Titler->Text->Length() == 0) {
		auto resourceLoader = Windows::ApplicationModel::Resources::ResourceLoader::GetForCurrentView();
		AlertMessage->Text = resourceLoader->GetString("TitleNotSet");
	}
	else {
		if (this->calendar->SelectedEventId == 0) {
			//create new event
			if (Starter->SelectedTime == nullptr && Dater->Date == nullptr) {
				//time and date are not selected, creating new inbox event
				newEvent = ref new InboxEvent;
				((InboxEvent^)newEvent)->Title = Titler->Text;
				((InboxEvent^)newEvent)->IsDone = false;
				((InboxEvent^)newEvent)->Id = this->calendar->getNewId();
				this->calendar->InboxEvents->Append((InboxEvent^)newEvent);
				this->calendar->save();
				isEventSet = true;
			}
			else if (Starter->SelectedTime != nullptr && Dater->Date == nullptr) {
				//only time selected
				auto resourceLoader = Windows::ApplicationModel::Resources::ResourceLoader::GetForCurrentView();
				AlertMessage->Text = resourceLoader->GetString("DateNotSet");
			}
			else if (Starter->SelectedTime == nullptr && Dater->Date != nullptr) {
				//only date selected
				auto resourceLoader = Windows::ApplicationModel::Resources::ResourceLoader::GetForCurrentView();
				AlertMessage->Text = resourceLoader->GetString("TimeNotSet");
			}
			else if (Starter->SelectedTime != nullptr && Dater->Date != nullptr) {
				// date and time selected -> create planned event
				newEvent = ref new PlannedEvent;

				((PlannedEvent^)newEvent)->Title = Titler->Text;

				TimeSpan start = Starter->Time;

				int sthours = start.Duration / 36000000000;
				int stminutes = start.Duration / 600000000 - sthours * 60;

				((PlannedEvent^)newEvent)->Start = sthours * 100 + stminutes;

				DateTime date = Dater->Date->Value;

				std::tm now;
				std::time_t loc = (date.UniversalTime / 10000000 - 11644473600); //current date - (-1601 since 1970 in seconds)
				localtime_s(&now, &loc);

				int y = now.tm_year + 1900; //current year
				int m = now.tm_mon + 1;		//current month
				int d = now.tm_mday;		//current day month

				((PlannedEvent^)newEvent)->Date = y * 10000 + m * 100 + d;

				((PlannedEvent^)newEvent)->IsDone = false;

				((PlannedEvent^)newEvent)->Id = this->calendar->getNewId();

				this->calendar->PlannedEvents->Append((PlannedEvent^)newEvent);
				this->calendar->save();
				isEventSet = true;
				isPlannedEventSet = true;
			}
		}

		if (this->calendar->SelectedEventId > 0) {
			//edit existing event
			newEvent = this->calendar->getEvent(this->calendar->SelectedEventId);

			if (newEvent->GetType()->ToString() == InboxEvent::typeid->ToString()) {
				//selected event is inbox event
				if (Starter->SelectedTime == nullptr && Dater->Date == nullptr) {
					//time and date are not selected, change existing inbox event
					((InboxEvent^)newEvent)->Title = Titler->Text;

					int evPos = 0;
					for (int pos = 0; pos < this->calendar->InboxEvents->Size; pos++) {
						if (this->calendar->InboxEvents->GetAt(pos)->Id == this->calendar->SelectedEventId) {
							evPos = pos;
							break;
						}
					}

					this->calendar->InboxEvents->SetAt(evPos, (InboxEvent^)newEvent);
					this->calendar->save();
					isEventSet = true;
				}
				else if (Starter->SelectedTime != nullptr && Dater->Date == nullptr) {
					//only time selected
					auto resourceLoader = Windows::ApplicationModel::Resources::ResourceLoader::GetForCurrentView();
					AlertMessage->Text = resourceLoader->GetString("DateNotSet");
				}
				else if (Starter->SelectedTime == nullptr && Dater->Date != nullptr) {
					//only date selected
					auto resourceLoader = Windows::ApplicationModel::Resources::ResourceLoader::GetForCurrentView();
					AlertMessage->Text = resourceLoader->GetString("TimeNotSet");
				}
				else if (Starter->SelectedTime != nullptr && Dater->Date != nullptr) {
					// date and time selected -> create planned event and delete old inbox event
					((InboxEvent^)newEvent)->Title = Titler->Text;

					TimeSpan start = Starter->Time;
					int sthours = start.Duration / 36000000000;
					int stminutes = start.Duration / 600000000 - sthours * 60;
					int evStart = sthours * 100 + stminutes;

					DateTime date = Dater->Date->Value;

					std::tm now;
					std::time_t loc = (date.UniversalTime / 10000000 - 11644473600); //current date - (-1601 since 1970 in seconds)
					localtime_s(&now, &loc);

					int y = now.tm_year + 1900; //current year
					int m = now.tm_mon + 1;		//current month
					int d = now.tm_mday;		//current day month
					int evDate = y * 10000 + m * 100 + d;

					newEvent = ref new PlannedEvent((InboxEvent^)newEvent, evStart, evDate);

					this->calendar->removeEventWithId(this->calendar->SelectedEventId);
					this->calendar->PlannedEvents->Append((PlannedEvent^)newEvent);
					this->calendar->save();
					isEventSet = true;
					isPlannedEventSet = true;
				}
			}
			else if (newEvent->GetType()->ToString() == PlannedEvent::typeid->ToString()) {
				
				//selected planned event
				
				if (Starter->SelectedTime == nullptr && Dater->Date == nullptr) {
					
					//planned to inbox event
					
					InboxEvent^ plannedToInbox = ref new InboxEvent;

					plannedToInbox->Title = Titler->Text;
					plannedToInbox->Id = ((PlannedEvent^)newEvent)->Id;
					plannedToInbox->IsDone = ((PlannedEvent^)newEvent)->IsDone;

					this->calendar->removeEventWithId(this->calendar->SelectedEventId);
					this->calendar->InboxEvents->Append(plannedToInbox);
					this->calendar->save();
					isEventSet = true;
				}
				else if (Starter->SelectedTime != nullptr && Dater->Date == nullptr) {
					//only time selected
					auto resourceLoader = Windows::ApplicationModel::Resources::ResourceLoader::GetForCurrentView();
					AlertMessage->Text = resourceLoader->GetString("DateNotSet");
				}
				else if (Starter->SelectedTime == nullptr && Dater->Date != nullptr) {
					//only date selected
					auto resourceLoader = Windows::ApplicationModel::Resources::ResourceLoader::GetForCurrentView();
					AlertMessage->Text = resourceLoader->GetString("TimeNotSet");
				}
				else if (Starter->SelectedTime != nullptr && Dater->Date != nullptr) {
					
					// date and time selected -> change planned event
					
					((PlannedEvent^)newEvent)->Title = Titler->Text;

					TimeSpan start = Starter->Time;
					int sthours = start.Duration / 36000000000;
					int stminutes = start.Duration / 600000000 - sthours * 60;
					int evStart = sthours * 100 + stminutes;

					((PlannedEvent^)newEvent)->Start = evStart;

					DateTime date = Dater->Date->Value;

					std::tm now;
					std::time_t loc = (date.UniversalTime / 10000000 - 11644473600); //selected date - (1970-1601 years in seconds)
					localtime_s(&now, &loc);

					int y = now.tm_year + 1900; //year
					int m = now.tm_mon + 1;		//month
					int d = now.tm_mday;		//day month
					int evDate = y * 10000 + m * 100 + d;

					((PlannedEvent^)newEvent)->Date = evDate;

					int evPos = 0;
					for (int pos = 0; pos < this->calendar->PlannedEvents->Size; pos++) {
						if (this->calendar->PlannedEvents->GetAt(pos)->Id == this->calendar->SelectedEventId) {
							evPos = pos;
							break;
						}
					}

					this->calendar->PlannedEvents->SetAt(evPos, (PlannedEvent^)newEvent);
					this->calendar->save();
					isEventSet = true;
					isPlannedEventSet = true;
				}
				
			}
		}
	}

	if (isEventSet) {
		Windows::UI::Xaml::Controls::Frame^ mainFrame = (Windows::UI::Xaml::Controls::Frame^) Window::Current->Content;
		MainPage^ mainPage = (MainPage^)mainFrame->Content;
		if (isPlannedEventSet) {
			mainPage->NavigateToToday(this->calendar);
		}
		else {
			mainPage->NavigateToInbox(this->calendar);
		}
	}
}

void EveryDay::EditEventPage::CancelButton_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e) {
	//Just go back without saving entered values

	Windows::UI::Xaml::Controls::Frame^ mainFrame = (Windows::UI::Xaml::Controls::Frame^) Window::Current->Content;
	MainPage^ mainPage = (MainPage^)mainFrame->Content;

	mainPage->NavigateToInbox(this->calendar);
}
