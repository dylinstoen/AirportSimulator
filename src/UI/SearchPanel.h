//
// Created by dylin on 4/7/2026.
//

#ifndef AIRPORTSIMULATOR_SEARCH_H
#define AIRPORTSIMULATOR_SEARCH_H
#include "../SearchController.h"
#include "../Model/Query.h"
class SearchPanel {
public:
    explicit SearchPanel(SearchController& searchController) : _controller(searchController) {};
    void Draw();
private:
    SearchController& _controller;
    Query _query;
    char _title[16] = "";
    char _chapter[16] = "";
    char _part[16] = "";
    char _section[16] = "";
};



#endif //AIRPORTSIMULATOR_SEARCH_H
