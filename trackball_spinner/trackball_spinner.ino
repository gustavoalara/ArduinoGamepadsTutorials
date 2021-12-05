
#include <PS2Mouse.h>
#include <Mouse.h>
//Definimos los pines SDA y SCL del Arduino
#define TRACKBALL_DATA 2
#define TRACKBALL_CLOCK 3
#define outputA 0 //Definimos a qué pin conectamos el Pin Output A del Rotary
#define outputB 1 //Definimos a qué pin conectamos el Pin Output B del Rotary

//The previous state of the AB pins
int UltimoEstado = 0;



PS2Mouse trackball(TRACKBALL_CLOCK, TRACKBALL_DATA, STREAM);



void setup()
{
  pinMode (outputA,INPUT_PULLUP); //Ponemos el Pin asignado a OutputA en modo Input (escucha)
  pinMode (outputB,INPUT_PULLUP); //Ponemos el Pin asignado a OutputB en modo Input (escucha) 
  attachInterrupt(digitalPinToInterrupt(outputA), Rotary, CHANGE); //Indicamos que el PIN está en modo interrupción y que cuando haya cambios se vaya a la función Rotary
  attachInterrupt(digitalPinToInterrupt(outputB), Rotary, CHANGE); //Indicamos que el PIN está en modo interrupción y que cuando haya cambios se vaya a la función Rotary
  trackball.initialize();
  trackball.set_resolution(3);
  trackball.set_sample_rate(10);
  Mouse.begin();
  Serial.begin(9600);
 
}


void loop()
{
 //Movimiento de la trackball
  //Declaramos el array data que será donde se meterá la información que nos devuelva la trackball
  int16_t data[3];

  //Definimos las variables que almacenarán los valores de si está pulsado o no un botón del reatón
  int Left_Click;
  int Right_Click;
  int Middle_Click;


 
  //Recopilamos la información pasada por la trackball y la guardamos en el array declarado anteriormente

  trackball.report(data);
  
  //Convertimos a byte la primera cadena que envía de información 
  byte N = data[0];
  // Asignamos a cada variable del botón del ratón el valor del bit que le corresponde en la posición del byte y le hacemos un AND lógico
  Left_Click = ((N >> 0) & 1);
  Right_Click = ((N >> 1) & 1);
  Middle_Click = ((N >> 2) & 1);


  //Movemos el ratón con los datos de las dos cadenas siguientes que envía la trackball
  Mouse.move(-data[1],data[2]);
 
  //Comprobamos si se pulsan los botones del trackball y si es así se pulsan en el ratón 
  
  if (Left_Click)
  {
    Mouse.press(MOUSE_LEFT);
  } else Mouse.release(MOUSE_LEFT);
  
  if (Right_Click)
  {
    Mouse.press(MOUSE_RIGHT);
  } else Mouse.release(MOUSE_RIGHT);
  
  if (Middle_Click)
  {
    Mouse.press(MOUSE_MIDDLE);
  } else Mouse.release(MOUSE_MIDDLE);
}

void Rotary()
{
  int EstadoInicial = !digitalRead(outputA); //Leemos el valor incial dado por el OutputA como estado inicial
  if (EstadoInicial != UltimoEstado) //Si los estados son distintos es que se ha girado el rotary y...
   {
      if (!digitalRead(outputB) != EstadoInicial) // .. si la lectura de OutputB es distinta del estado incial es que hemos movido a la derecha
      {
          Mouse.move(+5,0,0);
      }
      else                                      // ...y si es igual movemos a la izquierda
      {
          Mouse.move(-5,0,0);
      }
   }
  UltimoEstado = EstadoInicial;
}
