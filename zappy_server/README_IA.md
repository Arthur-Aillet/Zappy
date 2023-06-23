# IA Protocol

- All data passed by the server
- The client can be sent its request to the server without waiting for them to be done.
- The server sends back a message confirming the correct execution of the requests (or not of course)
- If the server sends more than `10` request without response, will no longer take them into account
- The server execute the client's request in the order they were received
- The requests are buffered and a command's execution time only block the player in question (`time limite`).
- The server can identify only the object class. It can identify the diffence between two objects with the same class

### Arguments

- `port`: The port number
- `width`: The width of the world
- `height`: The height of the world
- `nameX`: The name of the team `X` (you can have more than one team)
- `clientsNb`: is the number of authorized clients per team
- `freq`: is the reciprocal of time unit for execution of actions

### Default parameters
`port`: 4242
`width`: 10
`height`: 10
`nameX`: "Team1" "Team2" "Team3" "Team4"
`clientNB`: 2
`freq`: 100

### Connection:

When a client connects to the server:
    - The server sends: "WELCOME\n"
    - The client sends: "TEAM-NAME\n"
    - The server sends: "CLIENT-NUM\n"
    - The server sends: "X Y\n"

`X` and `Y` indicate the world's dimensions
`CLIENT-NUM` indicates the number of slots available on the server for the `TEAM-NAME` team. The client can be connected if the number is greater than or equal to 1.

### Action:

- `f` by default = `100`
    - time is in seconds.
    - Exemple: f = 1 => time limit = 7/1 = 7 seconds.
- Command = string end with a new line
- Bad Command return `ko`

| Action  | Command    | time limite | response  |
| :------ |:----------:|:-----------:| :-------: |
| move up one title | "Forward" | 7/f | ok |
| turn 90° right | "Right" | 7/f | ok |
| tunr 90° left | "Left" | 7/f | ok |
| look around | "Look" | 7/f | [tile1, tile2, ...] |
| inventory | "Inventory" | 1/f | [linemate n, sibur n, ...] |
| broadcast text | "Broadcast text\n" | 7/f | ok |
| send a message to a client | "message K, text\n" | - | - |
| number of team unused slots | "Connect_nbr" | - | value |
| fork a player | "Fork" | 42/f | ok |
| eject players from this tile | "Eject" | 7/f | ok/ko |
| death of a player | - | - | dead |
| take object | "Take object" | 7/f | ok/ko |
| set object down | "Set **'name object'**" | 7/f | ok/ko |
| start incantation | "Incantation" | 300/f | Elevation underway current level `k` / ko |

##### Fork command:

- The command `fork` creates a new slot and an egg
- as long as the egg has not hatched the player who laid the egg cannot do any other action
- When a client connects to a free slot of their team an available egg from the team is selected randomly.
- The selected egg then hatch and the newly spawned player starts with a random direction.

##### Inventory command:

This command allows you to see what resource the player has and how long he has left to live.

>*Ressource:*
>    - linemate
>    - deraumere
>    - sibur
>    - mendiane
>    - phiras
>    - thystame

>*Exemple:*
>"[ food 345 , sibur 3 , phiras 5 , ... , deraumere 0]\ n"

##### Broadcast command:

the server will then send the message to all its clients.

`"message K , text\n"` where `K` is the tile where the sound is comming from.

##### Ejection command:

- When a client send the eject command to the server, all of the clients that are sharing the tile will receive the following line:

    `eject : K\n` where `K` is the direction of the tile where the pushed player is coming from.

- When a player eject all other being from the unit of terrain it also destroy any eggs layed on that unit.