# esp32-uart-router-diagnosis
Used an ESP32 to read the boot log of my dead ASUS router, since I had no UART adapter or multimeter. Wiring, sketches and results inside.

# initial problem 
so basically my router(asus tuf AX5400) was not turning or just lightup the logo and nothing is responding . reset button is not working so i cant put it in rescue mode . the only option that remain is to use UART header in my router to see if its bootloader that is not responding or hardware that is failing 

# second problem 
i don't have a usb to UART connected and dont want to pay for one time use , that's where esp32 comes . i already had esp32 

# things required 
1) esp32
2) 5* jumper wires
3) power delivery cable for both router and esp32
4) arduino ide

# setup 
first we need to identify which header in the router is for which purpose like (GND, VCC, TX, RX). if it is written in router then it is fine but if not then we need to identify the headers first . for that i have provided header_finder.ino file see that for more info <img width="3072" height="4080" alt="IMG_20261103_120143518" src="https://github.com/user-attachments/assets/587424b8-a330-4eaa-b31b-313d531d9c4b" />


# readings 
now that wiring is done power the router and in arduino ide open serial monitor at 115200 and press EN button on esp32 and look at the readings  <img width="1917" height="985" alt="image" src="https://github.com/user-attachments/assets/9e7c2adc-4075-4cce-b324-be04f75da505" /> 
from here the hole that gives the higest reading is the (TX) hole . now remove all other wires except the wire that gave the higest reading and then move to check if bootloader is alive or not 

# second phase 
now we move onto finding the log from startup using the TX hole that we find earlier . also remove all other wires from it except the TX one (which in my case is hole 3)
now run this file() on esp32 using arduino ide and see if you receive any bytes . in there is two case scenario 
1) 0 bytes received - then there is a hardware problem so nothing can be done
2) some bytes are coming - then the hardware is fine but the bootloader is bricked and needs to be replaced
<img width="1917" height="1016" alt="image" src="https://github.com/user-attachments/assets/9ff0141f-11e9-4efd-8774-15bf525ccd2c" />
in my case hardware is fine but bootloader is bricked 





