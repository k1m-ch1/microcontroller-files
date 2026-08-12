from machine import Pin
import time

delay_time = 1
led = Pin("LED", Pin.OUT)

while True:
    led.toggle()
    time.sleep(delay_time)
