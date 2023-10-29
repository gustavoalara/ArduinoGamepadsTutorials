#include <XInput.h>

// Setup
const int ADC_Max = 1023; 

// Joystick Pins
const int Pin_dpadUp    = 15;
const int Pin_dpadDown  = 16;
const int Pin_dpadLeft  = 14;
const int Pin_dpadRight = 10;

// Trigger Pins
const int Pin_TriggerL = 8;
const int Pin_TriggerR = 9;

// Button Pins
const int Pin_ButtonA = 2;
const int Pin_ButtonB = 3;
const int Pin_ButtonX = 6;
const int Pin_ButtonY = 7;

const int Pin_ButtonLB = 4;
const int Pin_ButtonRB = 5;

const int Pin_ButtonBack  = A0;
const int Pin_ButtonStart = A1;
const int Pin_ButtonLogo = 0;

const int Pin_ButtonL3  = A3;
const int Pin_ButtonR3 = A2;

int lastButtonState[4] = {0,0,0,0};
int currentButtonState;

void setup() {

  //Ponemos los pines en modo PullUp

	pinMode(Pin_TriggerL, INPUT_PULLUP);
	pinMode(Pin_TriggerR, INPUT_PULLUP);

	pinMode(Pin_ButtonA, INPUT_PULLUP);
	pinMode(Pin_ButtonB, INPUT_PULLUP);
	pinMode(Pin_ButtonX, INPUT_PULLUP);
	pinMode(Pin_ButtonY, INPUT_PULLUP);

	pinMode(Pin_ButtonLB, INPUT_PULLUP);
	pinMode(Pin_ButtonRB, INPUT_PULLUP);

	pinMode(Pin_ButtonBack, INPUT_PULLUP);
  pinMode(Pin_ButtonStart, INPUT_PULLUP);
  pinMode(Pin_ButtonLogo, INPUT_PULLUP);

  pinMode(Pin_ButtonL3, INPUT_PULLUP);
	pinMode(Pin_ButtonR3, INPUT_PULLUP);

	pinMode(Pin_dpadUp, INPUT_PULLUP);
	pinMode(Pin_dpadDown, INPUT_PULLUP);
	pinMode(Pin_dpadLeft, INPUT_PULLUP);
	pinMode(Pin_dpadRight, INPUT_PULLUP);
	
	XInput.setJoystickRange(0, ADC_Max);  // Set joystick range to the ADC
	XInput.setAutoSend(false);  // Wait for all controls before sending

	XInput.begin();
}

void loop() {

  // Leemos el estado de los pines

	boolean buttonA = !digitalRead(Pin_ButtonA);
	boolean buttonB = !digitalRead(Pin_ButtonB);
	boolean buttonX = !digitalRead(Pin_ButtonX);
	boolean buttonY = !digitalRead(Pin_ButtonY);
	boolean buttonLB = !digitalRead(Pin_ButtonLB);
	boolean buttonRB = !digitalRead(Pin_ButtonRB);
  boolean buttonL3 = !digitalRead(Pin_ButtonL3);
  boolean buttonR3 = !digitalRead(Pin_ButtonR3);
	boolean buttonBack  = !digitalRead(Pin_ButtonBack);
	boolean buttonStart = !digitalRead(Pin_ButtonStart);
  boolean triggerLeft  = !digitalRead(Pin_TriggerL);
  boolean triggerRight = !digitalRead(Pin_TriggerR);
  boolean dpadUp = !digitalRead(Pin_dpadUp); 
  boolean dpadDown = !digitalRead(Pin_dpadDown); 
  boolean dpadLeft = !digitalRead(Pin_dpadLeft); 
  boolean dpadRight =!digitalRead(Pin_dpadRight); 
  boolean buttonLogo = !digitalRead(Pin_ButtonLogo);

  int pinesstick[4] = {dpadLeft,dpadRight,dpadUp,dpadDown};

	// Pasamos el valor de los botones XInput
 
	XInput.setButton(BUTTON_A, buttonA);
	XInput.setButton(BUTTON_B, buttonB);
	XInput.setButton(BUTTON_X, buttonX);
	XInput.setButton(BUTTON_Y, buttonY);

	XInput.setButton(BUTTON_LB, buttonLB);
	XInput.setButton(BUTTON_RB, buttonRB);
  
  XInput.setButton(BUTTON_L3, buttonL3);
  XInput.setButton(BUTTON_R3, buttonR3);

	XInput.setButton(BUTTON_BACK, buttonBack);
	XInput.setButton(BUTTON_START, buttonStart);
  XInput.setButton(BUTTON_LOGO, buttonLogo);

	XInput.setButton(TRIGGER_LEFT, triggerLeft);
	XInput.setButton(TRIGGER_RIGHT, triggerRight);

// XInput.setDpad(dpadUp, dpadDown, dpadLeft, dpadRight);

// Stick como palanca analógica

  for (int index = 0; index < 4; index++)
  {
    int currentButtonState = pinesstick[index];
    if (currentButtonState != lastButtonState[index])
    {
      switch (index) {
        case 0: // Izquierda
      	if (currentButtonState)
          {
            XInput.setJoystickX(JOY_LEFT,0);
          } else 
            {
                XInput.setJoystickX(JOY_LEFT,512);
            }
        break;
        case 1: // Derecha
      	if (currentButtonState)
          {
            XInput.setJoystickX(JOY_LEFT,1023);
          } else 
            {
                XInput.setJoystickX(JOY_LEFT,512);
            }
        break;
        case 2: // Arriba
          if (currentButtonState)
          {
            XInput.setJoystickY(JOY_LEFT,1023);
          } else 
            {
                XInput.setJoystickY(JOY_LEFT,512);
            }
        break;
        case 3: // Abajo
      	if (currentButtonState)
          {
            XInput.setJoystickY(JOY_LEFT,0);
          } else 
            {
                XInput.setJoystickY(JOY_LEFT,512);
            }
        break;
      }
      lastButtonState[index] = currentButtonState;
    }
  }
  // Send control data to the computer
  XInput.send();
}
