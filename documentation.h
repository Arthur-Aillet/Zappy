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
* Zappy, is a project composed in three parts:
*   - the server
*   - the graphical interface
*   - the AI
* The goal of the project is to make a network game where several teams compete in order to evolve as quickly as possible. 6 of their players have to reach the maximum level to make their team win.
* The players of each team must collect resources on the tiles in order to survive and evoluate.
*
*
* Each part is independent and can be reused as long as the communication protocol is respected.
* For example, you can reference the README in the zappy_server document which explains the different commands and responses the server can provide.
*
*
* - Server part
* Saves the progress of the game and communicates between the map and the players.
* Made in C
*
* - Graphic part
* Visual representation of the state of the game, it must display the map, its resources, the players as well as animate the actions of the players.
* Made in rust
*
* - Part AI
* This is our implementation of a player. It aims to recreate a hive with fighters, workers and a queen. The behavior of our players can be very different depending on their role in the hive.
* Made in python
*
*
* @section GamePlay
*
* This world has an finite but circular map. While walking around the map, players can find food and different stones.
* Food is essential for the survival of the player because every 10 actions it allows 1 life point and if it drops to zero it dies.
* The only way for him not to die is to feed himself. Stones are used to allow players to level up. There are 6 stone categories:
* - Linemate
* - Deraumere
* - Sibur
* - Beggar
* - Phiras
* - Thystame
*
* The server generates resources at startup and every 20 time units (defined by the parameters transmitted to the server at launch). Resources should be distributed evenly across the map.
*
* More a player evolves, the further he can see, this is important to analyze the resources he needs for the future.
*
* To pass a level, an incentation is made, it requires a specific number of players on the tile where the incantation is started and specific resources on the ground (not in the player's inventory).
* The players do not need to be on the same team for the cast. However the ritual can be stopped if during the incantation another player arrives on the space and pushes the players currently in ritual.
*
* Players can communicate with each other but be careful when a player sends a message all the other players whether they are in the team or not receive the message.
* However they receive the direction from where the message originates and the message but do not receive the information of who transmitted the message.
*
*
* @author Laetitia Bousch, Arthur Aillet
*/
