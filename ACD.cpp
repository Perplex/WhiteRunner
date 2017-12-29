//
// Created by Ceegan on 2017-12-22.
//

#include "ACD.h"
#include "MemoryTools.h"

ACD::ACD(HANDLE proc, long current): SizeOf(MemoryTools::Read<int>(proc, current + SymbolTable::ACD_SizeOf)),
                                     ID(MemoryTools::Read<int>(proc, current + SymbolTable::ACD_ID)),
                                     Name(MemoryTools::Read<std::string>(proc, current + SymbolTable::ACD_Name)),
                                     ActorID(MemoryTools::Read<int>(proc, current + SymbolTable::ACD_ActorID)),
                                     Position(MemoryTools::Read<vector3>(proc, current + SymbolTable::ACD_Position)),
                                     ItemLocation(MemoryTools::Read<int>(proc, current + SymbolTable::ACD_ItemLocation)),
                                     FastAttribGroupID(MemoryTools::Read<int>(proc, current + SymbolTable::ACD_FastAttribGroupID)),
                                     ActorType((d3::ActorType)MemoryTools::Read<int>(proc, current + SymbolTable::ACD_ActorType)),
                                     GizmoType((d3::GizmoType)MemoryTools::Read<int>(proc, current + SymbolTable::ACD_GizmoType)),
                                     Hitpoints(MemoryTools::Read<float>(proc, current + SymbolTable::ACD_Hitpoints)){

};