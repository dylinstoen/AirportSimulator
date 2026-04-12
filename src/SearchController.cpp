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
// 5. TODO: Json string gets passed into a json parser which parses the json string into a json
// 5. TODO: Json gets passed into a process version
// 6. TODO: Process version returns an array of the different versions
// 7. TODO: Controller updates results array
// 8. TODO: DatePickerPanel which has access to SearchController renders the array as 2 dropdown lists

// TODO: 4. Processing service returns string to controller
// TODO: 5. Controller calls a parser on xml and passes in xml
// TODO: 6. Parser returns parsed xml
// TODO: 7. Controller stores most recent result
// TODO: 8. Results panel asks for most recent when rendering
void SearchController::SubmitSearch(Query query) {
    _status = LOADING;
    _error.clear();
    try {
        std::string response = RegulationService::ProcessRequest(std::move(query));
        _results = RegulationService::ProcessResponse(response);
    } catch (std::exception &e) {
        _error = e.what();
        _status = Error;
    }
}