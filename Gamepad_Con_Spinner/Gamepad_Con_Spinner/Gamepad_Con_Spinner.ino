//Ejemplo simple de definición y creación del Gamepad en modo DirectInput con la librería de Heironimus
//Añadiendo ejes X,Y y un botón
#define outputA 0 //Definimos a qué pin conectamos el Pin Output A del Rotary
#define outputB 1 //Definimos a qué pin conectamos el Pin Output B del Rotary
#define botonA 2 //Definimos a qué pin conectamos el Pin Output B del Rotary
#define botonB 3 //Definimos a qué pin conectamos el Pin Output B del Rotary
#define ejeX A0 //Definimos a qué pin conectamos el Pin Output B del Rotary
#define ejeY A1 //Definimos a qué pin conectamos el Pin Output B del Rotary

#include <Joystick.h>
#include <Mouse.h>
#include <Keyboard.h>

//Inicialización de variables para la rotación del Spinner/rotary_encoder
int EstadoInicial;
int UltimoEstado;
int GamepadMode = 0; //Modo 0 = Ratón, Modo 1 = Joystick


const int TIEMPO_PULSACION  = 500; // 500 milisegundos

// Variables will change:
int UltimoEstadoBotonA = LOW;  // Último estado del pin del botón A, lo ponemos a 0
int EstadoInicialBotonA;     // Estado actual del pin del botón A
unsigned long MomentoPulsacion  = 0; //Variable que guarda el momento en el que se presiona el botón
unsigned long MomentoLiberacion = 0; //Variable que guarda el momento en el que se suelta el botón

//En este ejemplo tendríamos un Gamepad con un stick X, Y y el botón del propio stick (tipo mando Xbox o Play)

Joystick_ Joystick(JOYSTICK_DEFAULT_REPORT_ID,JOYSTICK_TYPE_GAMEPAD,
  2, 0,                  // Número de Botones (Máx. 128), Número de D-PAD (Máx. 2)
  true, true, false,     // Ejes X (si volante=false), Y (si acelerador2=false), Z (true= habilitado, false=deshabilitado)
  false, false, false ,   // Ejes Rx, Ry, Rz(si Freno o Timón=false) (true= habilitado, false=deshabilitado)
  false, false,          // Timón(si Rz o Freno=false), Acelerador
  false, false, false);  // Acelerador2(en columna de dirección, si Y=false), freno(si Rz o Timón = false), volante((en columna de dirección,si X=false)




void setup() {

  //Inicializamos los pines de los botones
  pinMode (outputA,INPUT_PULLUP); //Ponemos el Pin asignado a OutputA en modo Input (escucha)
  pinMode (outputB,INPUT_PULLUP); //Ponemos el Pin asignado a OutputB en modo Input (escucha)
  pinMode(botonA, INPUT_PULLUP); //Inicio el botonA en modo entrada y con resistencia 
  pinMode(botonB, INPUT_PULLUP); //Inicio el botonB en modo entrada y con resistencia 

  // Inicializamos el joystick
  Joystick.begin();
  Serial.begin(9600);
  //Iniciamos el ratón
  Mouse.begin(); 
  Joystick.setXAxisRange(0,1023); //Definimos el rango del eje X (con los valores mínimos y máximos sacados por el puerto serie)
  Joystick.setYAxisRange(0,1023); //Lo mismo para el eje Y
  UltimoEstado = !digitalRead(outputA); //Leemos el valor del Output A del Rotary y lo asignamos como último estado

}

void loop() {
  if (GamepadMode == 0) //Funciones cuando estamos en modo Ratón
  {
    Serial.println("Modo Ratón");
    EstadoInicial = !digitalRead(outputA); //Leemos el valor incial dado por el OutputA como estado inicial

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
   UltimoEstado = EstadoInicial; // Guardamos el ultimo valor

   //Botones mapeado a teclado
   if (!digitalRead(botonA)) //Si el botón conectado al Pin 2 está pulsado
  {
    Keyboard.write(65);  //Letra A
  }
   
  if (!digitalRead(botonB)) //Si el botón conectado al Pin 2 está pulsado
  {
    Keyboard.write(66);  //Letra B
  }
  
 //Comprobamos si se ha pulsado el botón A durante 0,5 seg
 
     EstadoInicialBotonA = digitalRead(botonA); //Leemos el estado del botón A y lo almacenamos en la variable de estado inicial
     if(UltimoEstadoBotonA == HIGH && EstadoInicialBotonA == LOW){ //Si el estado actual es pulsado y el último no...
      MomentoPulsacion = millis();      // Guardamos en qué momento ha sido presionado el botón A
    }
    
  else if(UltimoEstadoBotonA == LOW && EstadoInicialBotonA == HIGH) //Si el estado actual es soltado y el último fue pulsado...
  {
     MomentoLiberacion = millis(); // Guardamos en qué momento ha sido liberado el botón A

    long DuracionPulsacion = MomentoLiberacion - MomentoPulsacion; //Calculamos cuánto tiempo ha pasado

    if( DuracionPulsacion > TIEMPO_PULSACION ) //Si el tiempo es mayor que el definido (0,5 seg) cambiamos de modo
    {
      GamepadMode = 1;
    }
  }
    // Almacenamos el último estado del botón A
  UltimoEstadoBotonA = EstadoInicialBotonA;


}

  if (GamepadMode == 1) //Funciones cuando estamos en modo gamepad
  {
    Serial.println("Modo Gamepad");
  //Botones
  if (!digitalRead(botonA)) //Si el botón conectado al Pin 2 está pulsado
  {
    Joystick.setButton(0, 1);  //Activo el botón 0 del gamepad
  }
  else Joystick.setButton(0,0); //y si no, desactivo el botón 0 del gamepad
 
  if (!digitalRead(botonB)) //Si el botón conectado al Pin 2 está pulsado
  {
    Joystick.setButton(1, 1);  //Activo el botón 1 del gamepad
  }
  else Joystick.setButton(1,0); //y si no, desactivo el botón 0 del gamepad

  //Ejes

  Joystick.setXAxis(analogRead(ejeX)); //Paso al eje X los valores de la posición del potenciómetro conectado al pin A0
  Joystick.setYAxis(analogRead(ejeY)); //Paso al eje Y los valores de la posición del potenciómetro conectado al pin A1
  
  
  //Comprobamos si se ha pulsado el botón A durante 0,5 seg
 
     EstadoInicialBotonA = digitalRead(botonA); //Leemos el estado del botón A y lo almacenamos en la variable de estado inicial
    if(UltimoEstadoBotonA == HIGH && EstadoInicialBotonA == LOW){ //Si el estado actual
      MomentoPulsacion = millis();      // Guardamos en qué momento ha sido presionado el botón A
    }
    
  else if(UltimoEstadoBotonA == LOW && EstadoInicialBotonA == HIGH)
  {
     MomentoLiberacion = millis(); // Guardamos en qué momento ha sido liberado el botón A

    long DuracionPulsacion = MomentoLiberacion - MomentoPulsacion; //Calculamos cuánto tiempo ha pasado

    if( DuracionPulsacion > TIEMPO_PULSACION ) //Si el tiempo es mayor que el definido (0,5 seg) cambiamos de modo
    {
      GamepadMode = 0;
    }
  }
    // Almacenamos el último estado del botón A
  UltimoEstadoBotonA = EstadoInicialBotonA;
  }
}


 
 
