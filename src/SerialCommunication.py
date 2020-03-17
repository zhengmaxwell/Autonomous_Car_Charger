import serial 
import time
import RPi.GPIO as GPIO

s = serial.Serial('/dev/ttyS3', 9600)

while True:
    input = s.read()

    if input == -1:
        s.write('S') # STOP
    else:
        s.write('G') # GO

    if input == 1:
        s.write('X') # X Motor
    if input == 2:
        s.write('Y') # Y Motor
    if input == 3:
        s.write('Z') # Z Motor

    if input == 0:
        s.write('F') # Flip Direction