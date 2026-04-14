//
// Created by dylin on 4/9/2026.
//

#ifndef AIRPORTSIMULATOR_SEARCHCONTROLLER_H
#define AIRPORTSIMULATOR_SEARCHCONTROLLER_H
#include <string>
#include <vector>

#include "Model/Query.h"
#include "Model/Status.h"


class SearchController {
public:
    void SubmitSearch(Query query);
    [[nodiscard]] Status GetStatus() { return _status; }
    [[nodiscard]] std::string& GetError() { return _error; }
    [[nodiscard]] Query GetQuery() { return _query; }
    [[nodiscard]] std::vector<std::string>& GetResults() { return _results; }
private:
    char _searchBuffer[256] = "";
    std::string _error;
    Status _status = IDLE;
    Query _query;
    std::vector<std::string> _results;
};



#endif //AIRPORTSIMULATOR_SEARCHCONTROLLER_H
