//
// Created by Ceegan on 2017-12-22.
//

#ifndef WHITERUNNER_PATHMANAGER_H
#define WHITERUNNER_PATHMANAGER_H

#include <windows.h>
#include <vector>
#include "common.h"
#include "vector3.h"

class WRBot;

class PathManager {
    WRBot & m_bot;
    std::vector<std::pair<int, int>> breadCrumbs = {std::make_pair(100, 1020), std::make_pair(200, 200),
                                                    std::make_pair(560, 300), std::make_pair(960, 10),
                                                    std::make_pair(1600, 100), std::make_pair(1800, 600),
                                                    std::make_pair(1200, 500)};

    public:
    std::pair<int, int> screenPos(vector3 position);
    PathManager(WRBot & bot);
    void moveMouse(int x, int y, int button, DWORD sleep=0, bool move=false);
    void keyboard(WORD key);
    void PathFind(vector3 dst);
    vector3 playerPos() const;
    void followBreadCrumbs(int num=1);
};


#endif //WHITERUNNER_PATHMANAGER_H
