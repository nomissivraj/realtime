""" Import Libraries/Dependencies """
import sys
import pygame
import threading
import serial
ser = serial.Serial('/dev/ttyUSB0', 9600)

""" Initial Program Variables """
sensorVal = 77
globalVol = 0.1 #default volume
hornVol = 0.5

""" initialisations """
gameDisplay = pygame.display.set_mode((640, 480))
pygame.mixer.pre_init(16000, 16, 2, 4096) #frequency, size, channels, buffersize
pygame.init() #turn all of pygame on.

""" Load Sound files """
waves = pygame.mixer.Sound("waves.wav")
horn = pygame.mixer.Sound("wub.wav")


""" Play Sound Files """
waves.play(-1).set_volume(globalVol) #-1 repeats song forevere (until program closed)
horn.play().set_volume(hornVol)


"""" Functions """
def updateVol():
    sys.stdout.write("testbegin")
    globalVol = 1
    t = threading.Timer(5.0, updateVol)
    t.start()
    sys.stdout.write("testend")

while True:
    sensorVal = int(ser.readline())
    print(reading)
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            sys.exit()