'''
TeleOp Program for NSL_S2AV
@Author: Behrad Toghi
@Version: 1.0.0
'''

# Libraries
import math
import keyboard
import os
import time


class vehicle(object):
    #constructor
    def __init__(self, setThrottle, setSteering):
        self.throttle = setThrottle
        self.steering = setSteering

    #getters

    #setters

    def __str__(self):
        return "Throttle = " + str(math.floor(self.throttle)) + " , " + "Steering = " +  str(math.floor(self.steering))

# def getCh():
#     import sys
#     import termios
#     import fcntl
#     import os
#     fd = sys.stdin.fileno()
#
#     oldterm = termios.tcgetattr(fd)
#     newattr = termios.tcgetattr(fd)
#     newattr[3] = newattr[3] & ~termios.ICANON & ~termios.ECHO
#     termios.tcsetattr(fd, termios.TCSANOW, newattr)
#     oldflags = fcntl.fcntl(fd, fcntl.F_GETFL)
#     fcntl.fcntl(fd, fcntl.F_SETFL, oldflags | os.O_NONBLOCK)
#     try:
#         while 1:
#             try:
#                 c = sys.stdin.read(1)
#                 break
#             except IOError:
#                 pass
#     finally:
#         termios.tcsetattr(fd, termios.TCSAFLUSH, oldterm)
#         fcntl.fcntl(fd, fcntl.F_SETFL, oldflags)
#     return c
##############################################

def throttle_forward(teleOp):
    ttl_step = 2
    teleOp.throttle += ttl_step
    write(int(math.floor(teleOp.throttle)), 'throttle.txt')

def throttle_reverse(teleOp):
    ttl_step = 2
    teleOp.throttle -= ttl_step
    write(int(math.floor(teleOp.throttle)), 'throttle.txt')

def steer_right(teleOp):
    str_step = 1
    teleOp.steering += str_step
    write(int(math.floor(teleOp.steering)), 'steering.txt')

def steer_left(teleOp):
    str_step = 1
    teleOp.steering -= str_step
    write(int(math.floor(teleOp.steering)), 'steering.txt')

def hard_right(teleOp):
    teleOp.steering = 125
    write(int(math.floor(teleOp.steering)), 'steering.txt')

def hard_left(teleOp):
    teleOp.steering = 65
    write(int(math.floor(teleOp.steering)), 'steering.txt')

def hard_brake(teleOp):
    if 1900 > teleOp.throttle > 1650:
        goToPark()
        teleOp.throttle = 1050
    elif 1100 < teleOp.throttle <1550:
        goToPark()
        teleOp.throttle = 1950



def write (val, path):
    f = open(path, 'w')
    f.write(str(val))
    f.close()

def goToPark():
    ttl = 1600
    str = 90
    teleOp = vehicle(ttl, str)

    write((teleOp.throttle), 'throttle.txt')
    write((teleOp.steering), 'steering.txt')
    return teleOp

def main():

    #Initialization
    run = True
    brake = False
    steer = False
    teleOp = goToPark()
    while run:

        if keyboard.is_pressed("w"):
            if teleOp.throttle < 1950:
                throttle_forward(teleOp)

        if keyboard.is_pressed("s"):
            if teleOp.throttle > 1050:
                throttle_reverse(teleOp)

        if keyboard.is_pressed("d"):
            if teleOp.steering < 125:
                steer_right(teleOp)

        if keyboard.is_pressed("a"):
            if teleOp.steering > 65:
                steer_left(teleOp)

        if steer and not keyboard.is_pressed("e") and not keyboard.is_pressed("q"):
            teleOp.steering = 90
            write(teleOp.steering, 'steering.txt')
            steer = False

        if keyboard.is_pressed("e"):
            hard_right(teleOp)
            steer = True

        if keyboard.is_pressed("q"):
            hard_left(teleOp)
            steer = True

        if brake and not keyboard.is_pressed("b"):
            teleOp.throttle = 1600
            write(teleOp.throttle, 'throttle.txt')
            brake = False

        if keyboard.is_pressed("b"):
            hard_brake(teleOp)
            brake = True

        if keyboard.is_pressed("p"):
            teleOp = goToPark()

        if keyboard.is_pressed("0"):
            teleOp = goToPark()
            write((teleOp.throttle), 'throttle.txt')
            run = False

        showDash(teleOp)
        time.sleep(0.01)
    print('\n **Program Terminated**')



def showDash(teleOp):

    print('''
               ****************************************************************************
               ******                    **Networked Systems Lab**                   ******
               ******                     TeleOp V.1.0.1 Running                     ******
               ******                                                                ****** 
               ******                              |W|                               ******
               ******                                                                ****** 
               ******       Hard Left: |Q|    |A|  |S|  |D|    Hard Right: |E|       ******
               ******                                                                ******
               ******                         |B|       |P|                          ******
               ******                        Brake      Park                         ****** 
               ****************************************************************************                                                               
               Odometry Info:''')
    print (teleOp)
    print('''  
               ****************************************************************************
               Press "0" to Terminate
        
               TeleOp by: Behrad Toghi, NSL
               ****************************************************************************                                                               
               ''')

if __name__ == "__main__":
    main()