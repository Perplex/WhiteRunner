//
// Created by Ceegan on 2017-12-22.
//

#include "MemoryTools.h"
#include "WRBot.h"

template <> float MemoryTools::Read<float>(HANDLE proc, long address) {
    unsigned int buff = 0;
    ReadProcessMemory(proc, (LPCVOID) address, &buff, 8, nullptr);

    unsigned int  sign = buff >> 31;
    signed int  exponent = ((buff >> 23) & 0xff) - 0x7F;
    unsigned int  mantissa = buff << 9;
    float  value = 0;
    float mantissa2;

    value = 0.5f;
    mantissa2 = 0.0f;
    while (mantissa)
    {
        if (mantissa & 0x80000000)
            mantissa2 += value;
        mantissa <<= 1;
        value *= 0.5f;
    }

    value = (1.0f + mantissa2) * (pow (2, exponent));
    if (sign) value = -value;

    return value;

}

template <> vector3 MemoryTools::Read<vector3>(HANDLE proc, long address) {

    vector3 temp;

    ReadProcessMemory(proc, (LPCVOID) address, &temp.X, 4, nullptr);

    ReadProcessMemory(proc, LPCVOID (address + 0x4), &temp.Y, 4, nullptr);

    ReadProcessMemory(proc, LPCVOID (address + 0x8), &temp.Z, 4, nullptr);

    return temp;
}

template<> std::string MemoryTools::Read<std::string>(HANDLE proc, long address) {
    long buff = 0;
    int x=0;
    std::string name;

    ReadProcessMemory(proc, (LPCVOID) address, &buff, 8, nullptr);;
    while((buff & 0xff) != 0x00){
        while ((buff & 0xff) != 0x00) {
            name.push_back(char (buff & 0xff));
            buff >>= 8;
        }
        x++;
        buff = 0;
        ReadProcessMemory(proc, (LPCVOID)(address + 0x8*x), &buff, 8, nullptr);
    }

    return name;
}

std::vector<std::shared_ptr<ACD>> MemoryTools::getACDs(HANDLE proc) {
    long address;
    long buff =0;
    std::vector<std::shared_ptr<ACD>> ACDs;

    ReadProcessMemory(proc, (LPCVOID) SymbolTable::ObjectManager, &buff, 8, nullptr);

    // ACDManger
    address = buff + SymbolTable::Storage + SymbolTable::ACDManager;
    ReadProcessMemory(proc, (LPCVOID) address, &buff, 8, nullptr);

    // Pointer to ActorCommonData
    address = buff + SymbolTable::ACDManager_ActorCommonData;
    ReadProcessMemory(proc, (LPCVOID) address, &buff, 8, nullptr);
    address = buff;

    //Gets max index
    address = address + SymbolTable::ACDManager_MaxIndex;
    int maxInd = 0;
    ReadProcessMemory(proc, (LPCVOID) address, &maxInd, 8, nullptr);

    //ActorCommonData
    address += SymbolTable::ACDManager_Items - SymbolTable::ACDManager_MaxIndex;
    ReadProcessMemory(proc, (LPCVOID) address, &buff, 8, nullptr);

    //Gets ptr to first ACD
    address = buff + SymbolTable::ACDManager_FirstACD;
    ReadProcessMemory(proc, (LPCVOID) address, &buff, 8, nullptr);
    address = buff;

    // Create vector of ACDs
    for (int x = 0; x < maxInd; address += SymbolTable::ACD_SizeOf, x++){
        ACDs.push_back(std::make_shared<ACD>(proc, address));
    }

    return ACDs;
}

bool MemoryTools::verifyAttributeValue(HANDLE proc, int FastAttribGroupID) {
    int key = (-1 << 12) + (int(d3::AttributeID::ChestOpen) & 0xFFF);
    long address;
    int buff = 0;

    ReadProcessMemory(proc, (LPCVOID) SymbolTable::ObjectManager, &buff, 8, nullptr);

    // FastAttrib ptr
    address = buff + SymbolTable::FastAttrib + SymbolTable::Storage;
    ReadProcessMemory(proc, (LPCVOID) address, &buff, 8, nullptr);

    // FastAttributeGroup ExpandableContainer
    address = buff + SymbolTable::FastAttrib_FastAttribGroups;
    ReadProcessMemory(proc, (LPCVOID) address, &buff, 8, nullptr);
    address = buff;

    // FastAttrib list ptr
    address += SymbolTable::FastAttrib_items;
    ReadProcessMemory(proc, (LPCVOID) address, &buff, 8, nullptr);

    //Gets ptr to first FastAttrib
    address = buff + SymbolTable::FastAttrib_FirstAttrib;
    ReadProcessMemory(proc, (LPCVOID) address, &buff, 8, nullptr);

    // Verifying if chest is valid
    address = buff+SymbolTable::FastAttribGroup_SizeOf*(short)FastAttribGroupID;
    ReadProcessMemory(proc, (LPCVOID) address, &buff, 8, nullptr);

    if (buff != 0){
        int mask=0;
        address += SymbolTable::FastAttribGroup_Map;
        ReadProcessMemory(proc, (LPCVOID) (address+SymbolTable::Map_mask), &mask, 4, nullptr);

        if(mask != 0) {
            int count=0;
            ReadProcessMemory(proc, (LPCVOID)(address+SymbolTable::Map_count), &count, 4, nullptr);
            if (count == 0)
                return false;

            buff =0;
            ReadProcessMemory(proc, (LPCVOID)(address+SymbolTable::Map_bucket), &buff, 8, nullptr);
            address = buff;

            int hash = abs(key) -1;
            int index = hash & mask;
            long entry=0;

            ReadProcessMemory(proc, (LPCVOID)(address + index*0x8), &entry, 8, nullptr);

            while(entry != 0){
                int entryKey=0;
                ReadProcessMemory(proc, (LPCVOID)(entry+0x8), &entryKey, 4, nullptr);
                if (entryKey == key)
                    return true;
                ReadProcessMemory(proc, (LPCVOID)(entry+0x10), &entry, 8, nullptr);
            }
        }
    }
    return false;
}