#pragma once

#include <collection.h>
#include <ctime>

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
				IObservableVector<PlannedEvent^>^ get();
			}

			property IObservableVector<PlannedEvent^>^ OverdueEvents {
				IObservableVector<PlannedEvent^>^ get();
			}

			property Calendar^ Cal {
				Calendar^ get() { return this->calendar; }
				void set(Calendar^ Cal);
			}

			property long long SelectedEventId {
				long long get() { return this->calendar->SelectedEventId; }
				void set(long long SelectedEventId) { this->calendar->SelectedEventId = SelectedEventId; }
			}

			property String^ TodayString {
				String^ get() {
					std::time_t t = std::time(0);
					std::tm now;
					localtime_s(&now, &t);
					return now.tm_mday + L" " + this->calendar->getMonthName(now.tm_mon+1);
				}
			}

			property bool HasOverdue {
				bool get() { return this->hasOverdue; }
			}

			void save() { this->calendar->save(); }

		private:
			Calendar^ calendar;
			Vector<PlannedEvent^>^ sortByTime(Vector<PlannedEvent^>^ events, int left, int right);
			bool hasOverdue = false;
		};
	}
}