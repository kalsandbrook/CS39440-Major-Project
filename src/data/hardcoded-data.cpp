//
// Created by Kal on 22/02/2024.
//
#include "gameentry.h"
#include <QList>

const QList<GameEntry> gameList = {
    GameEntry("Minecraft", "A sandbox video game", {"Sandbox", "Survival"}),
    GameEntry("Grand Theft Auto V", "An action-adventure game", {"Action", "Adventure", "Open-world"}),
    GameEntry("Tetris", "A tile-matching puzzle game", {"Puzzle", "Arcade"}),
    GameEntry("Wii Sports", "A sports video game", {"Sports", "Party"}),
    GameEntry("Mario Kart 8", "A racing game", {"Racing", "Multiplayer"})
};
