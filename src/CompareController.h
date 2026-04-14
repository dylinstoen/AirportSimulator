//
// Created by dylin on 4/12/2026.
//

#ifndef AIRPORTSIMULATOR_COMPARECONTROLLER_H
#define AIRPORTSIMULATOR_COMPARECONTROLLER_H
#include <string>
#include <vector>
#include "Model/Status.h"

#include "Model/Query.h"


class CompareController {
public:
    void SubmitCompare(Query query, std::string firstDate, std::string secondDate);
    [[nodiscard]] std::string& GetError() { return _error; }
private:
    std::string results;
    Status _status = IDLE;
    std::string _error;
};



#endif //AIRPORTSIMULATOR_COMPARECONTROLLER_H
