#include "pch.h"
#include "MainPage.xaml.h"
#include <ctime>

#include "Views/EditEventPage.xaml.h"
#include "Views/InboxPage.xaml.h"
#include "Views/TodayPage.xaml.h"
#include "Views/WeekPage.xaml.h"
#include "Views/SettingsPage.xaml.h"
#include "Views/SearchResults.xaml.h"

using namespace EveryDay;

using namespace Platform;
using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;
using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Controls::Primitives;
using namespace Windows::UI::Xaml::Data;
using namespace Windows::UI::Xaml::Input;
using namespace Windows::UI::Xaml::Media;
using namespace Windows::UI::Xaml::Navigation;
using namespace Windows::UI::ViewManagement;
using namespace Windows::ApplicationModel::Core;
using namespace Microsoft::UI::Xaml::Controls;
using namespace Windows::UI::Xaml::Interop;
using namespace Windows::Storage;
using namespace Windows::Data::Json;

MainPage::MainPage()
{
	InitializeComponent();

	Window::Current->SetTitleBar(this->AppTitleBar);
	auto coreTitleBar = CoreApplication::GetCurrentView()->TitleBar;
	coreTitleBar->ExtendViewIntoTitleBar = true;

	ApplicationViewTitleBar^ titleBar = ApplicationView::GetForCurrentView()->TitleBar;
	titleBar->ButtonBackgroundColor = Windows::UI::Colors::Transparent;
	titleBar->ButtonInactiveBackgroundColor = Windows::UI::Colors::Transparent;

}

void MainPage::NavView_Loaded() {
	StorageFolder^ folder = ApplicationData::Current->LocalFolder;
	String^ filename = "events.json";

	create_task(folder->CreateFileAsync(filename, CreationCollisionOption::OpenIfExists))
		.then([this](task<StorageFile^> task) mutable {
		StorageFile^ file = task.get();
		this->calendar->setEventsFile(file);

		return FileIO::ReadTextAsync(file);
			}, task_continuation_context::use_default())
		.then([this](task<String^> task) mutable {
				String^ str = task.get();
				this->calendar->getFromStr(str);
			}).then([this]() mutable -> void {

				switch (this->calendar->DefaultPage) {
				case 0:
					ContentFrame->Navigate(InboxPage::typeid, this->calendar);
					NavView->SelectedItem = NavView->MenuItems->GetAt(2);
					break;
				case 1:
					ContentFrame->Navigate(TodayPage::typeid, this->calendar);
					NavView->SelectedItem = NavView->MenuItems->GetAt(3);
					break;
				case 2:
					ContentFrame->Navigate(WeekPage::typeid, this->calendar);
					NavView->SelectedItem = NavView->MenuItems->GetAt(4);
					break;
				default:
					ContentFrame->Navigate(InboxPage::typeid, this->calendar);
					NavView->SelectedItem = NavView->MenuItems->GetAt(2);
					break;
				}
				});
}

void MainPage::NavView_ItemInvoked(Microsoft::UI::Xaml::Controls::NavigationView sender, Microsoft::UI::Xaml::Controls::NavigationViewItemInvokedEventArgs args) {
	if (args.IsSettingsInvoked) {
		NavigateToSettings(this->calendar);
	}
	else {
		String^ selectedView = args.InvokedItemContainer->Tag->ToString();

		if (selectedView != "add") {
			this->calendar->SelectedEventId = 0;
		}

		if (selectedView == "inbox") {
			NavigateToInbox(this->calendar);
		}
		else if (selectedView == "today") {
			NavigateToToday(this->calendar);
		}
		else if (selectedView == "week") {
			NavigateToWeek(this->calendar);
		}
		else if (selectedView == "add") {
			NavigateToEdit(this->calendar);
		}
	}
}

void MainPage::NavigateToEdit(Calendar^ cal) {
	this->calendar = cal;
	if (ContentFrame->Content->GetType()->ToString() != EditEventPage::typeid->ToString()) {
		NavView->SelectedItem = NavView->MenuItems->GetAt(0);
		ContentFrame->Navigate(EditEventPage::typeid, cal);
	}
}

void MainPage::NavigateToInbox(Calendar^ cal) {
	this->calendar = cal;
	if (ContentFrame->Content->GetType()->ToString() != InboxPage::typeid->ToString()) {
		NavView->SelectedItem = NavView->MenuItems->GetAt(2);
		ContentFrame->Navigate(InboxPage::typeid, cal);
	}
}

void MainPage::NavigateToToday(Calendar^ cal) {
	this->calendar = cal;
	if (ContentFrame->Content->GetType()->ToString() != TodayPage::typeid->ToString()) {
		NavView->SelectedItem = NavView->MenuItems->GetAt(3);
		ContentFrame->Navigate(TodayPage::typeid, cal);
	}
}

void MainPage::NavigateToWeek(Calendar^ cal) {
	this->calendar = cal;
	if (ContentFrame->Content->GetType()->ToString() != WeekPage::typeid->ToString()) {
		NavView->SelectedItem = NavView->MenuItems->GetAt(4);
		ContentFrame->Navigate(WeekPage::typeid, cal);
	}
}

void MainPage::NavigateToSettings(Calendar^ cal) {
	this->calendar = cal;
	if (ContentFrame->Content->GetType()->ToString() != SettingsPage::typeid->ToString()) {
		ContentFrame->Navigate(SettingsPage::typeid, cal);
	}
}

void MainPage::NavigateToSearch(Calendar^ cal) {
	this->calendar = cal;
	ContentFrame->Navigate(SearchResults::typeid, cal);
}

void MainPage::NavigateToDefault(Calendar^ cal) {
	this->calendar = cal;
	switch (this->calendar->DefaultPage) {
	case 0:
		NavigateToInbox(this->calendar);
		break;
	case 1:
		NavigateToToday(this->calendar);
		break;
	case 2:
		NavigateToWeek(this->calendar);
		break;
	default:
		NavigateToInbox(this->calendar);
		break;
	}
}

void EveryDay::MainPage::AutoSuggestBox_QuerySubmitted(Windows::UI::Xaml::Controls::AutoSuggestBox^ sender, Windows::UI::Xaml::Controls::AutoSuggestBoxQuerySubmittedEventArgs^ args) {
	this->calendar->SearchPhrase = args->QueryText;
	NavigateToSearch(this->calendar);
}
