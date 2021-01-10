# Medidor-de-CO2
Medidor de CO2 con Arduino y sensor MH-Z19

Este proyecto está diseñado con un Arduino Nano y un sensor de CO2 Winsen MH-Z19.
La descripción sobre cómo armar en circuito se puede consultar en 

Además del controlador y el sensor se usa un display o una pantalla con salída I2C para mostrar las mediciones y un boozer para indicar que se sobrepasan los niveles de CO2 seguros.

Se han usado las librerías:
Sensor MH-Z19  https://github.com/piot-jp-Team/mhz19_uart 
Display https://github.com/fdebrabander/Arduino-LiquidCrystal-I2C-library 
Oled SH1106 ( https://github.com/wonho-maker/Adafruit_SH1106 , https://github.com/adafruit/Adafruit-GFX-Library , https://github.com/adafruit/Adafruit_BusIO )
