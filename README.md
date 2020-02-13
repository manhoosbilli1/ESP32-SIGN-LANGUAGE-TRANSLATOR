# ESP32-SIGN-LANGUAGE-TRANSLATOR
This project will play certain files when commands are given, show those commands on lcd. this project will be also be able to send current gps value through esp32 to a local server created on esp32

components used are amplifier, speaker, lcd, arduino nano, esp32, gprs and gsm module 

there are a few flex sensors attached to the fingers of a glove which is what's determining the pose of the hand. when certain value matches it will play a a file according to that command. it will also show that text on the lcd. all of this will be done when the toggle button is turned on 

when toggle button is turned off the code will switch to esp32, create a local server and upload current location i.e longitude, latitude. using gprs module. 
