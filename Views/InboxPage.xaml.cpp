#include "pch.h"
#include "InboxPage.xaml.h"

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


InboxPage::InboxPage() {
	InitializeComponent();
}

void InboxPage::OnNavigatedTo(NavigationEventArgs^ e) {
	if (e->Parameter != nullptr) {
		((InboxPageModel^)DataContext)->Cal = (Calendar^)e->Parameter;
	}
	else {
		((InboxPageModel^)DataContext)->Cal = ref new Calendar;
	}
}