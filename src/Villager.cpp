/*
** EPITECH PROJECT, 2023
** Panoramix
** File description:
** Villager
*/

#include "Panoramix.hpp"

Villager::Villager(int villagerId, int villagerFightLeft, Druid *newDruid)
{
    id = villagerId;
    fightLeft = villagerFightLeft;
    firstTime = 1;
    theirDruid = newDruid;
    std::cout<<"Villager "<<id<<": Going into battle!\n";
    villagerThread = std::thread(&Villager::villagerThreadFunc, this);
}

Villager::~Villager()
{
    villagerThread.join();
    std::cout<<"Villager "<<id<<": I'm going to sleep now.\n";
}

void Villager::villagerThreadFunc()
{
    theirDruid->lock.lock();
    villagerDrink();
    theirDruid->lock.unlock();
    while (fightLeft > 0) {
        fightLeft -= 1;
        std::cout<<"Villager "<<id<<": Take that roman scum! Only "<<fightLeft<<" left.\n";
        theirDruid->lock.lock();
        villagerDrink();
        theirDruid->lock.unlock();
    }
    Villager::~Villager();
}

void Villager::villagerDrink()
{
    int potSize = theirDruid->getPotSize();

    std::cout<<"Villager "<<id<<": I need a drink... I see "<<potSize<<" serving left.\n";
    if (potSize) {
        potSize -= 1;
        theirDruid->setPotSize(potSize);
        if (!firstTime) {
            fightLeft += 1;
        } else {
            firstTime = 0;
        }
    }
    if (!potSize && theirDruid != nullptr) {
        theirDruid->sem.release();
        std::cout<<"Villager: "<<id<<": Hey Pano wake up! We need more potion.\n";
        theirDruid->finish.acquire();
    }
}