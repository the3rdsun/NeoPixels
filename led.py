import RPi.GPIO as GPIO
import serial, time
import datetime
import sys

GPIO.setmode(GPIO.BCM)
GPIO.setup(9, GPIO.IN) #MISO
GPIO.setup(10, GPIO.IN) #MOSI
GPIO.setup(11, GPIO.IN) #SCLK

ser = serial.Serial('/dev/ttyAMA0', 9600)

while True :
	t = datetime.datetime.now().time()	
	minute = t.minute
	second = t.second
	
	if len(str(minute)) == 1 :
		minute = str(0) + str(minute)

	if len(str(second)) == 1 :
		second = str(0) + str(second)

	minSec = str(minute) + str(second)	

	#print(minSec)

	ser.write(str(minSec))
	time.sleep(1)

ser.close()
