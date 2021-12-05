
#include <PS2Mouse.h>
#include <Mouse.h>
//Definimos los pines SDA y SCL del Arduino
#define TRACKBALL_DATA 2
#define TRACKBALL_CLOCK 3


PS2Mouse trackball(TRACKBALL_CLOCK, TRACKBALL_DATA, STREAM);


void setup()
{
  trackball.initialize();
  Mouse.begin();
  
}


void loop()
{
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
  Right_Click = ((N >> 2) & 1);
  Middle_Click = ((N >> 1) & 1);

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
