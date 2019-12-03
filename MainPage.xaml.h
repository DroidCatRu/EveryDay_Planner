#pragma once

#include "MainPage.g.h"
#include "Helpers/Calendar.h"
#include "Views/InboxPage.xaml.h"

namespace EveryDay {
	
	public ref class MainPage sealed {

	public:
		MainPage();

	private:
		void NavView_Loaded();
		void NavView_ItemInvoked(Microsoft::UI::Xaml::Controls::NavigationView sender, Microsoft::UI::Xaml::Controls::NavigationViewItemInvokedEventArgs args);
		Calendar^ calendar = ref new Calendar;
	};
}
