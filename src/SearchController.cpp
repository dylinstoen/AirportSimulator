//
// Created by dylin on 4/9/2026.
//

#include "SearchController.h"

#include <iostream>
#include <cpr/cpr.h>

#include <utility>

#include "RegulationService.h"
#include "./Model/Query.h"

// 1. User enters: title, chapter, part,and section
// 2. Pass data into controller
// 3. Controller passes that data into a processing service
// 4. Processing service returns a json string of the version
// 5. Json string gets passed into a json parser which parses the json string into a json
// 5. Json gets passed into a process version
// 6. Process version returns an array of the different versions
// 7. Controller updates results array
// 8. DatePickerPanel which has access to SearchController renders the array as 2 dropdown lists

void SearchController::SubmitSearch(Query query) {
    _query = std::move(query);
    _status = LOADING;
    _error.clear();
    try {
        std::string response = RegulationService::ProcessRequest(_query);
        _results = RegulationService::ProcessSearchResponse(response);
        _status = SUCCESS;
    } catch (std::exception &e) {
        _error = e.what();
        _status = Error;
    }
}