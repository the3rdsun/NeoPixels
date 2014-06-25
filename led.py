import RPi.GPIO as GPIO
import serial, time
import datetime
import sys

GPIO.setmode(GPIO.BCM)
GPIO.setup(9, GPIO.IN) #MISO
GPIO.setup(10, GPIO.IN) #MOSI
GPIO.setup(11, GPIO.IN) #SCLK

ser = serial.Serial('/dev/ttyAMA0', 9600)

led = raw_input("What led do you want to change?: ")

if led.lower() == "all" :
	led = "FF"

else :
	if len(led) == 1 :
		led = str(0) + led

print("All colours are percentages out of 100!")

red = raw_input("How much red?: ")
green = raw_input("How much green?: ")
blue = raw_input("How much blue?: ")

red = float(red)
green = float(green)
blue = float(blue)

red = red * 2.5
green = green * 2.5
blue = blue * 2.5

red = hex(int(red))[2:]
print(red)
green = hex(int(green))[2:]
print(green)
blue = hex(int(blue))[2:]
print(blue)

if len(red) == 1 :
	red = str(0) + str(red)

if len(green) == 1 :
	green = str(0) + str(green)

if len(blue) == 1 :
	blue = str(0) + str(blue)

colour = str(red).upper() + str(green).upper() + str(blue).upper()

ledCol = 'P' + led + colour

print(ledCol)

ser.write(ledCol)

ser.close()
