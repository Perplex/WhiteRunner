//
// Created by Ceegan on 2017-12-22.
//

#ifndef WHITERUNNER_SYMBOLTABLE_H
#define WHITERUNNER_SYMBOLTABLE_H

class SymbolTable {
public:
    const long static ObjectManager = 0x141DF3D30;

    const int static Storage = 0x7E8;

    const int static FastAttrib = 0x180;
    const int static ACDManager = 0x198;

    const int static ACDManager_SizeOf = 0x150;
    const int static ACDManager_ActorCommonData = 0x0;
    const int static ACDManager_Items = 0x120;
    const int static ACDManager_MaxIndex = 0x108;
    const int static ACDManager_FirstACD = 0x0;

    const int static ACD_SizeOf = 0x3A0;
    const int static ACD_ID = 0x0;
    const int static ACD_Name = 0x4;
    const int static ACD_ActorID = 0x8C;
    const int static ACD_Position = 0xD8;
    const int static ACD_ItemLocation = 0x124;
    const int static ACD_FastAttribGroupID = 0x130;
    const int static ACD_ActorType = 0x1BC;
    const int static ACD_GizmoType = 0x1B8;
    const int static ACD_Hitpoints = 0x1C0;

    const int static FastAttrib_SizeOf = 0xA0;
    const int static FastAttrib_FastAttribGroups = 0x90;
    const int static FastAttrib_items = 0x120;
    const int static FastAttrib_FirstAttrib = 0x0;

    const int static FastAttribGroup_SizeOf = 0x12E8;
    const int static FastAttribGroup_ID = 0x0;
    const int static FastAttribGroup_Flags = 0x4;
    const int static FastAttribGroup_PtrMap = 0x10;
    const int static FastAttribGroup_Map = 0x18;

    const int static Map_mask = 0x0;
    const int static Map_count = 0x4;
    const int static Map_bucket = 0x10;

    };
#endif //WHITERUNNER_SYMBOLTABLE_H
