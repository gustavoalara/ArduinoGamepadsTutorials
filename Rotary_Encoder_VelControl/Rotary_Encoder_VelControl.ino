#define outputA 1 //Definimos a qué pin conectamos el Pin Output A del Rotary
#define outputB 0 //Definimos a qué pin conectamos el Pin Output B del Rotary
#define button 2 //Definimos a qué pin conectamos el Pin Output B del Rotary
#include <Mouse.h> //Incluimos la librería para manejar el ratón

int EstadoInicial;
int UltimoEstado;
int vel = 5;

void setup(){

       pinMode (outputA,INPUT); //Ponemos el Pin asignado a OutputA en modo Input (escucha)
       pinMode (outputB,INPUT); //Ponemos el Pin asignado a OutputB en modo Input (escucha)
       pinMode (button, INPUT_PULLUP); //Ponemos el Pin asignado a button en modo Input_pullup (escucha con resistencia)
       Mouse.begin(); //Iniciamos el ratón
       UltimoEstado = digitalRead(outputA);   //Leemos el valor incial dado por el OutputA como último estado


 }

void loop(){
  EstadoInicial = digitalRead(outputA); //Leemos el valor incial dado por el OutputA como estado inicial
if (EstadoInicial != UltimoEstado) //Si los estados son distintos es que se ha girado el rotary y...
   {
      if (digitalRead(outputB) != EstadoInicial) // .. si la lectura de OutputB es distinta del estado incial es que hemos movido a la derecha
      {
          Mouse.move(+vel,0,0);
      }
      else                                      // ...y si es igual movemos a la izquierda
      {
          Mouse.move(-vel,0,0);
      }
   }

UltimoEstado = EstadoInicial; // Guardamos el ultimo valor
//Aumentamos la velocidad si pulsamos el botón del Encoder
if (!digitalRead(button))
  {
    vel = vel + 5;
      if (vel >= 40) vel = 5;
  }
   
}
