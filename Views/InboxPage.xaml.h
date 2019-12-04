#pragma once

#include "Views\InboxPage.g.h"
#include "ViewModels/InboxPageModel.h"

using namespace EveryDay;
using namespace EveryDay::ViewModels;

namespace EveryDay {
	
	[Windows::Foundation::Metadata::WebHostHidden]
	public ref class InboxPage sealed {

	public:
		InboxPage();

	protected:
		virtual void OnNavigatedTo(Windows::UI::Xaml::Navigation::NavigationEventArgs^ e) override;
	private:
		void Item_Tapped(Platform::Object^ sender, Windows::UI::Xaml::Input::TappedRoutedEventArgs^ e);
		void EditItem_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void RemoveItem_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
	};
}
