#pragma once
#include "Helpers/InboxEvent.h"
#include "Helpers/PlannedEvent.h"

using namespace EveryDay;

using namespace Platform;
using namespace Windows::Data::Json;
using namespace Windows::Storage;
using namespace Platform::Collections;
using namespace concurrency;

namespace EveryDay {

	public ref class Calendar sealed {

	public:
		Calendar() {}

		property int DateShowed {
			int get() { return this->dateShowed; }
			void set(int DateShowed) { this->dateShowed = DateShowed; }
		}

		void addPlannedEvent(PlannedEvent^ Event) { this->plannedEvents->Append(Event); }
		PlannedEvent^ getPlannedEventAt(int i) { return this->plannedEvents->GetAt(i); }
		int getPlannedEventsSize() { return this->plannedEvents->Size; }

		void addInboxEvent(InboxEvent^ Event) { this->inboxEvents->Append(Event); }
		InboxEvent^ getInboxEventAt(int i) { return this->inboxEvents->GetAt(i); }
		int getInboxEventsSize() { return this->inboxEvents->Size; }

		void save();
		void setEventsFile(StorageFile^ EventsFile);
		void getFromStr(String^ str);
		String^ getJsonedStr();
		void loadFromFile();

		Platform::String^ getWeekDay(int yy, int mm, int dd) {

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
				return "Monday";
			case 1:
				return "Tuesday";
			case 2:
				return "Wednesday";
			case 3:
				return "Thursday";
			case 4:
				return "Friday";
			case 5:
				return "Saturday";
			case 6:
				return "Sunday";
			default:
				return "ERROR";
			}
		}
		Platform::String^ getMonthName(int mon) {
			switch (mon - 1) {
			case 0:
				return "January";
			case 1:
				return "February";
			case 2:
				return "March";
			case 3:
				return "April";
			case 4:
				return "May";
			case 5:
				return "June";
			case 6:
				return "July";
			case 7:
				return "August";
			case 8:
				return "September";
			case 9:
				return "October";
			case 10:
				return "November";
			case 11:
				return "December";
			default:
				return "ERROR";
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
		StorageFile^ eventsFile;
		long long selectedEventId = 0;
	};
}