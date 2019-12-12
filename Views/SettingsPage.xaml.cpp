#include "pch.h"
#include "SettingsPage.xaml.h"
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

SettingsPage::SettingsPage() {
	InitializeComponent();
	auto resourceLoader = Windows::ApplicationModel::Resources::ResourceLoader::GetForCurrentView();
	DefPager->Items->Append(resourceLoader->GetString("Inbox"));
	DefPager->Items->Append(resourceLoader->GetString("Today"));
	DefPager->Items->Append(resourceLoader->GetString("Week"));
}

void SettingsPage::OnNavigatedTo(NavigationEventArgs^ e) {
	if (e->Parameter != nullptr) {
		this->calendar = (Calendar^)e->Parameter;
		DefPager->SelectedIndex = this->calendar->DefaultPage;
	}
	else {
		this->calendar = ref new Calendar;
		DefPager->SelectedIndex = 0;
	}
}

void EveryDay::SettingsPage::DefPager_SelectionChanged(Platform::Object^ sender, Windows::UI::Xaml::Controls::SelectionChangedEventArgs^ e) {
	this->calendar->DefaultPage = DefPager->SelectedIndex;
	this->calendar->save();
}


void EveryDay::SettingsPage::ClearDoneButton_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e) {
	for (int i = 0; i < this->calendar->InboxEvents->Size; i++) {
		if (this->calendar->InboxEvents->GetAt(i)->IsDone) {
			this->calendar->InboxEvents->RemoveAt(i);
		}
	}

	for (int i = 0; i < this->calendar->PlannedEvents->Size; i++) {
		if (this->calendar->PlannedEvents->GetAt(i)->IsDone) {
			this->calendar->PlannedEvents->RemoveAt(i);
		}
	}

	this->calendar->save();
}


void EveryDay::SettingsPage::ClearAllButton_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e) {
	ContentDialog^ dialog = ref new ContentDialog();
	auto resourceLoader = Windows::ApplicationModel::Resources::ResourceLoader::GetForCurrentView();

	dialog->Title = resourceLoader->GetString("ClearAllConfirm");
	dialog->Content = resourceLoader->GetString("CantBeUndone");
	dialog->IsSecondaryButtonEnabled = true;
	dialog->PrimaryButtonText = resourceLoader->GetString("ConfirmDeletion");
	dialog->SecondaryButtonText = resourceLoader->GetString("CancelDeletion");
	dialog->PrimaryButtonClick += ref new Windows::Foundation::TypedEventHandler<ContentDialog^, ContentDialogButtonClickEventArgs^>(this, &SettingsPage::OnPrimaryButtonClick);
	dialog->ShowAsync();
}

void SettingsPage::OnPrimaryButtonClick(ContentDialog^ sender, ContentDialogButtonClickEventArgs^ args) {
	this->calendar->InboxEvents->Clear();
	this->calendar->PlannedEvents->Clear();
	this->calendar->save();
}