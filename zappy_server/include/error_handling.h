/*
** EPITECH PROJECT, 2022
** zappy
** File description:
** error_handling.h
*/

#ifndef ERROR_HANDLING_H_
    #define ERROR_HANDLING_H_
    #define CYAN    "\e[1;36m"
    #define GREEN   "\e[1;32m"
    #define RED     "\e[1;31m"
    #define PURPLE  "\e[1;35m"
    #define BLUE    "\e[1;34m"
    #define YELLOW  "\e[1;33m"
    #define NEUTRE  "\e[0;m"

    #include <stdio.h>

int error(char *message, int ret);

#endif /* !ERROR_HANDLING_H_ */
