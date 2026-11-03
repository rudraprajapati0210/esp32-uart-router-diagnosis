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
first we need to identify which header in the router is for which purpose like (GND, VCC, TX, RX). if it is written in router then it is fine but if not then we need to identify the headers first 


