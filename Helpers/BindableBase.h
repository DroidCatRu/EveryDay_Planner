#pragma once
#include <ppltasks.h>

using namespace EveryDay;
using namespace Platform;
using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Data;

namespace EveryDay {
	public ref class BindableBase : DependencyObject, INotifyPropertyChanged {

	public:
		virtual event PropertyChangedEventHandler^ PropertyChanged;

	protected:
		virtual void OnPropertyChanged(String^ propertyName) {
			PropertyChanged(this, ref new PropertyChangedEventArgs(propertyName));
		}
	};
}