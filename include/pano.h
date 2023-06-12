/*
** EPITECH PROJECT, 2023
** PanoramixMonRepo
** File description:
** pano
*/

#pragma once
#include <pthread.h>
#include <semaphore.h>

typedef struct pano {
    int                 refills;
    int                 pot_size;
    sem_t               pano_is_waiting;
    sem_t               wait_pano;
    pthread_mutex_t    *druid_mutex;
}pano;


typedef struct villagers {
    int                 id;
    int                 fight_left;
    pthread_mutex_t    *villager_mutex;
    pano               *druid;
}villagers;

void *pano_loop(void *panoramix);
void *villager_loop(void *villager_void);