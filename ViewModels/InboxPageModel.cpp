#include "pch.h"
#include "InboxPageModel.h"

using namespace EveryDay;
using namespace EveryDay::ViewModels;

void InboxPageModel::Cal::set(Calendar^ Cal) {
	this->calendar = Cal;

	auto evs = this->calendar->InboxEvents;
	OnPropertyChanged("InboxEvents");
	OnPropertyChanged("Cal");
}