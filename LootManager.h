//
// Created by Ceegan on 2017-12-22.
//

#ifndef WHITERUNNER_LOOTMANAGER_H
#define WHITERUNNER_LOOTMANAGER_H

#include <queue>
#include <vector>
#include "ACD.h"
#include "common.h"
#include "MemoryTools.h"

class WRBot;

class LootManager {
    WRBot & m_bot;
    std::queue<std::shared_ptr<ACD>> chests;

    void findChests();

    public:
    void lootArea();
    LootManager(WRBot & bot);
};


#endif //WHITERUNNER_LOOTMANAGER_H
