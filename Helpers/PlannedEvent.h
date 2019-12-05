#pragma once
#include "Helpers/BindableBase.h"
#include "Helpers/InboxEvent.h"

namespace EveryDay {

	[Windows::UI::Xaml::Data::Bindable]
	public ref class PlannedEvent sealed : BindableBase {

	public:
		property Platform::String^ Title {
			Platform::String^ get() { return this->title; }
			void set(Platform::String^ Title) {
				this->title = Title;
				OnPropertyChanged("Title");
			}
		}
		property long long Id {
			long long get() {
				return this->id;
			}
			void set(long long Id) {
				this->id = Id;
			}
		}
		property bool IsDone {
			bool get() { return this->isDone; }
			void set(bool IsDone) {
				this->isDone = IsDone;
				OnPropertyChanged("IsVisible");
				OnPropertyChanged("IsDone");
			}
		}
		property bool IsVisible {
			bool get() { return !this->isDone; }
		}
		property Platform::String^ TimeInCard {
			Platform::String^ get() { return this->timeincard; }
			void set(Platform::String^ TimeInCard) {
				this->timeincard = TimeInCard;
				OnPropertyChanged("TimeInCard");
			}
		}
		property int Start {
			int get() { return this->start; }
			void set(int Start) {
				this->start = Start;
				this->TimeInCard = (this->start / 100).ToString() + L":" + (this->start % 100).ToString();
				OnPropertyChanged("TimeInCard");
				OnPropertyChanged("Start");
			}
		}
		property int Date {
			int get() { return this->date; }
			void set(int Date) {
				this->date = Date;
				OnPropertyChanged("Date");
			}
		}

		PlannedEvent();
		PlannedEvent(InboxEvent^ ev, int Start, int Date);
		PlannedEvent(Platform::String^ Title,
			int Start,
			int Date,
			long long Id,
			bool IsDone);

	private:
		Platform::String^ title;
		long long id;
		bool isDone;
		int start;
		int date;
		Platform::String^ timeincard;
	};
}
