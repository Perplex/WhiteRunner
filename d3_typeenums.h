//
// Created by Ceegan on 2017-12-22.
//

#ifndef WHITERUNNER_D3_TYPEENUMS_H
#define WHITERUNNER_D3_TYPEENUMS_H

#include <map>

namespace d3{

    enum class GizmoType {
        Invalid = -1,
        Door = 0,
        Chest = 1,
        Portal = 2,
        Waypoint = 4,
        Item = 5, // Not included in Symbols
        Checkpoint = 7,
        Sign = 8,
        HealingWell = 9,
        PowerUp = 10,
        TownPortal = 11,
        HearthPortal = 12,
        Headstone = 18,
        PortalDestination = 20,
        BreakableChest = 23,
        SharedStash = 25,
        Spawner = 28,
        PageOfFatePortal = 33,
        Trigger = 44,
        SecretPortal = 47,
        DestroyableObject = 48,
        BreakableDoor = 56,
        Switch = 57,
        PressurePlate = 58,
        Gate = 59,
        DestroySelfWhenNear = 60,
        ActTransitionObject = 62,
        ReformingDestroyableObject = 63,
        Banner = 64,
        LoreChest = 65,
        BossPortal = 66,
        PlacedLoot = 67,
        SavePoint = 68,
        ReturnPointPortal = 69,
        DungeonPortal = 70,
        IdentifyAll = 71,
        ReturnPortal = 75,
        RecreateGameWithParty = 76,
        Mailbox = 77,
        LootRunSwitch = 78,
        PoolOfReflection = 79
    };

    enum class ActorType {
        Invalid = 0,
        Monster = 1,
        Gizmo = 2,
        ClientEffect = 3,
        ServerProp = 4,
        Environment = 5,
        Critter = 6,
        Player = 7,
        Item = 8,
        AxeSymbol = 9,
        Projectile = 10,
        CustomBrain = 11
    };

    enum class AttributeID {
        ChestOpen = 461,
        IsNPC = 482,
        NPCIsOperatable = 483,
        NPCIsEscorting = 484,
        NPCHasInteractOptions = 485,
        NPCTalkTargetANN = 714,
        NPCConvTargetANN = 715
    };

    /*std::ostream& operator<<(std::ostream& out, const ActorType value){
        static std::map<ActorType, std::string> AT;

        if (AT.empty()){
            AT[ActorType::Invalid] = "Invalid";
            AT[ActorType::Monster] = "Monster";
            AT[ActorType::Gizmo] = "Gizmo";
            AT[ActorType::ClientEffect] = "ClientEffect";
            AT[ActorType::ServerProp] = "ServerProp";
            AT[ActorType::Environment] = "Environment";
            AT[ActorType::Critter] = "Critter";
            AT[ActorType::Player] = "Player";
            AT[ActorType::Item] = "Item";
            AT[ActorType::AxeSymbol] = "AxeSymbol";
            AT[ActorType::Projectile] = "Projectile";
            AT[ActorType::CustomBrain] = "CustomBrain";
        }

        return out << AT[value];
    }*/
}

#endif //WHITERUNNER_D3_TYPEENUMS_H
