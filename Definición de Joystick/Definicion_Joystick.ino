//Ejemplo simple de definición y creación del Gamepad en modo DirectInput con la librería de Heironimus
//Máximo 128 botones, 2 D-PAD y 7 ejes

#include <Joystick.h>

//En este ejemplo tendríamos un Gamepad de 128 botones, 2 D-Pad y 7 ejes (Rx, Ry, Acelerador, Freno y columna de dirección con volante y acelerador)

Joystick_ Joystick(JOYSTICK_DEFAULT_REPORT_ID,JOYSTICK_TYPE_GAMEPAD,
  128, 2,                  // Número de Botones (Máx. 128), Número de D-PAD (Máx. 2)
  false, false, true,     // Ejes X (si volante=false), Y (si acelerador2=false), Z (true= habilitado, false=deshabilitado)
  true, true, false ,   // Ejes Rx, Ry, Rz(si Freno o Timón=false) (true= habilitado, false=deshabilitado)
  false, true,          // Timón(si Rz o Freno=false), Acelerador
  true, true, true);  // Acelerador2(en columna de dirección, si Y=false), freno(si Rz o Timón = false), volante((en columna de dirección,si X=false)

void setup() {

  // Inicializamos el joystick
  Joystick.begin();
}

void loop() {

}