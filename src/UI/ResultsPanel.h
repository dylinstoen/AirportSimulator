//
// Created by dylin on 4/9/2026.
//

#ifndef AIRPORTSIMULATOR_RESULTSPANEL_H
#define AIRPORTSIMULATOR_RESULTSPANEL_H
#include "../CompareController.h"


class ResultsPanel {
public:
    explicit ResultsPanel(CompareController& compareController) : _controller(compareController) {};
    void Draw() const;
private:
    CompareController& _controller;
};



#endif //AIRPORTSIMULATOR_RESULTSPANEL_H
