#pragma once
namespace EveryDay {

	[Windows::UI::Xaml::Data::Bindable]
	public ref class InboxEvent sealed {

	public:
		property Platform::String^ Title {
			Platform::String^ get() { return this->title; }
			void set(Platform::String^ Title) { this->title = Title; }
		}
		property Platform::String^ Color {
			Platform::String^ get() { return this->color; }
			void set(Platform::String^ Color) { this->color = Color; }
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
			void set(bool IsDone) { this->isDone = IsDone; }
		}

		InboxEvent();
		InboxEvent(InboxEvent^ ev);
		InboxEvent(Platform::String^ Title,
			Platform::String^ Color,
			long long Id,
			bool IsDone);

	private:
		Platform::String^ title;
		Platform::String^ color;
		long long id;
		bool isDone;
	};
}
