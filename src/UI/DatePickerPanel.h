//
// Created by dylin on 4/10/2026.
//

#ifndef AIRPORTSIMULATOR_DATEPICKERPANEL_H
#define AIRPORTSIMULATOR_DATEPICKERPANEL_H
#include <utility>

#include "SearchPanel.h"
#include "../SearchController.h"
#include "../CompareController.h"

class DatePickerPanel {
public:
    explicit DatePickerPanel(SearchController& searchController, CompareController& compareController) : _searchController(searchController), _compareController(compareController) {};
    void Draw();
private:
    CompareController& _compareController;
    SearchController& _searchController;
};



#endif //AIRPORTSIMULATOR_DATEPICKERPANEL_H
