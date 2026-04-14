//
// Created by dylin on 4/8/2026.
//

#ifndef AIRPORTSIMULATOR_MAINWINDOW_H
#define AIRPORTSIMULATOR_MAINWINDOW_H
#include "DatePickerPanel.h"
#include "ResultsPanel.h"
#include "SearchPanel.h"


class MainWindow {
public:
    MainWindow(SearchController& searchController) : _searchPanel(searchController), _datePickerPanel(searchController) {};
    void Draw();
private:
    SearchPanel _searchPanel;
    ResultsPanel _resultsPanel;
    DatePickerPanel _datePickerPanel;
};



#endif //AIRPORTSIMULATOR_MAINWINDOW_H
