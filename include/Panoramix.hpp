/*
** EPITECH PROJECT, 2023
** Panoramix
** File description:
** Panoramix
*/

#pragma once
#include <iostream>
#include <thread>
#include <semaphore>
#include <mutex>
#include <unistd.h>


class Druid {
    public:
        Druid(int starterRefill, int starterPotSize);
        ~Druid();
        void druidRefill();
        void druidThreadFunc();
        int getPotSize() {return potSize;}
        void setPotSize(int newPot) {potSize = newPot;}
        std::mutex lock;
        std::binary_semaphore sem;
        std::binary_semaphore finish;
    private:
        int refill;
        int potSize;
        std::thread druidThread;
};

class Villager {
    public:
        Villager(int villagerId, int villagerFightLeft, Druid *newDruid);
        ~Villager();
        void villagerDrink();
        void villagerThreadFunc();
    private:
        int id;
        int fightLeft;
        std::thread villagerThread;
        int firstTime;
        Druid *theirDruid;
};
