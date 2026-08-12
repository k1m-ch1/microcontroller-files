So essentially, when we start up, the raspberry pi pico exposes a mass storage device which has a FAT16 file system. We can mount it and then upload some sort of binary which has the micro python interpreter, which can be found [here](https://www.raspberrypi.com/documentation/microcontrollers/micropython.html).

After that's done, we can unplug it and re-plug it and then now it exposes a USB CDC (Communication Device Class), which is basically UART, and when you talk to it using something like `tio`, you get a python REPL.

You can use it like a normal REPL, but you can get some sort of raw REPL using pressing `CTRL-A`.

But essentially, once we have that, we can literally send a piece of python code and run it.

To access the file system, it's scuff but we gotta use python's API to access the file system (at least there's a built in filesystem).

We can use something like `mpremote` to reveal a nicer interface.

```
mpremote connect /dev/ttyACM1 run ./001_blink.py 
```

Special features of the Pico:

- 12 bit ADC
- 16 bit PWM
- Programmable I/O or something
- USB 1.1
- low power mode
- 2 spi
- 2 i2c
- 2 uart
