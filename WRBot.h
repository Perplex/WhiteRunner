//
// Created by Ceegan on 2017-12-21.
//

#ifndef WHITERUNNER_WRBOT_H
#define WHITERUNNER_WRBOT_H

#include "common.h"

#include "LootManager.h"
#include "PathManager.h"
#include "ButtonManager.h"
#include <windows.h>
#include <w32api/tlhelp32.h>

class WRBot {
public:
    WRBot();
    ~WRBot();
    void update(int loop);

    LootManager     m_loot;
    PathManager     m_paths;
    ButtonManager   m_buttons;
    HANDLE          proc;

    const LootManager & Loot() const;
    const PathManager & Path() const;
    const ButtonManager & buttons() const;
};


#endif //WHITERUNNER_WRBOT_H
