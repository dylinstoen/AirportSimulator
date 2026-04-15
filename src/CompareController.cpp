//
// Created by dylin on 4/12/2026.
//

#include "CompareController.h"

#include <iostream>

#include "CompareResponseMotor.h"
#include "RegulationService.h"

// Pass query and the first date into a process request that returns the stringed xml of the result
// Pass second date and query and return the stringed xml of that
// Pass string xml first into a xml processor to convert it to string of just the contents
// Pass string xml of second into a xml processor to convert it to a string of just the contents
// TODO: Store contentFirstDate and display to screen in tab 1
// TODO: Store contentSecondDate and display to screen in tab 2
// TODO: Store difContent and display to screen in tab 3
void CompareController::SubmitCompare(Query query, const std::string& firstDate, const std::string& secondDate) {
    _status = LOADING;
    try {
        query.url = "https://www.ecfr.gov/api/versioner/v1/full/" + firstDate + "/title-" + query.title + ".xml";
        std::string contentFirstDateJson = RegulationService::ProcessRequest(query);
        query.url = "https://www.ecfr.gov/api/versioner/v1/full/" + secondDate + "/title-" + query.title + ".xml";
        std::string contentSecondDateJson = RegulationService::ProcessRequest(query);
        resultFirstDate = RegulationService::ProcessCompareResponse(contentFirstDateJson);
        resultSecondDate = RegulationService::ProcessCompareResponse(contentSecondDateJson);
        _status = SUCCESS;
    } catch (std::exception& e) {
        _error = e.what();
        _status = Error;
    }

}