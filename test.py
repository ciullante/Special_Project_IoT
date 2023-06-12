
import Adafruit_IO
import serial
import re
import time
import serial.tools.list_ports

ADAFRUIT_IO_KEY = 'aio_VjUM237vZvYjFVO9JJgdYw6BY14z'
ADAFRUIT_IO_USERNAME = 'ciullante'
SERIAL_MESSASGE_LENGHT = 13
DESIRED_UPDATE_TIME = 5
UPDATE_TIME_THRESHOLD = 500

try:
    try:
        aio = Adafruit_IO.Client(ADAFRUIT_IO_USERNAME, ADAFRUIT_IO_KEY)
        feed = aio.feeds('temperature')
    except Adafruit_IO.RequestError:
        print("Invalid login values")
        exit()
    port = serial.tools.list_ports.comports()[0]
    ser = serial.Serial(port.device, 115200)
    sleeping_time = DESIRED_UPDATE_TIME
    
    while True:
        while ser.in_waiting != 0:
            ser.reset_input_buffer()
            time.sleep(0.10)
        temp = ser.readline().decode()
        temp = re.findall("\d+\.\d+", temp)[0]
        try:
            aio.send_data(feed.key, temp)
            if sleeping_time > DESIRED_UPDATE_TIME:
                sleeping_time = sleeping_time - 1 #Response to exponential backoff, similar to TCP
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
