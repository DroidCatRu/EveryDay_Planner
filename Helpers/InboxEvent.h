#pragma once
#include "Helpers/BindableBase.h"

namespace EveryDay {

	[Windows::UI::Xaml::Data::Bindable]
	public ref class InboxEvent sealed : BindableBase {

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

		InboxEvent();
		InboxEvent(InboxEvent^ ev);
		InboxEvent(Platform::String^ Title,
			long long Id,
			bool IsDone);

	private:
		Platform::String^ title;
		long long id;
		bool isDone = false;
	};
}
