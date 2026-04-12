//
// Created by dylin on 4/10/2026.
//

#ifndef AIRPORTSIMULATOR_DATEPICKERPANEL_H
#define AIRPORTSIMULATOR_DATEPICKERPANEL_H
#include <utility>

#include "../SearchController.h"


class DatePickerPanel {
public:
    explicit DatePickerPanel(SearchController& searchController) : _controller(searchController) {};
    void Draw() const;
private:
    SearchController& _controller;
};



#endif //AIRPORTSIMULATOR_DATEPICKERPANEL_H
