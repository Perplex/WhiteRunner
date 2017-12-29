//
// Created by Ceegan on 2017-12-22.
//

#ifndef WHITERUNNER_ACD_H
#define WHITERUNNER_ACD_H

#include <windows.h>
#include "d3_typeenums.h"
#include "SymbolTable.h"
#include "vector3.h"

class ACD {

public:
    ACD(HANDLE proc, long current);

    const int SizeOf;
    int ID;
    std::string Name;
    int ActorID;
    vector3 Position;
    int ItemLocation;
    int FastAttribGroupID;
    d3::ActorType ActorType;
    d3::GizmoType GizmoType;
    float Hitpoints;
};


#endif //WHITERUNNER_ACD_H
