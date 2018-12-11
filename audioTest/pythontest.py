""" Import Libraries/Dependencies """
import sys
import pygame
import threading
import serial
ser = serial.Serial('/dev/ttyUSB0', 9600)

""" Initial Program Variables """
sensorVal = 77
globalVol =  0.2
hornVol = 0.5

""" initialisations """
gameDisplay = pygame.display.set_mode((100, 100))
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
waves.set_volume(globalVol)#-1 repeats song forevere (until program closed)
#horn.play().set_volume(hornVol)
#atmos.play().set_volume(hornVol)
#industrial.play().set_volume(hornVol)
#machines.play().set_volume(hornVol)
#metal.play().set_volume(hornVol)


"""" Functions """
#Volume update loop that responds to the current sensor value and sets a global volume based on this
def updateVol():
    #Set default volume
    if int(sensorVal) < 100:
        globalVol = 0.2
    else:#Map current sensor value to a new usable range of volume
        globalVol = map(int(sensorVal), 0, 800, 0, 1)
    #update volume with current converted/mapped sensor value
    waves.set_volume(globalVol)
    
    print("Variable Volume: "+ str(globalVol))
    print("Actual Volume: "+ str(waves.get_volume()))

#map function to convert orignal value and range to a 0-1 float range - usabel as volume
def map(value, originMin, originMax, newMin, newMax):
    #Get spread of each range
    originRange = originMax - originMin
    newRange = newMax - newMin
    
    #Convert original range into new range (0-1 - float)
    scaledVal = float(value - originMin) / float(originRange)
    
    #convert the new orignal scaled value into a value relative to the new range
    return newMin + (scaledVal * newRange)
    
while True:
    #Store current sensor value from serial (ser)
    sensorVal = int(ser.readline())
    #Run volume update loop
    updateVol()
    #t = threading.Timer(5.0, updateVol)
    #t.start()
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            sys.exit()