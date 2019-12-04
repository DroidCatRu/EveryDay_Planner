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
}


void EveryDay::EditEventPage::AddButton_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e) {
	//TODO: add event to calendar or replace existing one by id and go back to previous screen

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
