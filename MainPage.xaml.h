#pragma once

#include "MainPage.g.h"
#include "Helpers/Calendar.h"

namespace EveryDay {
	
	public ref class MainPage sealed {

	public:
		MainPage();
		void NavigateToEdit(Calendar^ cal);
		void NavigateToInbox(Calendar^ cal);
		void NavigateToToday(Calendar^ cal);
		void NavigateToWeek(Calendar^ cal);
		void NavigateToSettings(Calendar^ cal);
		void NavigateToSearch(Calendar^ cal);
		void NavigateToDefault(Calendar^ cal);

	private:
		void NavView_Loaded();
		void NavView_ItemInvoked(Microsoft::UI::Xaml::Controls::NavigationView sender, Microsoft::UI::Xaml::Controls::NavigationViewItemInvokedEventArgs args);
		Calendar^ calendar = ref new Calendar;
		void AutoSuggestBox_QuerySubmitted(Windows::UI::Xaml::Controls::AutoSuggestBox^ sender, Windows::UI::Xaml::Controls::AutoSuggestBoxQuerySubmittedEventArgs^ args);
	};
}
