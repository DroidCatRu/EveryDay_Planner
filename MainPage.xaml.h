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

	private:
		void NavView_Loaded();
		void NavView_ItemInvoked(Microsoft::UI::Xaml::Controls::NavigationView sender, Microsoft::UI::Xaml::Controls::NavigationViewItemInvokedEventArgs args);
		Calendar^ calendar = ref new Calendar;
	};
}
