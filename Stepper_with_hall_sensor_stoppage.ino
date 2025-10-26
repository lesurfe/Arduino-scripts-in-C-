/*
	Capitulo 31 de Arduino desde cero en Español.
	Programa que utiliza la Libreria Stepper para el control de un motor unipolar
	de 5 hilos modelo 28BYJ-48 y su correspondiente driver ULN2003. Se establece una
	velocidad de 2 RPM y un total de 512 pasos equivalentes a un cuarto de vuelta.

	Autor: bitwiseAr  

*/

#include <Stepper.h>			// incluye libreria stepper

int hall_sensor = 7;

Stepper motor1(2048, 8, 10, 9, 11);  	// pasos completos
 
void setup() {

  pinMode(hall_sensor, INPUT);

  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);

  motor1.setSpeed(2); // en RPM (valores de 1, 2 o 3 para 28BYJ-48)

}
 
void loop() {

  int sensorState = digitalRead(hall_sensor);

  if (sensorState == LOW) // si el iman no fue detectado entonces el motor esta girando y la luz apagada
  { 
    digitalWrite(LED_BUILTIN, HIGH);
    motor1.step(4); // cantidad de pasos
  }

  else{
    digitalWrite(LED_BUILTIN, LOW); // si el iman fue detectado parar motor y prender la luz
  }

  delay(20);				// demora de 2 seg. por cuestiones practicas
}