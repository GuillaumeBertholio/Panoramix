/*
** EPITECH PROJECT, 2023
** PanoramixMonRepo
** File description:
** main
*/

#include <stdlib.h>
#include <stdio.h>
#include "pano.h"
#include <unistd.h>

static void info()
{
    printf("USAGE: ./panoramix <nb_villager> ");
    printf("<pot_size> <nb_fights> <nb_refills>\n");
    exit(0);
}

static void check_arg(char **av)
{
    char tab[5][12] = {"nb_villagers", "pot_size", "nb_fights", "nb_refills"};

    for (int i = 0; i < 4; i++) {
        if (atoi(av[i]) <= 0) {
            printf("Error: %s must be > 0\n", tab[i]);
            exit(84);
        }
    }
}

static void create_thread(pano *druid, villagers *villager, int size)
{
    pthread_t *all_thread;

    all_thread = malloc(sizeof(pthread_t) * (size + 1));
    pthread_create(&all_thread[0], NULL, pano_loop, druid);
    for (int i = 1; i < size + 1; i++)
        pthread_create(&all_thread[i], NULL, villager_loop, &villager[i - 1]);
    for (int i = 0; i < size + 1; i++) {
        pthread_join(all_thread[i], NULL);
    }
    free(all_thread);
}

static void create_villager(char **av, pano *druid)
{
    villagers new_villager;
    villagers *villager;
    pthread_mutex_t mutex;
    int size = atoi(av[1]);

    villager = malloc(sizeof(villagers) * size);
    if (!villager) {
        printf("Error: malloc villager");
        exit (84);
    }
    new_villager.druid = druid;
    new_villager.fight_left = atoi(av[3]);
    pthread_mutex_init(&mutex, NULL);
    new_villager.villager_mutex = &mutex;
    for (int i = 0; i < size; i++) {
        new_villager.id = i;
        villager[i] = new_villager;
    }
    create_thread(druid, villager, size);
    free(villager);
}

int main(int ac, char **av)
{
    pano druid;

    if (ac != 5 || (av[1][0] == '-' && av[1][1] == 'h'))
        info();
    check_arg(&av[1]);
    druid.pot_size = atoi(av[2]);
    druid.refills = atoi(av[4]);
    sem_init(&druid.pano_is_waiting, 0, 1);
    sem_init(&druid.wait_pano, 0, 1);
    create_villager(av, &druid);
}