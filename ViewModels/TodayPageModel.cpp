#include "pch.h"
#include "TodayPageModel.h"

using namespace EveryDay;
using namespace EveryDay::ViewModels;

void TodayPageModel::Cal::set(Calendar^ Cal) {
	this->calendar = Cal;

	auto evs = this->calendar->PlannedEvents;
	OnPropertyChanged("TodayEvents");
	OnPropertyChanged("Cal");
}