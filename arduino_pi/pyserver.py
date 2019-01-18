""" Import Libraries/Dependencies """
import sys
import pygame
import threading
import serial
# ser = serial.Serial('/dev/ttyUSB0', 9600) #mcu /dev/ttyUSB0 #installation /dev/ttyACM0
ser = serial.Serial('/dev/tty.usbmodem14101', 9600) #mcu /dev/ttyUSB0 #installation /dev/ttyACM0

""" Initial Program Variables """
sensorVal1 = 77
sensorVal2 = 77
sensorVal3 = 77
globalVol =  0.2
output1Vol = 0.2
output2Vol =  0.2
output3Vol =  0.2




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
waves.set_volume(globalVol)#-1 repeats song forever (until program closed)


#Keep track of whether audio elements have been played
hornPlayed = False
atmosPlayed = False
industrialPlayed = False
"""" Main Loop """
#Volume update loop that responds to the current sensor value and sets a global volume based on this
def updateVols():
    #Set default volume for global (waves) the sensor vals here will need to be whatever sensor is highest of the 3
    if int(sensorVal1) < 100:
        globalVol = 0.2
    else:#Map current sensor value to a new usable range of volume
        globalVol = map(int(sensorVal1), 0, 800, 0, 1)
    #update volume with current converted/mapped sensor value
    waves.set_volume(globalVol)
    
    #Handle volume for bottle 1
    if int(sensorVal1) < 100:
        output1Vol = 0.2
    else:
        output1Vol = map(int(sensorVal1), 0, 800, 0, 1);
        print("bottle 1 " +str(output1Vol))
    
    #Handle volume for bottle 2
    if int(sensorVal2) < 100:
        output2Vol = 0.2
    else:
        output2Vol = map(int(sensorVal2), 0, 800, 0, 1)
        print("bottle 2 " +str(output2Vol))
                
    #Handle volume for bottle 3
    if int(sensorVal3) < 100:
        output3Vol = 0.2
    else:
        output3Vol = map(int(sensorVal3), 0, 800, 0, 1)
        print("bottle 3 " +str(output3Vol))
        
    #print("Variable Volume: "+ str(globalVol))
    #print("Actual Volume: "+ str(waves.get_volume()))
    
    #PLAY BOTTLE 1 (ATMOSPHERE)
    global atmosPlayed #track if atmos played
    if (output1Vol > 0.2 and atmosPlayed == False) :
        atmosPlayed = True
        atmos.play()
        t = threading.Timer(258.0, resetAtmos)
        t.start()
    print("atmos played: " + str(atmosPlayed))
    atmos.set_volume(output1Vol)
    
    #PLAY BOTTLE 2
    global hornPlayed #track if horn played
    if (output2Vol > 0.2 and hornPlayed == False) :
        print("output2: " + str(output2Vol))
        hornPlayed = True
        horn.play()
        t = threading.Timer(4.0, resetHorn)
        t.start()
    print("horn played: " + str(hornPlayed))
    horn.set_volume(output2Vol)
    
    #PLAY BOTTLE 3
    global industrialPlayed #track if industrial played
    if (output3Vol > 0.2 and industrialPlayed == False) :
        print("output3: " + str(output3Vol))
        industrialPlayed = True
        industrial.play()
        t = threading.Timer(91.0, resetIndustrial)
        t.start()
    industrial.set_volume(output3Vol)
    print("Industrial played: " + str(industrialPlayed))

def resetAtmos() :
    global atmosPlayed
    #print("func!")
    atmosPlayed = False
    
def resetHorn() :
    global hornPlayed
    #print("func!")
    hornPlayed = False
    
def resetIndustrial() :
    global industrialPlayed
    #print("func!")
    industrialPlayed = False

"""" Functions """
#map function to convert orignal value and range to a 0-1 float range - usabel as volume
def map(value, originMin, originMax, newMin, newMax):
    #Get spread of each range
    originRange = originMax - originMin
    newRange = newMax - newMin
    
    #Convert original range into new range (0-1 - float)
    scaledVal = float(value - originMin) / float(originRange)
    
    #convert the new orignal scaled value into a value relative to the new range
    return newMin + (scaledVal * newRange)
###  end map function



while True:
    #print(ser.readline())
    #Store current sensor value from serial (ser)
    #sensorVal1 = int(ser.readline())
    #sensorVal2 = int(ser.readline())
    #sensorVal3 = int(ser.readline())
    
#TESTING
    sensorString = str(ser.readline()) 

    if "sensor1" in sensorString:
        sensorVal1 = int(sensorString[7:])
        print(int(string[7:]))
    elif "sensor2" in sensorString:
        sensorVal2 = int(sensorString[7:])
    elif "sensor3" in sensorString:
        sensorVal3 = int(sensorString[7:])
        
#TESTING
    
    
    #Run volume update loop
    updateVols()
    #t = threading.Timer(5.0, updateVol)
    #t.start()
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            sys.exit()