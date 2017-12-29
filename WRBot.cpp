//
// Created by Ceegan on 2017-12-21.
//

#include "WRBot.h"

WRBot::WRBot(): m_loot(*this), m_paths(*this), m_buttons(*this) {
    PROCESSENTRY32 entry;
    HANDLE hProcess = nullptr;
    entry.dwSize = sizeof(PROCESSENTRY32);

    HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

    if (Process32First(snapshot, &entry) == TRUE)
        while (Process32Next(snapshot, &entry) == TRUE)
            if (strcmp(entry.szExeFile, "Diablo III64.exe") == 0)
                hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, entry.th32ProcessID);
    CloseHandle(snapshot);
    proc = hProcess;

    assert(proc != nullptr);
}

WRBot::~WRBot() {
    std::cout << "\nClosing Diablo III Process Handle" << std::endl;
    CloseHandle(proc);
}

void WRBot::update(int loop){
    m_buttons.OnStart();
    if (loop %3 == 0){
        m_buttons.Salvage();
    }
    m_buttons.getQuest();
    m_paths.followBreadCrumbs(3);
    m_paths.keyboard(VK_ESCAPE);
    m_paths.followBreadCrumbs(4);
    m_loot.lootArea();
    m_buttons.OnEnd();
    Sleep(12000);
}

const LootManager& WRBot::Loot() const {
    return m_loot;
}

const PathManager& WRBot::Path() const {
    return m_paths;
}

const ButtonManager& WRBot::buttons() const {
    return m_buttons;
}
