#include "pch.h"

#include "MainPage.xaml.h"

#include "SearchResults.xaml.h"
#include "ViewModels/SearchPageModel.h"

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

SearchResults::SearchResults() {
	InitializeComponent();
}

void SearchResults::OnNavigatedTo(NavigationEventArgs^ e) {
	if (e->Parameter != nullptr) {
		((SearchPageModel^)DataContext)->Cal = (Calendar^)e->Parameter;
	}
	else {
		((SearchPageModel^)DataContext)->Cal = ref new Calendar;
	}
}

void EveryDay::SearchResults::Item_Tapped(Platform::Object^ sender, Windows::UI::Xaml::Input::TappedRoutedEventArgs^ e) {
	FrameworkElement^ senderElement = (FrameworkElement^)sender;

	FlyoutBase^ flyout = FlyoutBase::GetAttachedFlyout(senderElement);
	flyout->ShowAt(senderElement);
}


void EveryDay::SearchResults::Inbox_EditItem_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e) {

	FrameworkElement^ senderElement = (FrameworkElement^)sender;

	if (senderElement->DataContext != nullptr) {
		((SearchPageModel^)DataContext)->Cal->SelectedEventId = ((InboxEvent^)senderElement->DataContext)->Id;
	}

	Windows::UI::Xaml::Controls::Frame^ mainFrame = (Windows::UI::Xaml::Controls::Frame^) Window::Current->Content;
	MainPage^ mainPage = (MainPage^)mainFrame->Content;

	mainPage->NavigateToEdit(((SearchPageModel^)DataContext)->Cal);
}


void EveryDay::SearchResults::Inbox_RemoveItem_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e) {

	FrameworkElement^ senderElement = (FrameworkElement^)sender;

	if (senderElement->DataContext != nullptr) {
		((SearchPageModel^)DataContext)->Cal->removeEventWithId(((InboxEvent^)senderElement->DataContext)->Id);
	}
	Calendar^ tmpcal = ((SearchPageModel^)DataContext)->Cal;
	tmpcal->save();
}

void EveryDay::SearchResults::Inbox_CheckBox_Checked(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e) {
	if (Inbox->IsLoaded) {
		FrameworkElement^ senderCheckBox = (FrameworkElement^)sender;
		FrameworkElement^ senderItem = (FrameworkElement^)senderCheckBox->Parent;
		InboxEvent^ ev = (InboxEvent^)senderItem->DataContext;
		if (ev != nullptr && ev->IsDone == false) {
			ev->IsDone = true;
			Calendar^ tmpcal = ((SearchPageModel^)DataContext)->Cal;
			tmpcal->save();
		}
	}
}


void EveryDay::SearchResults::Inbox_CheckBox_Unchecked(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e) {
	if (Inbox->IsLoaded) {
		FrameworkElement^ senderCheckBox = (FrameworkElement^)sender;
		FrameworkElement^ senderItem = (FrameworkElement^)senderCheckBox->Parent;
		InboxEvent^ ev = (InboxEvent^)senderItem->DataContext;
		if (ev != nullptr && ev->IsDone == true) {
			ev->IsDone = false;
			Calendar^ tmpcal = ((SearchPageModel^)DataContext)->Cal;
			tmpcal->save();
		}
	}
}

void EveryDay::SearchResults::Planned_EditItem_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e) {

	FrameworkElement^ senderElement = (FrameworkElement^)sender;

	if (senderElement->DataContext != nullptr) {
		((SearchPageModel^)DataContext)->Cal->SelectedEventId = ((PlannedEvent^)senderElement->DataContext)->Id;
	}

	Windows::UI::Xaml::Controls::Frame^ mainFrame = (Windows::UI::Xaml::Controls::Frame^) Window::Current->Content;
	MainPage^ mainPage = (MainPage^)mainFrame->Content;

	mainPage->NavigateToEdit(((SearchPageModel^)DataContext)->Cal);
}

void EveryDay::SearchResults::Planned_RemoveItem_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e) {

	FrameworkElement^ senderElement = (FrameworkElement^)sender;

	if (senderElement->DataContext != nullptr) {
		((SearchPageModel^)DataContext)->Cal->removeEventWithId(((PlannedEvent^)senderElement->DataContext)->Id);
	}
	Calendar^ tmpcal = ((SearchPageModel^)DataContext)->Cal;
	tmpcal->save();
}

void EveryDay::SearchResults::Planned_CheckBox_Checked(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e) {
	if (Planned->IsLoaded) {
		FrameworkElement^ senderCheckBox = (FrameworkElement^)sender;
		FrameworkElement^ senderItem = (FrameworkElement^)senderCheckBox->Parent;
		PlannedEvent^ ev = (PlannedEvent^)senderItem->DataContext;
		if (ev != nullptr && ev->IsDone == false) {
			ev->IsDone = true;
			Calendar^ tmpcal = ((SearchPageModel^)DataContext)->Cal;
			tmpcal->save();
		}
	}
}


void EveryDay::SearchResults::Planned_CheckBox_Unchecked(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e) {
	if (Planned->IsLoaded) {
		FrameworkElement^ senderCheckBox = (FrameworkElement^)sender;
		FrameworkElement^ senderItem = (FrameworkElement^)senderCheckBox->Parent;
		PlannedEvent^ ev = (PlannedEvent^)senderItem->DataContext;
		if (ev != nullptr && ev->IsDone == true) {
			ev->IsDone = false;
			Calendar^ tmpcal = ((SearchPageModel^)DataContext)->Cal;
			tmpcal->save();
		}
	}
}
