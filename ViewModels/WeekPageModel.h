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
		public ref class WeekPageModel sealed : BindableBase {

		public:
			WeekPageModel() { this->calendar = ref new Calendar; }

			property IObservableVector<PlannedEvent^>^ Monday {
				IObservableVector<PlannedEvent^>^ get();
			}

			property IObservableVector<PlannedEvent^>^ Tuesday {
				IObservableVector<PlannedEvent^>^ get();
			}

			property IObservableVector<PlannedEvent^>^ Wednesday {
				IObservableVector<PlannedEvent^>^ get();
			}

			property IObservableVector<PlannedEvent^>^ Thursday {
				IObservableVector<PlannedEvent^>^ get();
			}

			property IObservableVector<PlannedEvent^>^ Friday {
				IObservableVector<PlannedEvent^>^ get();
			}

			property IObservableVector<PlannedEvent^>^ Saturday {
				IObservableVector<PlannedEvent^>^ get();
			}

			property IObservableVector<PlannedEvent^>^ Sunday {
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
					return now.tm_mday + L" " + this->calendar->getMonthName(12);
				}
			}

			property String^ TuesdayString {
				String^ get() {
					int date = getDateIncreased(1);
					int d = date % 100;
					int m = (date % 10000 - d) / 100;

					return d.ToString() + L" " + this->calendar->getMonthName(12);
				}
			}

			property String^ WednesdayString {
				String^ get() {
					int date = getDateIncreased(2);
					int d = date % 100;
					int m = (date % 10000 - d) / 100;

					return d.ToString() + L" " + this->calendar->getMonthName(12);
				}
			}

			property String^ ThursdayString {
				String^ get() {
					int date = getDateIncreased(3);
					int d = date % 100;
					int m = (date % 10000 - d) / 100;

					return d.ToString() + L" " + this->calendar->getMonthName(12);
				}
			}

			property String^ FridayString {
				String^ get() {
					int date = getDateIncreased(4);
					int d = date % 100;
					int m = (date % 10000 - d) / 100;

					return d.ToString() + L" " + this->calendar->getMonthName(12);
				}
			}

			property String^ SaturdayString {
				String^ get() {
					int date = getDateIncreased(5);
					int d = date % 100;
					int m = (date % 10000 - d) / 100;

					return d.ToString() + L" " + this->calendar->getMonthName(12);
				}
			}

			property String^ SundayString {
				String^ get() {
					int date = getDateIncreased(6);
					int d = date % 100;
					int m = (date % 10000 - d) / 100;

					return d.ToString() + L" " + this->calendar->getMonthName(12);
				}
			}

			property String^ WednesdayWeekDay {
				String^ get() {
					int date = getDateIncreased(2);
					int d = date % 100;
					int m = (date % 10000 - d) / 100;
					int y = (date - date % 10000) / 10000;
					return this->calendar->getWeekDay(y, m, d);
				}
			}

			property String^ ThursdayWeekDay {
				String^ get() {
					int date = getDateIncreased(3);
					int d = date % 100;
					int m = (date % 10000 - d) / 100;
					int y = (date - date % 10000) / 10000;
					return this->calendar->getWeekDay(y, m, d);
				}
			}

			property String^ FridayWeekDay {
				String^ get() {
					int date = getDateIncreased(4);
					int d = date % 100;
					int m = (date % 10000 - d) / 100;
					int y = (date - date % 10000) / 10000;
					return this->calendar->getWeekDay(y, m, d);
				}
			}

			property String^ SaturdayWeekDay {
				String^ get() {
					int date = getDateIncreased(5);
					int d = date % 100;
					int m = (date % 10000 - d) / 100;
					int y = (date - date % 10000) / 10000;
					return this->calendar->getWeekDay(y, m, d);
				}
			}

			property String^ SundayWeekDay {
				String^ get() {
					int date = getDateIncreased(6);
					int d = date % 100;
					int m = (date % 10000 - d) / 100;
					int y = (date - date % 10000) / 10000;
					return this->calendar->getWeekDay(y, m, d);
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

			int getDateIncreased(int n);
		};
	}
}