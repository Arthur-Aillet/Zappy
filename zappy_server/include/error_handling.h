/*
** EPITECH PROJECT, 2022
** zappy
** File description:
** error_handling.h
*/

#ifndef ERROR_HANDLING_H_
    #define ERROR_HANDLING_H_
    #define C    "\e[1;36m"
    #define G   "\e[1;32m"
    #define R     "\e[1;31m"
    #define P  "\e[1;35m"
    #define B    "\e[1;34m"
    #define Y  "\e[1;33m"
    #define N  "\e[0;m"

    #include <stdio.h>

int error(char *message, int ret);
int basic_log(char *message, char *color, int ret);

#endif /* !ERROR_HANDLING_H_ */
