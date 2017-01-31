import smbus
import time
import random

bus = smbus.SMBus(1)
#address of slave (arduino)
adr_arduino1 = 0x4
adr_arduino2 = 0x5
time.sleep(0.1)

while True:
    r = random.randrange(0, 180)
    #send data to arduino with address of slave and data
    bus.write_byte(adr_arduino1, r)
    print("Angle: ", r)
    time.sleep(2)
