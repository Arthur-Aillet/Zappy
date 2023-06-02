def fowards():
    return

def left():
    return

def right():
    return

def look():
    return 1;

def pick_up():
    return

def look_arround():
    found_obj = -1;
    for i in range(4):
        found_obj = look
        if (found_obj != -1):
            return found_obj
    return found_obj

def spiral(i):
    while i > 0:
        i -= 1;
        fowards();
        if look() != -1:
            return True;
    right()
    return False

def go_to(i):
    row_max = 1;
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
    switch += 1;
    if switch % 2 == 0:
        spiral_len += 1;
    if spiral(spiral_len):
        go_to(look)
        pick_up()
        while look_arround != -1:
            go_to(look_arround);
            pick_up();

def main():
    switch = 0;
    spiral_len = 1;
    while True:
        loop();
