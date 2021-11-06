//Ejemplo simple de definición y creación del Gamepad en modo DirectInput con la librería de Heironimus
//Añadiendo un botón


#include <Joystick.h>

//En este ejemplo tendríamos un Gamepad de 1 botón unicamente

Joystick_ Joystick(JOYSTICK_DEFAULT_REPORT_ID,JOYSTICK_TYPE_GAMEPAD,
  1, 0,                  // Número de Botones (Máx. 128), Número de D-PAD (Máx. 2)
  false, false, false,     // Ejes X (si volante=false), Y (si acelerador2=false), Z (true= habilitado, false=deshabilitado)
  false, false, false ,   // Ejes Rx, Ry, Rz(si Freno o Timón=false) (true= habilitado, false=deshabilitado)
  false, false,          // Timón(si Rz o Freno=false), Acelerador
  false, false, false);  // Acelerador2(en columna de dirección, si Y=false), freno(si Rz o Timón = false), volante((en columna de dirección,si X=false)

void setup() {

  //Inicializamos los pines de los botones
  pinMode(2, INPUT_PULLUP); //Inicio el Pin2 en modo entrada y con resistencia

  // Inicializamos el joystick
  Joystick.begin();
}

void loop() {

  if (!digitalRead(2)) //Si el botón conectado al Pin 2 está pulsado
  {
    Joystick.setButton(0, 1);  //Activo el botón 0 del gamepad
  }
  else Joystick.setButton(0,0); //y si no, desactivo el botón 0 del gamepad

}
