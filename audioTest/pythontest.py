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
waves = pygame.mixer.Sound("audio/waves.wav")
horn = pygame.mixer.Sound("audio/wub.wav")
atmos = pygame.mixer.Sound("audio/atmosphere.wav")
industrial= pygame.mixer.Sound("audio/industrialambience.wav")
machines = pygame.mixer.Sound("audio/machines.wav")
metal = pygame.mixer.Sound("audio/metal-hammers.wav")

""" Play Sound Files """
waves.play(-1)
waves.set_volume(0.2)#-1 repeats song forevere (until program closed)
#horn.play().set_volume(hornVol)
#atmos.play().set_volume(hornVol)
#industrial.play().set_volume(hornVol)
#machines.play().set_volume(hornVol)
#metal.play().set_volume(hornVol)


"""" Functions """
def updateVol():
    if int(sensorVal) > 100:
        waves.set_volume(0.9)
    elif int(sensorVal) < 100:
        waves.set_volume(0.2)
    print(waves.get_volume())
    print("updateVol")
    #sys.stdout.write("testbegin")
    globalVol = 1
    #sys.stdout.write("testend")


while True:
    print(waves.get_volume())
    sensorVal = int(ser.readline())
    print(int(sensorVal))
    updateVol()
    #t = threading.Timer(5.0, updateVol)
    #t.start()
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            sys.exit()