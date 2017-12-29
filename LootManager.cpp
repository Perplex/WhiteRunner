//
// Created by Ceegan on 2017-12-22.
//

#include "LootManager.h"
#include "WRBot.h"


LootManager::LootManager(WRBot &bot): m_bot(bot) {}

void LootManager::findChests() {
    for (auto ACD : MemoryTools::getACDs(m_bot.proc)){
        if (ACD->ID != -1 && ACD->GizmoType == d3::GizmoType::Chest && ACD->ActorType == d3::ActorType::Gizmo && !MemoryTools::verifyAttributeValue(m_bot.proc, ACD->FastAttribGroupID)){
            std::cout << ACD->Name << std::endl;
            chests.push(ACD);
        }
    }
}

void LootManager::lootArea() {
    if (chests.empty()){
        findChests();
    }

    while(!chests.empty()){
        auto chest = chests.front();

        m_bot.m_paths.PathFind(chest->Position);

        for (auto acd : MemoryTools::getACDs(m_bot.proc)){
            if (acd->ID != -1 && acd->ItemLocation == -1 && acd->ActorType == d3::ActorType::Item){
                m_bot.m_paths.PathFind(acd->Position);
                break;
            }
        }
        chests.pop();

        if (chests.empty()){
            findChests();
        }
    }
}