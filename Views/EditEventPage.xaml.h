#pragma once

#include "Views\EditEventPage.g.h"

#include "Helpers/Calendar.h"

namespace EveryDay {
	
	[Windows::Foundation::Metadata::WebHostHidden]
	public ref class EditEventPage sealed {

	public:
		EditEventPage();

	protected:
		virtual void OnNavigatedTo(Windows::UI::Xaml::Navigation::NavigationEventArgs^ e) override;

	private:
		Calendar^ calendar;

		void CheckBox_Checked(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void CheckBox_Unchecked(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void AddButton_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void CancelButton_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
	};
}
