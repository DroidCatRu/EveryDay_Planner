#include "pch.h"
#include "MainPage.xaml.h"
#include <ctime>

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

				std::time_t t = std::time(0);
				std::tm now;
				localtime_s(&now, &t);
				int yearToShow = now.tm_year + 1900;
				int monthToShow = now.tm_mon + 1;
				int dayToShow = now.tm_mday;
				this->calendar->DateShowed = yearToShow * 10000 + monthToShow * 100 + dayToShow;

				//ContentFrame->Navigate(Day::typeid, this->calendar);
				NavView->SelectedItem = NavView->MenuItems->GetAt(0);
				});
}

void MainPage::NavView_ItemInvoked(NavigationView sender, NavigationViewItemInvokedEventArgs args) {
	/*
	if (args.IsSettingsInvoked) {
		NavigateToSettings();
		selectedView = "settings";
	}
	else {
		selectedView = args.InvokedItemContainer->Tag->ToString();

		std::time_t t = std::time(0);
		std::tm now;
		localtime_s(&now, &t);
		yearToShow = now.tm_year + 1900;
		monthToShow = now.tm_mon + 1;
		dayToShow = now.tm_mday;
		this->calendar->DateShowed = yearToShow * 10000 + monthToShow * 100 + dayToShow;

		if (selectedView == "day") {
			NavigateToDayPlan();
		}
		if (selectedView == "week") {
			NavigateToThreeDayPlan();
		}
		if (selectedView == "month") {
			NavigateToMonthPlan();
		}
	}
	*/
}