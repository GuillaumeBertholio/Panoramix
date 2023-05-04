/*
** EPITECH PROJECT, 2023
** Panoramix
** File description:
** Main
*/

#include "Panoramix.hpp"
#include <string.h>

int info(int returnValue)
{
    std::cout<<"USAGE: ./panoramix <nb_villager> <pot_size> <nb_fights> <nb_refills>\nValues must be >0.\n";
    return returnValue;
}

void core(int nbrVillager, int potSize, int nbrFight, int nbrRefill)
{
    Villager *villager[nbrVillager];
    Druid *druid = new Druid(nbrRefill, potSize);

    for (int i = 0; i < nbrVillager; i++)
        villager[i] = new Villager(i, nbrFight, druid);
}

int main(int ac, char **av)
{
    int intArg[4];

    if (ac == 2 && !strcmp(av[1], "-h"))
        return info(0);
    if (ac != 5)
        return info(84);
    for (int i = 0; i < 4; i++) {
        intArg[i] = atoi(av[i + 1]);
        if (intArg[i] <= 0)
            return info(84);
    }
    core(intArg[0], intArg[1], intArg[2], intArg[3]);
    return 0;
}