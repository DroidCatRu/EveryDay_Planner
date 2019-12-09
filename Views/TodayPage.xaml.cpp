#include "pch.h"
#include "TodayPage.xaml.h"
#include "EditEventPage.xaml.h"
#include "MainPage.xaml.h"

#include "ViewModels/TodayPageModel.h"

using namespace EveryDay;
using namespace EveryDay::ViewModels;

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


TodayPage::TodayPage() {
	InitializeComponent();
}

void TodayPage::OnNavigatedTo(NavigationEventArgs^ e) {
	if (e->Parameter != nullptr) {
		((TodayPageModel^)DataContext)->Cal = (Calendar^)e->Parameter;
	}
	else {
		((TodayPageModel^)DataContext)->Cal = ref new Calendar;
	}
}

void EveryDay::TodayPage::Item_Tapped(Platform::Object^ sender, Windows::UI::Xaml::Input::TappedRoutedEventArgs^ e) {
	FrameworkElement^ senderElement = (FrameworkElement^)sender;

	FlyoutBase^ flyout = FlyoutBase::GetAttachedFlyout(senderElement);
	flyout->ShowAt(senderElement);
}

void EveryDay::TodayPage::EditItem_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e) {

	FrameworkElement^ senderElement = (FrameworkElement^)sender;

	if (senderElement->DataContext != nullptr) {
		((TodayPageModel^)DataContext)->Cal->SelectedEventId = ((PlannedEvent^)senderElement->DataContext)->Id;
	}

	Windows::UI::Xaml::Controls::Frame^ mainFrame = (Windows::UI::Xaml::Controls::Frame^) Window::Current->Content;
	MainPage^ mainPage = (MainPage^)mainFrame->Content;

	mainPage->NavigateToEdit(((TodayPageModel^)DataContext)->Cal);
}

void EveryDay::TodayPage::RemoveItem_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e) {

	FrameworkElement^ senderElement = (FrameworkElement^)sender;

	if (senderElement->DataContext != nullptr) {
		((TodayPageModel^)DataContext)->Cal->removeEventWithId(((PlannedEvent^)senderElement->DataContext)->Id);
	}
	Calendar^ tmpcal = ((TodayPageModel^)DataContext)->Cal;
	tmpcal->save();
}

void EveryDay::TodayPage::CheckBox_Checked(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e) {
	if (Events->IsLoaded) {
		FrameworkElement^ senderCheckBox = (FrameworkElement^)sender;
		FrameworkElement^ senderItem = (FrameworkElement^)senderCheckBox->Parent;
		PlannedEvent^ ev = (PlannedEvent^)senderItem->DataContext;
		if (ev != nullptr && ev->IsDone == false) {
			ev->IsDone = true;
			Calendar^ tmpcal = ((TodayPageModel^)DataContext)->Cal;
			tmpcal->save();
		}
	}
}

void EveryDay::TodayPage::CheckBox_Unchecked(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e) {
	if (Events->IsLoaded) {
		FrameworkElement^ senderCheckBox = (FrameworkElement^)sender;
		FrameworkElement^ senderItem = (FrameworkElement^)senderCheckBox->Parent;
		PlannedEvent^ ev = (PlannedEvent^)senderItem->DataContext;
		if (ev != nullptr && ev->IsDone == true) {
			ev->IsDone = false;
			Calendar^ tmpcal = ((TodayPageModel^)DataContext)->Cal;
			tmpcal->save();
		}
	}
}
