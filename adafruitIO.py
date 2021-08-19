from Adafruit_IO import Client, RequestError, Feed, Data
import serial
import time
import sys
puerto = serial.Serial()
puerto.baudrate = 9600
puerto.timeout = 3
puerto.port = 'COM2' 
puerto.open()

ADAFRUIT_IO_KEY = "aio_MTLj18KU18EKFTd3SpqBg6oNSVJV"
ADAFRUIT_IO_USERNAME = "XwaanPV"
aio = Client(ADAFRUIT_IO_USERNAME, ADAFRUIT_IO_KEY)

#Digital Feed
#line = puerto.readline()
#print(line)
digital_feed = aio.feeds('lab05-s1')
#aio.send_data(digital_feed.key, 42)
#digital_data = aio.receive(digital_feed.key)
#print(f'POTENCIA: {digital_data.value}')
#p = [""]
#Analog Feed
while 1:
    #with puerto:
        #for i in range(1):
            #p[i] = puerto.readline()
    #aio.send_data(digital_feed.key, int(p[0]))
    #aio.send_data(analog_feed.key, 22)
    puerto.close()
    ValorPORTD_feed = aio.feeds('lab05')        #NOMBRE DE Feed
    ValorPORTD_data = aio.receive('lab05').value    #ValordeFeed
    puerto.open()
    #print(f'TEMPERATURA: {analog_data.value}')
    #dat_envio = str(analog_data.value)
    puerto.write(chr(int(ValorPORTD_data)).encode()) #EnvioHaciaPic
    time.sleep(5)
