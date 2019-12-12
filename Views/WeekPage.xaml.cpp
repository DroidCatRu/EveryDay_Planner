#include "pch.h"
#include "WeekPage.xaml.h"
#include "EditEventPage.xaml.h"
#include "MainPage.xaml.h"

#include "ViewModels/WeekPageModel.h"

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


WeekPage::WeekPage() {
	InitializeComponent();
}

void WeekPage::OnNavigatedTo(NavigationEventArgs^ e) {
	if (e->Parameter != nullptr) {
		((WeekPageModel^)DataContext)->Cal = (Calendar^)e->Parameter;
	}
	else {
		((WeekPageModel^)DataContext)->Cal = ref new Calendar;
	}
}

void EveryDay::WeekPage::Item_Tapped(Platform::Object^ sender, Windows::UI::Xaml::Input::TappedRoutedEventArgs^ e) {
	FrameworkElement^ senderElement = (FrameworkElement^)sender;

	FlyoutBase^ flyout = FlyoutBase::GetAttachedFlyout(senderElement);
	flyout->ShowAt(senderElement);
}

void EveryDay::WeekPage::EditItem_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e) {

	FrameworkElement^ senderElement = (FrameworkElement^)sender;

	if (senderElement->DataContext != nullptr) {
		((WeekPageModel^)DataContext)->Cal->SelectedEventId = ((PlannedEvent^)senderElement->DataContext)->Id;
	}

	Windows::UI::Xaml::Controls::Frame^ mainFrame = (Windows::UI::Xaml::Controls::Frame^) Window::Current->Content;
	MainPage^ mainPage = (MainPage^)mainFrame->Content;

	mainPage->NavigateToEdit(((WeekPageModel^)DataContext)->Cal);
}

void EveryDay::WeekPage::RemoveItem_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e) {

	FrameworkElement^ senderElement = (FrameworkElement^)sender;

	if (senderElement->DataContext != nullptr) {
		((WeekPageModel^)DataContext)->Cal->removeEventWithId(((PlannedEvent^)senderElement->DataContext)->Id);
	}
	Calendar^ tmpcal = ((WeekPageModel^)DataContext)->Cal;
	tmpcal->save();
}

void EveryDay::WeekPage::CheckBox_Checked(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e) {
	if (OverdueList->IsLoaded && MondayList->IsLoaded && TuesdayList->IsLoaded && WednesdayList->IsLoaded && ThursdayList->IsLoaded && FridayList->IsLoaded && SaturdayList->IsLoaded && SundayList->IsLoaded) {
		FrameworkElement^ senderCheckBox = (FrameworkElement^)sender;
		FrameworkElement^ senderItem = (FrameworkElement^)senderCheckBox->Parent;
		PlannedEvent^ ev = (PlannedEvent^)senderItem->DataContext;
		if (ev != nullptr && ev->IsDone == false) {
			ev->IsDone = true;
			Calendar^ tmpcal = ((WeekPageModel^)DataContext)->Cal;
			tmpcal->save();
		}
	}
}

void EveryDay::WeekPage::CheckBox_Unchecked(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e) {
	if (OverdueList->IsLoaded && MondayList->IsLoaded && TuesdayList->IsLoaded && WednesdayList->IsLoaded && ThursdayList->IsLoaded && FridayList->IsLoaded && SaturdayList->IsLoaded && SundayList->IsLoaded) {
		FrameworkElement^ senderCheckBox = (FrameworkElement^)sender;
		FrameworkElement^ senderItem = (FrameworkElement^)senderCheckBox->Parent;
		PlannedEvent^ ev = (PlannedEvent^)senderItem->DataContext;
		if (ev != nullptr && ev->IsDone == true) {
			ev->IsDone = false;
			Calendar^ tmpcal = ((WeekPageModel^)DataContext)->Cal;
			tmpcal->save();
		}
	}
}
