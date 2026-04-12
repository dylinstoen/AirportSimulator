//
// Created by dylin on 4/9/2026.
//

#ifndef AIRPORTSIMULATOR_SEARCHCONTROLLER_H
#define AIRPORTSIMULATOR_SEARCHCONTROLLER_H
#include <string>
#include <vector>

#include "Model/Query.h"

enum SearchStatus {
    IDLE,
    LOADING,
    SUCCESS,
    Error
};
class SearchController {
public:
    void SubmitSearch(Query query);
    [[nodiscard]] SearchStatus GetStatus() const { return _status; }
    [[nodiscard]] const std::string& GetError() const { return _error; }
    [[nodiscard]] const std::vector<std::string>& GetResults() const { return _results; }
private:
    char _searchBuffer[256] = "";
    std::string _error;
    SearchStatus _status = IDLE;
    std::vector<std::string> _results;
};



#endif //AIRPORTSIMULATOR_SEARCHCONTROLLER_H
