# Medidor-de-CO2
Medidor de CO2 con Arduino o WEMOS D1 Mini y sensor MH-Z19

Este proyecto tiene dos veriones. Una está diseñada con un Arduino Nano y un sensor de CO2 Winsen MH-Z19. La otra con un WEMOS D1 Mini, que permite conectar con WiFi, y un sensor de CO2 Winsen MH-Z19.
La descripción sobre cómo armar en circuito se puede consultar en http://www.jorgealiaga.com.ar/?page_id=2864 

Además del controlador y el sensor se usa un display o una pantalla con salída I2C para mostrar las mediciones y un boozer para indicar que se sobrepasan los niveles de CO2 seguros.

Se han usado las librerías:
Sensor MH-Z19  https://github.com/piot-jp-Team/mhz19_uart 
Display https://github.com/fdebrabander/Arduino-LiquidCrystal-I2C-library 
Oled SH1106 ( https://github.com/wonho-maker/Adafruit_SH1106 , https://github.com/adafruit/Adafruit-GFX-Library , https://github.com/adafruit/Adafruit_BusIO )


IMPORTANTE: ver la versión 2 que incorpora importantes mejoras (https://github.com/jlaliaga/Medidor-de-CO2/releases/tag/V2) 
