#pragma once

#include "Helpers/Calendar.h"
#include "Helpers/BindableBase.h"
#include "Helpers/InboxEvent.h"

using namespace EveryDay;
using namespace Platform;
using namespace Windows::Foundation::Collections;
using namespace Platform::Collections;

namespace EveryDay {

	namespace ViewModels {

		[Windows::UI::Xaml::Data::Bindable]
		public ref class InboxPageModel sealed : BindableBase {

		public:
			InboxPageModel() { this->calendar = ref new Calendar; }

			property IObservableVector<InboxEvent^>^ InboxEvents {
				IObservableVector<InboxEvent^>^ get() { return this->inboxEvents; }
			}

			property Calendar^ Cal {
				Calendar^ get() { return this->calendar; }
				void set(Calendar^ Cal);
			}

		private:
			Calendar^ calendar;
			Vector<InboxEvent^>^ inboxEvents = ref new Vector<InboxEvent^>;

			Vector<InboxEvent^>^ sortById(Vector<InboxEvent^>^ eventsdata, int left, int right);
		};
	}
}