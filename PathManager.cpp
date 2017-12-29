//
// Created by Ceegan on 2017-12-22.
//

#include "PathManager.h"
#include "WRBot.h"
#include "MemoryTools.h"

PathManager::PathManager(WRBot &bot): m_bot(bot){}

std::pair<int, int> PathManager::screenPos(vector3 position) {
    vector3 charPos = playerPos();

    double xd = position.X - charPos.X;
    double yd = position.Y - charPos.Y;
    double zd = position.Z - charPos.Z;

    double w = -0.515 * xd + -0.514 * yd + -0.686 * zd + 97.985;
    double X = (-1.182 * xd + 1.283 * yd + 0 * zd + 7.045e-3) / w;
    double Y = (-1.54 * xd + -1.539 * yd + 2.307 * zd + 6.161) / w;

    double width = 1920;
    double height = 1080;
    double aspect = 16.0f/9.0f;

    double aspectChange = (width/height) / aspect;

    X /= aspectChange;

    return std::make_pair((int)((X + 1) / 2 * width), (int)((1 - Y) / 2 * height));
}

void PathManager::moveMouse(int x, int y, int button, DWORD sleep, bool move) {
    INPUT input;

    input.type = INPUT_MOUSE;
    input.mi.mouseData = 0;
    input.mi.time = 0;
    input.mi.dx = x * (65536 / GetSystemMetrics(SM_CXSCREEN));
    input.mi.dy = y * (65536 / GetSystemMetrics(SM_CYSCREEN));
    input.mi.dwFlags = MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_MOVE;
    if (button == 1){
        input.mi.dwFlags = input.mi.dwFlags | MOUSEEVENTF_LEFTDOWN | MOUSEEVENTF_LEFTUP;
    }
    else if (button == 2){
        input.mi.dwFlags = input.mi.dwFlags | MOUSEEVENTF_RIGHTDOWN | MOUSEEVENTF_RIGHTUP;
    }

    SendInput(1, &input, sizeof(input));
    if (move){
        Sleep(600);
        input.mi.dwFlags = input.mi.dwFlags | MOUSEEVENTF_LEFTDOWN | MOUSEEVENTF_LEFTUP;
        SendInput(1, &input, sizeof(input));
        Sleep(sleep);
    }
    else{
        Sleep(sleep);
    }
}

void PathManager::keyboard(WORD key) {
    INPUT input;

    input.type = INPUT_KEYBOARD;
    input.ki.wVk = key;

    SendInput(1, &input, sizeof(INPUT));

    input.ki.dwFlags = KEYEVENTF_KEYUP;
    Sleep(100);
    SendInput(1, &input, sizeof(INPUT));
}

vector3 PathManager::playerPos() const{
    for (auto acd : MemoryTools::getACDs(m_bot.proc)){
        if (acd->ID != -1 && acd->ActorType == d3::ActorType::Player){
            return acd->Position;
        }
    }
    assert(true);
}

// TODO: Path find based on grid built from in-game meshes
void PathManager::PathFind(vector3 dst) {
    auto loc = screenPos(dst);
    moveMouse(loc.first, loc.second, 0, 3000, true);
}

void PathManager::followBreadCrumbs(int num) {
    for (int x=0; x < num; x++){
        auto loc = breadCrumbs.front();
        breadCrumbs.erase(breadCrumbs.begin());
        moveMouse(loc.first, loc.second, 0, 3000, true);
    }

}