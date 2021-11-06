//Ejemplo simple de definición y creación del Gamepad en modo DirectInput con la librería de Heironimus
//Añadiendo un D-Pad y 2 botones


#include <Joystick.h>

//En este ejemplo tendríamos un Gamepad con un D-PAD y 2 botones

Joystick_ Joystick(JOYSTICK_DEFAULT_REPORT_ID,JOYSTICK_TYPE_GAMEPAD,
  2, 1,                  // Número de Botones (Máx. 128), Número de D-PAD (Máx. 2)
  false, false, false,     // Ejes X (si volante=false), Y (si acelerador2=false), Z (true= habilitado, false=deshabilitado)
  false, false, false ,   // Ejes Rx, Ry, Rz(si Freno o Timón=false) (true= habilitado, false=deshabilitado)
  false, false,          // Timón(si Rz o Freno=false), Acelerador
  false, false, false);  // Acelerador2(en columna de dirección, si Y=false), freno(si Rz o Timón = false), volante((en columna de dirección,si X=false)

void setup() {

  //Inicializamos los pines de los botones
  pinMode(2, INPUT_PULLUP); //Inicio el Pin2 en modo entrada y con resistencia (Arriba)
  pinMode(3, INPUT_PULLUP); //Inicio el Pin3 en modo entrada y con resistencia (Derecha)
  pinMode(4, INPUT_PULLUP); //Inicio el Pin4 en modo entrada y con resistencia (Abajo)
  pinMode(5, INPUT_PULLUP); //Inicio el Pin5 en modo entrada y con resistencia (Izquierda)
  pinMode(6, INPUT_PULLUP); //Inicio el Pin2 en modo entrada y con resistencia (Botón 0)
  pinMode(7, INPUT_PULLUP); //Inicio el Pin2 en modo entrada y con resistencia (Botón 1)

  // Inicializamos el joystick
  Joystick.begin();
}

void loop() {
  //Gamepad
  if (!digitalRead(2)) //Si el botón conectado al Pin 2 está pulsado
  {
    Joystick.setHatSwitch(0, 0);  //Muevo el D-Pad 0 a  0 grados (Arriba)
  }
  if (!digitalRead(3)) //Si el botón conectado al Pin 3 está pulsado
  {
    Joystick.setHatSwitch(0, 90);  //Muevo el D-Pad 0 a 90 grados (Derecha)
  }
  if (!digitalRead(4)) //Si el botón conectado al Pin 4 está pulsado
  {
    Joystick.setHatSwitch(0, 180);  //Muevo el D-Pad 0 a 180 grados (Abajo)
  }
  if (!digitalRead(5)) //Si el botón conectado al Pin 5 está pulsado
  {
    Joystick.setHatSwitch(0, 270);  //Muevo el D-Pad 0 a 270 grados (Izquierda)
  }

  if (digitalRead(2) && digitalRead(3) && digitalRead(4) && digitalRead(5)) //Si ninguno de los pines 2,3,4, y 5 están pulsado
  {
    Joystick.setHatSwitch(0, -1);  //Dejo el D-Pad 0 al centro
  }
  
  //Botones
  if (!digitalRead(6)) //Si el botón conectado al Pin 6 está pulsado
  {
    Joystick.setButton(0, 1);  //Activo el botón 0 del gamepad
  }
  else Joystick.setButton(0,0); //y si no, desactivo el botón 0 del gamepad
  
  if (!digitalRead(7)) //Si el botón conectado al Pin 7 está pulsado
  {
    Joystick.setButton(1, 1);  //Activo el botón 0 del gamepad
  }
  else Joystick.setButton(1,0); //y si no, desactivo el botón 0 del gamepad

}