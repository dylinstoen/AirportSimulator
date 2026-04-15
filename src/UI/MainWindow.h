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
    MainWindow(SearchController& searchController, CompareController& compareController) : _searchPanel(searchController), _datePickerPanel(searchController, compareController), _resultsPanel(compareController) {};
    void Draw();
private:
    SearchPanel _searchPanel;
    DatePickerPanel _datePickerPanel;
    ResultsPanel _resultsPanel;
};



#endif //AIRPORTSIMULATOR_MAINWINDOW_H
