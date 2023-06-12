/*
** EPITECH PROJECT, 2023
** PanoramixMonRepo
** File description:
** villager
*/

#include <stdio.h>
#include "pano.h"

static void drink_potion(villagers *villager)
{
    pthread_mutex_lock(villager->villager_mutex);
    if (villager->druid->pot_size > 0) {
        villager->fight_left++;
        villager->druid->pot_size--;
        printf("Villager %d: I need a drink... I see %d servings left.\n",
            villager->id, villager->druid->pot_size);
    }
    if (villager->druid->pot_size == 0 && villager->druid->refills > 0) {
        sem_post(&villager->druid->pano_is_waiting);
        sem_wait(&villager->druid->wait_pano);
    }
    pthread_mutex_unlock(villager->villager_mutex);
}

static void fight(villagers *villager)
{
    villager->fight_left--;
    printf("Villager %d: Take that roman scum! Only %d left.\n",
        villager->id, villager->fight_left);
    if (!villager->fight_left) {
        drink_potion(villager);
    }
}

void *villager_loop(void *villager_void)
{
    villagers *villager = (villagers *)(villager_void);

    printf("Villager %d: Going into battle!\n", villager->id);
    drink_potion(villager);
    while (villager->fight_left > 0) {
        fight(villager);
    }
    printf("Villager %d: I'm going to sleep now.\n", villager->id);
}