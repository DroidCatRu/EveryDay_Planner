#pragma once

#include <collection.h>

#include "Helpers/Calendar.h"
#include "Helpers/BindableBase.h"
#include "Helpers/PlannedEvent.h"

using namespace EveryDay;
using namespace Platform;
using namespace Windows::Foundation::Collections;
using namespace Platform::Collections;

namespace EveryDay {

	namespace ViewModels {

		[Windows::UI::Xaml::Data::Bindable]
		public ref class TodayPageModel sealed : BindableBase {

		public:
			TodayPageModel() { this->calendar = ref new Calendar; }

			property IObservableVector<PlannedEvent^>^ TodayEvents {
				IObservableVector<PlannedEvent^>^ get() { return this->calendar->PlannedEvents; }
			}

			property Calendar^ Cal {
				Calendar^ get() { return this->calendar; }
				void set(Calendar^ Cal);
			}

			property long long SelectedEventId {
				long long get() { return this->calendar->SelectedEventId; }
				void set(long long SelectedEventId) { this->calendar->SelectedEventId = SelectedEventId; }
			}

			void save() { this->calendar->save(); }

		private:
			Calendar^ calendar;
		};
	}
}