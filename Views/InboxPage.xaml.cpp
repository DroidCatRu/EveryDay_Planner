#include "pch.h"
#include "InboxPage.xaml.h"
#include "EditEventPage.xaml.h"
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


InboxPage::InboxPage() {
	InitializeComponent();
}

void InboxPage::OnNavigatedTo(NavigationEventArgs^ e) {
	if (e->Parameter != nullptr) {
		((InboxPageModel^)DataContext)->Cal = (Calendar^)e->Parameter;
	}
	else {
		((InboxPageModel^)DataContext)->Cal = ref new Calendar;
	}
}

void EveryDay::InboxPage::Item_Tapped(Platform::Object^ sender, Windows::UI::Xaml::Input::TappedRoutedEventArgs^ e) {
	FrameworkElement^ senderElement = (FrameworkElement^)sender;

	FlyoutBase^ flyout = FlyoutBase::GetAttachedFlyout(senderElement);
	flyout->ShowAt(senderElement);
}


void EveryDay::InboxPage::EditItem_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e) {

	FrameworkElement^ senderElement = (FrameworkElement^)sender;

	if (senderElement->DataContext != nullptr) {
		((InboxPageModel^)DataContext)->Cal->SelectedEventId = ((InboxEvent^)senderElement->DataContext)->Id;
	}

	Windows::UI::Xaml::Controls::Frame^ mainFrame = (Windows::UI::Xaml::Controls::Frame^) Window::Current->Content;
	MainPage^ mainPage = (MainPage^)mainFrame->Content;

	mainPage->NavigateToEdit(((InboxPageModel^)DataContext)->Cal);
}


void EveryDay::InboxPage::RemoveItem_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e) {

	FrameworkElement^ senderElement = (FrameworkElement^)sender;

	if (senderElement->DataContext != nullptr) {
		((InboxPageModel^)DataContext)->Cal->removeEventWithId(((InboxEvent^)senderElement->DataContext)->Id);
	}
	Calendar^ tmpcal = ((InboxPageModel^)DataContext)->Cal;
	tmpcal->save();
}

void EveryDay::InboxPage::CheckBox_Checked(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e) {
	if (Events->IsLoaded) {
		FrameworkElement^ senderCheckBox = (FrameworkElement^)sender;
		FrameworkElement^ senderItem = (FrameworkElement^)senderCheckBox->Parent;
		InboxEvent^ ev = (InboxEvent^)senderItem->DataContext;
		if (ev != nullptr && ev->IsDone == false) {
			ev->IsDone = true;
			Calendar^ tmpcal = ((InboxPageModel^)DataContext)->Cal;
			tmpcal->save();
		}
	}
}


void EveryDay::InboxPage::CheckBox_Unchecked(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e) {
	if (Events->IsLoaded) {
		FrameworkElement^ senderCheckBox = (FrameworkElement^)sender;
		FrameworkElement^ senderItem = (FrameworkElement^)senderCheckBox->Parent;
		InboxEvent^ ev = (InboxEvent^)senderItem->DataContext;
		if (ev != nullptr && ev->IsDone == true) {
			ev->IsDone = false;
			Calendar^ tmpcal = ((InboxPageModel^)DataContext)->Cal;
			tmpcal->save();
		}
	}
}
