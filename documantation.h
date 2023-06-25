/*
** EPITECH PROJECT, 2023
** B-YEP-400-PAR-4-1-zappy-laetitia.bousch
** File description:
** documentation
*/

/** @file mainpage.h
* @brief Definition of class Template
*
* $Header: /nfs/slac/g/glast/ground/cvs/workbook/pages/advanced_doxygen/usingDoxygen.htm,v 1.1.1.1 2007/06/29 15:03:16 chuckp Exp $
*/
/** @mainpage
*
* @section a Our group
* Laetitia Bousch | Auguste Frater | Axel Denis | Arthur Aillet | Julian Scott | Ludovic De-Chavagnac
*
* @section contexte Contexte
* Zappy, it is a project to compose three parts:
*   - the server
*   - the gui
*   - the AI
* The goal of the project is to make a network game where several teams compete in order to evolve as quickly as possible so that 6 of their players reach the maximum level to make their team win.
* For this the players of each team must collect resources on the tiles in order to survive and evaluate.
*
*
* You should know that each part is independent and can be reused if the communication protocol is respected.
* For example, you can reference the readme in the zappy_server document which explains the different commands and responses the server can provide.
*
*
* - Server part
* The server is the part that saves the progress of the game and communicates between the map and the players.
* It is made in C
*
* - Graphic part
* This part allows to have a visual of the current game, it must display the map with its resources and the players as well as animate the actions of the players.
* It is made in rust.
*
* - Part AI
* This part aims to recreate a hive with fighters, workers and a queen. So this means that the behavior of our players can be very different depending on their role in the hive.
* It is made in python.
*
*
* @section GamePlay
*
* This world has an infinite map.
* resources section
* While walking around the map, players can find food and different stones.
* Food is essential for the survival of the player because every 10 actions it allows 1 life point and if it drops to zero it dies.
* The only way for him not to die is to feed himself.
* Stones are used to allow players to level up. There are 6 categories:
* - Linemate
* - Deraumere
* - Sibur
* - Beggar
* - Phiras
* - Thystame
*
* The server generates resources at startup and every 20 time units (defined by the parameters transmitted to the server when it is launched). Resources should be distributed evenly across the map.
*
* You should know that the more a player evolves, the further he can see on the next squares to analyze the resources he needs for the future.
*
* Each level pass requires a specific number of players on the square where the incantation is done and resources that are on the ground and not in the players' inventory. The players do not need to be on the same team for the cast.
* However the ritual can be stopped if during the incantation another player arrives on the space and pushes the players currently in ritual.
*
* Players can communicate with each other but be careful when a player sends a message all the other players whether they are in the team or not receive the message. However they receive the direction from where the message originates and the message but do not receive the information of who transmitted the message.
*
*
* @author Laetitia Bousch
*/