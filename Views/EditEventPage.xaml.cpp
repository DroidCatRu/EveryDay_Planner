#include "pch.h"
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
			}
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
		}
	}

	if (this->calendar->SelectedEventId > 0) {

		newEvent = this->calendar->getEvent(this->calendar->SelectedEventId);

		if (newEvent->GetType()->ToString() == InboxEvent::typeid->ToString()) {
			//selected event is inbox event
			if (Starter->SelectedTime == nullptr && Dater->Date == nullptr) {
				//time and date are not selected, change existing inbox event
				((InboxEvent^)newEvent)->Title = Titler->Text;
				
				int evPos = 0;
				for (int pos = 0; pos < this->calendar->InboxEvents->Size; pos++) {
					if (this->calendar->InboxEvents->GetAt(pos)->Id == ((InboxEvent^)newEvent)->Id) {
						evPos = pos;
						break;
					}
				}
				
				this->calendar->InboxEvents->SetAt(evPos, (InboxEvent^)newEvent);
				this->calendar->save();
			}
			else if (Starter->SelectedTime == nullptr && Dater->Date != nullptr) {
				//only time selected
			}
			else if (Starter->SelectedTime != nullptr && Dater->Date == nullptr) {
				//only date selected
			}
			else if (Starter->SelectedTime != nullptr && Dater->Date != nullptr) {
				// date and time selected -> create planned event and delete old inbox event
			}
		}
		else if (newEvent->GetType()->ToString() == PlannedEvent::typeid->ToString()) {
			//selected event is planned event
			((PlannedEvent^)newEvent)->Title = Titler->Text;
		}
	}

	Windows::UI::Xaml::Controls::Frame^ mainFrame = (Windows::UI::Xaml::Controls::Frame^) Window::Current->Content;
	MainPage^ mainPage = (MainPage^)mainFrame->Content;

	mainPage->NavigateToInbox(this->calendar);
}

void EveryDay::EditEventPage::CancelButton_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e) {
	//Just go back without saving entered values

	Windows::UI::Xaml::Controls::Frame^ mainFrame = (Windows::UI::Xaml::Controls::Frame^) Window::Current->Content;
	MainPage^ mainPage = (MainPage^)mainFrame->Content;

	mainPage->NavigateToInbox(this->calendar);
}
