/*
** EPITECH PROJECT, 2023
** B-YEP-400-PAR-4-1-zappy-laetitia.bousch
** File description:
** ia
*/

#ifndef IA_H_
    #define IA_H_

    #define ARRAY_SIZE(array) (sizeof(array) / sizeof(array[0]))

typedef struct client_teams_s {
    const u_int8_t *comd;
    void (*handler)(client_t *client, u_int8_t **command);
} client_teams_t;

static const client_teams_t COMMAND_GESTION[] = {
    {"/login", funct_login},
    {"/logout", funct_logout},
    {"/users", funct_users},
    {"/user", funct_user},
    {"/help", funct_help},
    {"/send", funct_send},
    {"/messages", funct_messages},
    {"/subscribe", funct_subscribe},
    {"/subscribed", funct_subscribed},
    {"/unsubscribe", funct_unsubscribe},
    {"/use", funct_use},
    {"/create", funct_create},
    {"/list", funct_list},
    //{"/info", funct_info},
    {"LOGIN", funct_response_login},
    {"USERS", funct_response_users},
    {"USER", funct_response_user},
    {"SEND", funct_response_send},
    {"MESSAGES", funct_response_messages},
    {"SUBSCRIBE", funct_response_subscribe},
    {"SUBSCRIBED", funct_response_subscribed},
    {"UNSUBSCRIBE", funct_response_unsubscribe},
    {"TEAM", funct_response_team},
    {"LOGOUT", funct_response_logout},
    {"CHANEL", funct_response_chanel},
    {"THREAD", funct_response_thread},
    {"REPLY", funct_response_msg},
    {"LIST_TEAMS", funct_response_print_teams},
    {"LIST_CHANEL", funct_response_print_chanel},
    {"LIST_THREAD", funct_response_print_threads},
    {"LIST_REPLIES", funct_response_print_replies},
};

#endif /* !IA_H_ */
