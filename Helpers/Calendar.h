#pragma once
#include "Helpers/InboxEvent.h"
#include "Helpers/PlannedEvent.h"
#include "Helpers/BindableBase.h"

using namespace EveryDay;

using namespace Platform;
using namespace Windows::Data::Json;
using namespace Windows::Storage;
using namespace Platform::Collections;
using namespace Windows::Foundation::Collections;
using namespace concurrency;

namespace EveryDay {

	[Windows::UI::Xaml::Data::Bindable]
	public ref class Calendar sealed : BindableBase {

	public:
		Calendar() {}

		property long long SelectedEventId {
			long long get() { return this->selectedEventId; }
			void set(long long SelectedEventId) { this->selectedEventId = SelectedEventId; }
		}

		property int DefaultPage {
			int get() { return this->defaultPage; }
			void set(int defPage) { this->defaultPage = defPage; }
		}

		property String^ SearchPhrase {
			String^ get() { return this->searchPhrase; }
			void set(String^ phrase) { this->searchPhrase = phrase; }
		}

		property IObservableVector<InboxEvent^>^ InboxEvents {
			IObservableVector<InboxEvent^>^ get() { return this->inboxEvents; }

			void set(IObservableVector<InboxEvent^>^ events) {
				this->inboxEvents->Clear();

				for (int i = 0; i < events->Size; i++) {
					this->inboxEvents->Append(events->GetAt(i));
				}
				OnPropertyChanged("InboxEvents");
			}
		}

		property IObservableVector<PlannedEvent^>^ PlannedEvents {
			IObservableVector<PlannedEvent^>^ get() { return this->plannedEvents; }

			void set(IObservableVector<PlannedEvent^>^ events) {
				this->plannedEvents->Clear();

				for (int i = 0; i < events->Size; i++) {
					this->plannedEvents->Append(events->GetAt(i));
				}
				OnPropertyChanged("PlannedEvents");
			}
		}

		void addPlannedEvent(PlannedEvent^ Event) { this->plannedEvents->Append(Event); }
		PlannedEvent^ getPlannedEventAt(int i) { return this->plannedEvents->GetAt(i); }
		int getPlannedEventsSize() { return this->plannedEvents->Size; }

		void addInboxEvent(InboxEvent^ Event) { this->inboxEvents->Append(Event); }
		InboxEvent^ getInboxEventAt(int i) { return this->inboxEvents->GetAt(i); }
		int getInboxEventsSize() { return this->inboxEvents->Size; }

		Object^ getEvent(long long id);
		void setEventDone(long long id, bool done);
		void removeEventWithId(long long id);
		long long getNewId();

		void save();
		void setEventsFile(StorageFile^ EventsFile);
		void getFromStr(String^ str);
		String^ getJsonedStr();
		void loadFromFile();

		Platform::String^ getWeekDay(int yy, int mm, int dd) {
			auto resourceLoader = Windows::ApplicationModel::Resources::ResourceLoader::GetForCurrentView();

			int rst =
				dd
				+ ((153 * (mm + 12 * ((14 - mm) / 12) - 3) + 2) / 5)
				+ (365 * (yy + 4800 - ((14 - mm) / 12)))
				+ ((yy + 4800 - ((14 - mm) / 12)) / 4)
				- ((yy + 4800 - ((14 - mm) / 12)) / 100)
				+ ((yy + 4800 - ((14 - mm) / 12)) / 400)
				- 32045;

			switch (rst % 7) {
			case 0:
				return resourceLoader->GetString("dMonday");
			case 1:
				return resourceLoader->GetString("dTuesday");
			case 2:
				return resourceLoader->GetString("dWednesday");
			case 3:
				return resourceLoader->GetString("dThursday");
			case 4:
				return resourceLoader->GetString("dFriday");
			case 5:
				return resourceLoader->GetString("dSaturday");
			case 6:
				return resourceLoader->GetString("dSunday");
			default:
				return "ERROR";
			}
		}
		Platform::String^ getMonthName(int mon) {
			auto resourceLoader = Windows::ApplicationModel::Resources::ResourceLoader::GetForCurrentView();
			
			switch (mon - 1) {
			case 0:
				return resourceLoader->GetString("mJanuary");
			case 1:
				return resourceLoader->GetString("mFebruary");
			case 2:
				return resourceLoader->GetString("mMarch");
			case 3:
				return resourceLoader->GetString("mApril");
			case 4:
				return resourceLoader->GetString("mMay");
			case 5:
				return resourceLoader->GetString("mJune");
			case 6:
				return resourceLoader->GetString("mJuly");
			case 7:
				return resourceLoader->GetString("mAugust");
			case 8:
				return resourceLoader->GetString("mSeptember");
			case 9:
				return resourceLoader->GetString("mOctober");
			case 10:
				return resourceLoader->GetString("mNovember");
			case 11:
				return resourceLoader->GetString("mDecember");
			default:
				return "Undefined";
			}
		}
		int getNumberOfDays(int month, int year)
		{
			//leap year condition, if month is 2
			if (month == 2)
			{
				if ((year % 400 == 0) || (year % 4 == 0 && year % 100 != 0))
					return 29;
				else
					return 28;
			}
			//months which has 31 days
			else if (month == 1 || month == 3 || month == 5 || month == 7 || month == 8
				|| month == 10 || month == 12)
				return 31;
			else
				return 30;
		}

	private:
		Vector<PlannedEvent^>^ plannedEvents = ref new Vector<PlannedEvent^>;
		Vector<InboxEvent^>^ inboxEvents = ref new Vector<InboxEvent^>;
		int dateShowed = 0;
		int defaultPage = 0;
		StorageFile^ eventsFile;
		long long selectedEventId = 0;
		String^ searchPhrase;

		Vector<InboxEvent^>^ sortById(Vector<InboxEvent^>^ eventsdata, int left, int right);
	};
}