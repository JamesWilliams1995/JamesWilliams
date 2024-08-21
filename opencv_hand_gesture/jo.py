import serial
ser= serial.Serial()
ser.port='COM3'
ser.baudrate =9600

while True:
   
    if ser.in_waiting > 0:
        line = ser.readline().decode('utf-8').rstrip()
        print(line)