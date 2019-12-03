﻿#pragma once

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
	};
}