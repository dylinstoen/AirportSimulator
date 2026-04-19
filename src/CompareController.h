//
// Created by dylin on 4/12/2026.
//

#ifndef AIRPORTSIMULATOR_COMPARECONTROLLER_H
#define AIRPORTSIMULATOR_COMPARECONTROLLER_H
#include <memory>
#include <string>
#include <vector>
#include "Model/Status.h"
#include "Model/Query.h"
#include "Model/Response.h"


class CompareController {
public:
    void SubmitCompare(Query query, const std::string& firstDate, const std::string& secondDate);
    [[nodiscard]] std::string& GetError() { return _error; }
    [[nodiscard]] Status GetStatus() const { return _status; }
    [[nodiscard]] Response GetResponseFirstDate() { return resultFirstDate; }
    [[nodiscard]] Response GetResponseSecondDate() { return resultSecondDate; }
    [[nodiscard]] ResponseDif GetDiffResponse() { return resultDifferenceResponse; }
private:
    Response resultFirstDate;
    Response resultSecondDate;
    ResponseDif resultDifferenceResponse;
    Status _status = IDLE;
    std::string _error;
};



#endif //AIRPORTSIMULATOR_COMPARECONTROLLER_H
