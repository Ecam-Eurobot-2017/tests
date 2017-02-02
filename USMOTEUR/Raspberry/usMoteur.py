'''
Note: a TimeOutException appear when distance even 0.
'''

import smbus
import time

#slave arduino address
address_arduino = 0x04
bus = smbus.SMBus(1)

#get a measure by i2c
def getUSMeasure():
    bus.write_byte(address_arduino, 1)
    distance = bus.read_byte(address_arduino)
    return distance

#request rotate motor in a sens
def forward():
    bus.write_byte(address_arduino, 2)

#request rotate motor in the other sens
def backward():
    bus.write_byte(address_arduino, 3)

if __name__ == '__main__':
    while True:
        distance = getUSMeasure()
        print(distance)

        if distance < 20:
            backward()
            print('I move back')

        else:
            forward()
            print('I advance')

        time.sleep(0.1)
