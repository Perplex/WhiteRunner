//
// Created by Ceegan on 2017-12-22.
//

#ifndef WHITERUNNER_MEMORYTOOLS_H
#define WHITERUNNER_MEMORYTOOLS_H

#include <vector>
#include <memory>
#include <cmath>
#include "ACD.h"


namespace MemoryTools {

    std::vector<std::shared_ptr<ACD>> getACDs(HANDLE proc);

    template <typename T> T Read(HANDLE proc, long address) {
        T buff = 0;
        ReadProcessMemory(proc, (LPCVOID) address, &buff, 4, nullptr);

        return buff;
    }

    template <> float Read<float>(HANDLE proc, long address);
    template <> std::string Read<std::string>(HANDLE proc, long address);
    template <> vector3 Read<vector3>(HANDLE proc, long address);
    bool verifyAttributeValue(HANDLE proc, int FastAttribGroupID);

};


#endif //WHITERUNNER_MEMORYTOOLS_H
