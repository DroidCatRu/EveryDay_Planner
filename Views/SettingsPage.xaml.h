#pragma once

#include "Views\SettingsPage.g.h"
#include "Helpers/Calendar.h"

using namespace Windows::UI::Xaml::Controls;

namespace EveryDay {

	[Windows::Foundation::Metadata::WebHostHidden]
	public ref class SettingsPage sealed {
	public:
		SettingsPage();

	protected:
		virtual void OnNavigatedTo(Windows::UI::Xaml::Navigation::NavigationEventArgs^ e) override;

	private:
		Calendar^ calendar;
		void DefPager_SelectionChanged(Platform::Object^ sender, Windows::UI::Xaml::Controls::SelectionChangedEventArgs^ e);
		void ClearDoneButton_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void ClearAllButton_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void OnPrimaryButtonClick(ContentDialog^ sender, ContentDialogButtonClickEventArgs^ args);
	};
}
