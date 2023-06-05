from connect import connect
from sys import stderr

RETRY = 5

def send_server(client, message):
    answer = b'ko\n'
    trys = 0
    while answer == b'ko\n' and trys < RETRY:
        trys += 1
        client.send(bytes(message + "\n", "utf-8"))
        answer = client.recv(1024)
    if answer == b'ko\n':
        stderr.write("ko on " + str(answer) + "\n")
    return answer

def broadcast(client, text):
    if send_server(client, "Broadcast " + text) == b'ok\n':
        return True
    return False

def fowards(client):
    if send_server(client, "Forward") == b'ok\n':
        return True
    return False

def left(client):
    if send_server(client, "Left") == b'ok\n':
        return True
    return False

def right(client):
    if send_server(client, "Right") == b'ok\n':
        return True
    return False

def look(client):
    answer = send_server(client, "Look")
    return 1

def pick_up(client):
    if send_server(client, "Take object") == b'ok\n':
        return True
    return False

def look_arround():
    found_obj = -1
    for i in range(4):
        found_obj = look
        if (found_obj != -1):
            return found_obj
    return found_obj

def spiral(i):
    while i > 0:
        i -= 1
        fowards()
        if look() != -1:
            return True
    right()
    return False

def go_to(i):
    row_max = 1
    while i < row_max :
        i -= row_max
        row_max += 2
    if (row_max / 2 < i):
        left()
    if (row_max / 2 > i):
        right()
    for n in range(abs(row_max - (i))):
        fowards()
    pick_up()
    return

def loop(switch, spiral_len):
    switch += 1
    if switch % 2 == 0:
        spiral_len += 1
    if spiral(spiral_len):
        go_to(look)
        pick_up()
        while look_arround != -1:
            go_to(look_arround)
            pick_up()

def main():
    client_num, map_x, map_y = connect()
    switch = 0
    spiral_len = 1
    while True:
        loop()
