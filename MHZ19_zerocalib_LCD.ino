/*----------------------------------------------------------
    MH-Z19 CO2 sensor  Zero calibration SAMPLE
  ----------------------------------------------------------*/
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <MHZ19_uart.h>

//Crear el objeto display  dirección  0x27 y 16 columnas x 2 filas
LiquidCrystal_I2C display(0x27,16,2);  //

const int rx_pin = 3;  //Serial rx pin no
const int tx_pin = 4;  //Serial tx pin no

const int waitingMinutes = 30;  //cantidad de minutos a esperar
const long waitingSeconds = waitingMinutes * 60L; // cantidad de segundos a esperar
long cnt = 0; // cuenta segundos

MHZ19_uart mhz19;

/*----------------------------------------------------------
    MH-Z19 CO2 sensor  setup
  ----------------------------------------------------------*/
void setup() {

  display.begin();
  display.clear(); // borra pantalla
  
  //Encender la luz de fondo.
  display.backlight();
  delay(1000);
  
  mhz19.begin(rx_pin, tx_pin); // setting rx and tx pin, and initialize Software Serial.

  /*   MH-Z19 has automatic calibration procedure. the MH-Z19 executing automatic calibration, its do zero point(stable gas environment (400ppm)) judgement.
       The automatic calibration cycle is every 24 hours after powered on.  
       If you use this sensor in door, you execute `setAutoCalibration(false)`.   */
  mhz19.setAutoCalibration(false);

/*  while ( mhz19.isWarming() ) { // la función gesStatus parece no funcionar
    display.setCursor(0, 0); // Ubicamos el cursor en la primera posición(columna:0) de la primera línea(fila:0)
    display.print("Calentando");    // Escribe primera linea del cartel
    display.setCursor(0, 1); // Ubicamos el cursor en la primera posición(columna:0) de la segunda línea(fila:1)
    display.print(mhz19.getStatus());  // Escribe segunda linea del cartel
    delay(1000);
    display.clear(); // borra pantalla
 } */

  display.clear(); // borra pantalla  
  display.setCursor(0, 0); // Ubicamos el cursor en la primera posición(columna:0) de la primera línea(fila:0)
  display.print("Calentando");    // Escribe primera linea del cartel
  display.setCursor(0, 1); // Ubicamos el cursor en la primera posición(columna:0) de la segunda línea(fila:1)
  display.print("Espere 1 minuto");  // Escribe segunda linea del cartel
  delay(60000); // espera 60 segundos
  display.clear(); // borra pantalla  

}

/*----------------------------------------------------------
    MH-Z19 CO2 sensor  loop
  ----------------------------------------------------------*/

void loop() {

  if ( ++cnt % 60 == 0) { // Si cnt es múltiplo de 60
    display.clear(); // borra pantalla  
    display.setCursor(0,0);
    display.print(cnt / 60); // Cada minuto muestra el valor
    display.setCursor(7,0);
    display.print("minutos"); // 
    display.setCursor(0, 1); // Ubicamos el cursor en la primera posición(columna:0) de la segunda línea(fila:1)
    display.print("co2: ");    // Escribe texto
    display.setCursor(8, 1); // Ubicamos el cursor en la novena posición(columna:8) de la segunda línea(fila:1)
    display.print(mhz19.getPPM()); // Escribe CO2
    display.setCursor(12, 1); // Ubicamos el cursor en la treceava posición(columna:12) de la segunda línea(fila:1)
    display.print("ppm"); // Escribe texto
  } else {
    display.clear(); // borra pantalla  
    display.setCursor(0,0);
    display.print(cnt); // muestra los segundos transcurridos
    display.setCursor(7,0);
    display.print("segundos");    
  }
  delay(1000); // Espera 1 segundo

  if (cnt > waitingSeconds) { // Se pasaron 30 minutos
    display.clear(); // borra pantalla  
    mhz19.calibrateZero(); // Calibra
    display.setCursor(0,0);
    display.print("PRIMERA"); //
    display.setCursor(0, 1); // Ubicamos el cursor en la primera posición(columna:0) de la segunda línea(fila:1)
    display.print("CALIBRACION");    // Escribe texto
    
    delay(60000); // Espera 60 segundos
    display.clear(); // borra pantalla  
    mhz19.calibrateZero();  // Calibra por segunda vez por las dudas
    display.setCursor(0,0);
    display.print("SEGUNDA"); //
    display.setCursor(0, 1); // Ubicamos el cursor en la primera posición(columna:0) de la segunda línea(fila:1)
    display.print("CALIBRACION");    // Escribe texto

    for ( int i = 0; i < 10; i++) { // muestra mediciones
      display.clear(); // borra pantalla
      display.setCursor(0, 0); // Ubicamos el cursor en la primera posición(columna:0) de la primera línea(fila:0)
      display.print("co2: ");    // Escribe texto
      display.setCursor(8, 0); // Ubicamos el cursor en la novena posición(columna:8) de la primera línea(fila:0)
      display.print(mhz19.getPPM()); // Escribe CO2
      display.setCursor(12, 0); // Ubicamos el cursor en la treceava posición(columna:12) de la primera línea(fila:0)
      display.print("ppm"); // Escribe texto
      delay(10000); // Espera 10 segundos
    }
    cnt = 0; // vuelve a enmpezar la calibración
    return;
  }

}
