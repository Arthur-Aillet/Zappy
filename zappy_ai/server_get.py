##
## EPITECH PROJECT, 2022
## zappy [WSL: Ubuntu]
## File description:
## server_get.py
##

from connect import send_server

def look(client):
    answer = str(send_server(client, "Look"))[4:-6].split(", ")
    for i in range(len(answer)):
        answer[i] = answer[i].split()
    return answer

def inventory(client):
    answer = send_server(client, "Inventory")
    if len(answer) < 5:
        return {'food': 0, 'linemate': 0, 'deraumere': 0, 'sibur': 0, 'mendiane': 0, 'phiras': 0, 'thystame': 0}
    answer = str(answer)[4:-5].replace(',', '').split()
    if len(answer) % 2 != 0:
        return {'food': 0, 'linemate': 0, 'deraumere': 0, 'sibur': 0, 'mendiane': 0, 'phiras': 0, 'thystame': 0}
    output = {}
    for i in range(0, len(answer), 2):
        output[answer[i]] = int(answer[i + 1])
    return output