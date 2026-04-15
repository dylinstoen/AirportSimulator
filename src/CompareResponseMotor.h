//
// Created by dylin on 4/13/2026.
//

#ifndef AIRPORTSIMULATOR_COMPARERESPONSEMOTOR_H
#define AIRPORTSIMULATOR_COMPARERESPONSEMOTOR_H
#include <memory>
#include <tinyxml2.h>
#include "Model/Response.h"

class CompareResponseMotor {
public:
    static ResponseNode Process(tinyxml2::XMLElement* root);
};



#endif //AIRPORTSIMULATOR_COMPARERESPONSEMOTOR_H
