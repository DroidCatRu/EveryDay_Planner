#pragma once

#include "Views\SearchResults.g.h"
#include "ViewModels/SearchPageModel.h"

namespace EveryDay {

	[Windows::Foundation::Metadata::WebHostHidden]
	public ref class SearchResults sealed {

	public:
		SearchResults();

	protected:
		virtual void OnNavigatedTo(Windows::UI::Xaml::Navigation::NavigationEventArgs^ e) override;

	private:
		void Item_Tapped(Platform::Object^ sender, Windows::UI::Xaml::Input::TappedRoutedEventArgs^ e);

		void Inbox_EditItem_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void Inbox_RemoveItem_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void Inbox_CheckBox_Checked(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void Inbox_CheckBox_Unchecked(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);

		void Planned_EditItem_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void Planned_RemoveItem_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void Planned_CheckBox_Checked(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void Planned_CheckBox_Unchecked(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
	};
}
