/*
** EPITECH PROJECT, 2023
** B-YEP-400-PAR-4-1-zappy-laetitia.bousch
** File description:
** common
*/

#ifndef COMMON_H_
    #define COMMON_H_
    #include <stdint.h>
    #include <time.h>

enum resources {
    FOOD,
    LINEMATE,
    DERAUMERE,
    SIBUR,
    MENDIANE,
    PHIRAS,
    THYSTAME,
    EGG
};

typedef struct msg_queue_s {
    time_t time;
    uint8_t **msg;
    void (*handler)(uint8_t **args); //FIXME - check arguments
    //NOTE - pointeur sur fonctione qu'on doit executer
    msg_queue_s *next_msg;
} msg_queue_t;

typedef struct error_handling_s {
    int error_code;
    uint8_t *msg_error;
} error_handling_t;

#endif /* !COMMON_H_ */
