
/*----------------------------------------------------------
    MH-Z19 CO2 sensor  SAMPLE
  ----------------------------------------------------------*/
#include <MHZ19_uart.h> // incluye librería para manejo del sensor de CO2
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

//Crear el objeto display  dirección  0x27 y 16 columnas x 2 filas
LiquidCrystal_I2C display(0x27,16,2);  //


const int rx_pin = 3;	//Serial rx pin no
const int tx_pin = 4;	//Serial tx pin no
const int buzzer = 12 ;
int cnt = 0; // cuenta LOOPS

MHZ19_uart mhz19; // asigna medidor al sensor

void setup() {

  pinMode(buzzer, OUTPUT); //Inicia buzzer
  tone(buzzer, 55,20);
  // Inicializar el display
  display.begin();
  display.clear(); // borra pantalla
  
  //Encender la luz de fondo.
  display.backlight();

    // Escribimos el Mensaje en el display.
  display.setCursor(0, 1); // Ubicamos el cursor en la primera posición(columna:0) de la segunda línea(fila:1)
  display.print("INICIANDO");
  delay(5000);
  display.clear(); // borra pantalla
/*----------------------------------------------------------
    calentando MH-Z19 CO2 sensor
  ----------------------------------------------------------*/

  mhz19.begin(rx_pin, tx_pin); // inicializa el sensor
  mhz19.setAutoCalibration(false);
  
// muestra indicación de que está calentando 
  display.setCursor(0, 0); // Ubicamos el cursor en la primera posición(columna:0) de la primera línea(fila:0)
  display.print("Calentando");    // Escribe primera linea del cartel
  display.setCursor(0, 1); // Ubicamos el cursor en la primera posición(columna:0) de la primera línea(fila:0)
  display.print("Espere 3 minutos");  // Escribe segunda linea del cartel
  
  delay(90000);
  display.clear(); // borra pantalla  

  tone(buzzer, 55,100); // pitido de 55Hz indicando que funciona normal, calentando
}

/*----------------------------------------------------------
    MH-Z19 CO2 sensor  loop
  ----------------------------------------------------------*/
void loop() {

  if ( ++cnt % 30 == 0) { // Si cnt es múltiplo de 30
    display.clear(); // borra pantalla  
    display.setCursor(0,0);
    display.print("MEDIDOR CO2"); // Cada minuto muestra el valor
    display.setCursor(0, 1); // Ubicamos el cursor en la primera posición(columna:0) de la segunda línea(fila:1)
    display.print("UNAHUR");    // Escribe texto
    delay(3000); //demora 3 seg entre mediciones
    cnt = 0; // vuelve a empezar LOS LOOPS
  } else {

  }
  
  int co2ppm = mhz19.getPPM(); // mide CO2
  int temp = mhz19.getTemperature(); // mide temperatura

//  Muestra medición de CO2    
  display.clear(); // borra pantalla
  display.setCursor(0, 0); // Ubicamos el cursor en la primera posición(columna:0) de la primera línea(fila:0)
  display.print("co2: ");    // Escribe texto
  display.setCursor(8, 0); // Ubicamos el cursor en la novena posición(columna:8) de la primera línea(fila:0)
  display.print(co2ppm); // Escribe CO2
  display.setCursor(12, 0); // Ubicamos el cursor en la treceava posición(columna:12) de la primera línea(fila:0)
  display.print("ppm"); // Escribe texto
  
//  Muestra medición de temperatura
  display.setCursor(0, 1); // Ubicamos el cursor en la primera posición(columna:0) de la segunda línea(fila:1)
  display.print("temp: ");    // Escribe texto
  display.setCursor(8, 1); // Ubicamos el cursor en la novena posición(columna:8) de la segunda línea(fila:1)
  display.print(temp); // Escribe temperatura
  display.setCursor(12, 1); // Ubicamos el cursor en la treceava posición(columna:12) de la segunda línea(fila:1)
  display.print("*C"); // Escribe texto

//  Emite un sonido en función del resultado
    int tono = co2ppm / 100;
    switch (tono){
    case 5: // menor a 600ppm, 55Hz, 0.1 seg
       tone(buzzer, 55,100); break;
    case 6: // menor a 700ppm, 55Hz, 0.1 seg// menor a 600ppm
       tone(buzzer, 55,100); break;       
    case 7: // menor a 800ppm, 55Hz, 0.1 seg
       tone(buzzer, 55,100); break;
    case 8: // menor a 900ppm, 110Hz, 1 seg
       tone(buzzer, 110,1000); break;
    case 9: // menor a 1000ppm, 220Hz, 2 seg
       tone(buzzer, 220,2000); break;
    case 10: // menor a 1100ppm, 440Hz, 2 seg
       tone(buzzer, 440,2000); break;
    case 11: // menor a 120ppm, 880Hz, 2 seg
       tone(buzzer, 880,2000); break;
    case 12: // menor a 1300ppm, 880Hz, 4 seg
       tone(buzzer, 880,4000); break;
    default:  // otro valor, no hace ruido
      break;
    }
   
  delay(10000); //demora 10 seg entre mediciones
}
