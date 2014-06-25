import RPi.GPIO as GPIO
import serial, time
import datetime
import sys

GPIO.setmode(GPIO.BCM)
GPIO.setup(9, GPIO.IN) #MISO
GPIO.setup(10, GPIO.IN) #MOSI
GPIO.setup(11, GPIO.IN) #SCLK

P = 'P'

ser = serial.Serial('/dev/ttyAMA0', 9600)

led = raw_input("What led do you want to change?: ")

if led.lower() == "all" :
	led = "FF"

else :
	if len(led) == 1 :
		led = str(0) + led

colour = raw_input("Input hex for the colour to change it to!: ")

ledCol = str(P) + led + colour

print(ledCol)

ser.write(ledCol)

ser.close()
