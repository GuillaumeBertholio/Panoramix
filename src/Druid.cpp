/*
** EPITECH PROJECT, 2023
** Panoramix
** File description:
** Druid
*/

#include "Panoramix.hpp"

Druid::Druid(int starterRefill, int starterPotSize) : sem(0), finish(0)
{
    refill = starterRefill;
    potSize = starterPotSize;
    std::cout<<"Druid: I'm ready... but sleepy...\n";
    druidThread = std::thread(&Druid::druidThreadFunc, this);
}

Druid::~Druid()
{
    druidThread.join();
    std::cout<<"Druid: I'm out of viscum. I'm going back to... zZz\n";
}

void Druid::druidThreadFunc()
{
    while(refill > 0) {
        sem.acquire();
        druidRefill();
    }
    Druid::~Druid();
}

void Druid::druidRefill()
{
    if (refill > 0) {
        refill -= 1;
        potSize += 1;
        std::cout<<"Druid: Ah! Yes, yes, I'm awake! Working on it! Beware I can only make "<<
            refill<<" more refills after this one.\n";
    }
    finish.release();
}