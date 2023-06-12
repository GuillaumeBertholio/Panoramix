/*
** EPITECH PROJECT, 2023
** PanoramixMonRepo
** File description:
** pano
*/

#include <stdio.h>
#include "pano.h"

static void preparing_potion(pano *druid)
{
    if (druid->refills > 0) {
        druid->refills--;
        druid->pot_size++;
        printf("Druid: Ah! Yes, yes, I'm awake! Working on it! Beware ");
        printf("I can only make %d refills more refills after this one.\n",
            druid->refills);
    }
    sem_post(&druid->wait_pano);
}

void *pano_loop(void *panoramix)
{
    pano *druid = (pano *)(panoramix);

    printf("Druid: I'm ready... but sleepy...\n");
    while (druid->refills > 0) {
        sem_wait(&druid->pano_is_waiting);
        preparing_potion(druid);
    }
    printf("I'm out of viscum. I'm going back to... zZz\n");
}