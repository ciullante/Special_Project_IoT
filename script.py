
import Adafruit_IO
import serial
import re
import time

ADAFRUIT_IO_KEY = ''
ADAFRUIT_IO_USERNAME = ''
SERIAL_MESSASGE_LENGHT = 13
INITIAL_UPDATE_TIME = 1
UPDATE_TIME_THRESHOLD = 500

try:
    try:
        aio = Adafruit_IO.Client(ADAFRUIT_IO_USERNAME, ADAFRUIT_IO_KEY)
        feed = aio.feeds('temperature')
    except Adafruit_IO.RequestError:
        print("Invalid login values")
        exit()
    ser = serial.Serial('/dev/ttyUSB0', 115200)
    sleeping_time = INITIAL_UPDATE_TIME
    while True:
        if ser.in_waiting != 0 and (ser.in_waiting%SERIAL_MESSASGE_LENGHT) == 0:
            lines = ser.read_all()
            if lines != None :
                lines = lines.decode().strip("\n\r").split("\n\r")
                temp = lines[-1]
                temp = re.findall("\d+\.\d+", temp)[0]
                try:
                    aio.send_data(feed.key, temp)
                except Adafruit_IO.ThrottlingError:
                    print("too fast")
                    if sleeping_time > UPDATE_TIME_THRESHOLD:
                        print("Adafruit can't go faster than selected threshold: TERMINATING")
                        exit()
                    sleeping_time = sleeping_time * 2 #exponential backoff
                print(temp)
        time.sleep(sleeping_time)
except Exception as e:
    print(e)
    exit()
