#include <XInput.h>


#define xPD3 0b00001000 //Digital Pin 1  - PRO Micro - TX,  INT3
#define xPD2 0b00000100 //Digital Pin 0  - PRO Micro - RX,  INT2
#define xPD1 0b00000010 //Digital Pin 2  - PRO Micro - SDA, INT0
#define xPD0 0b00000001 //Digital Pin 3  - PRO Micro - SCL, INT1
#define xPD_10 (xPD1 | xPD0)
#define xPD_32 (xPD3 | xPD2)
#define xPD4 0b00010000 //Digital Pin 4  - PRO Micro
#define xPC6 0b01000000 //Digital Pin 5  - PRO Micro
#define xPD7 0b10000000 //Digital Pin 6  - PRO Micro
#define xPE6 0b01000000 //Digital Pin 7  - PRO Micro
#define xPB4 0b00010000 //Digital Pin 8  - PRO Micro
#define xPB5 0b00100000 //Digital Pin 9  - PRO Micro
#define xPB6 0b01000000 //Digital Pin 10 - PRO Micro
#define xPB3 0b00001000 //Digital Pin 14 - PRO Micro
#define xPB1 0b00000010 //Digital Pin 15 - PRO Micro
#define xPB2 0b00000100 //Digital Pin 16 - PRO Micro
#define xPF7 0b10000000 //Digital Pin A0 - PRO Micro
#define xPF6 0b01000000 //Digital Pin A1 - PRO Micro
#define xPF5 0b00100000 //Digital Pin A2 - PRO Micro
#define xPF4 0b00010000 //Digital Pin A3 - PRO Micro

// Setup

const int ADC_Max = 1023; //Valor máximo del stick analógico

int lastButtonState[4] = {0,0,0,0};

int stickType = 1; // Cambiar si queremos cambiar el comportamiento de nuestro stick (0 = DPad, 1 = Palanca Análogica Izquierda, 2 = Palanca Análogica Derecha)


void setup() {


// Configura los botones como entradas, utilizando resistencias pull-up internas

// Usa resistencias de entrada internas para todos los pines que estamos utilizando: resistencia pull-up, cuando se presiona el botón (se conecta a tierra), la entrada en el pin se lleva a LOW.


  PORTD = 0b10011111; //Pines D0 (PD3), D1 (PD2), D2 (PD1),D3 (PD0),D4 (PD4), D6 (PD7)
  PORTB = 0b01111110; //Pines D15 (PB1), D16 (PB2), D14 (PB3), D8 (PB4), D9 (PB5), D10, (PB6)
  PORTC = 0b01000000; //Pines D5 (PC6)
  PORTE = 0b01000000; //Pines D7 (PE6)
  PORTF = 0b11110000; //Pines A0 (PF7) & A1 (PF6) & A2 (PF5) & A3 (PF4)


	XInput.setJoystickRange(0, ADC_Max);  // Set joystick range to the ADC
	XInput.setAutoSend(false);  // Wait for all controls before sending

	XInput.begin();
}

void loop() {

  //Comprueba el estado de cada pin
  
  boolean buttonA = (PIND & xPD1) >> 1; //Pin 2    
  boolean buttonB = (PIND & xPD0) >> 0; //Pin 3
  boolean buttonX = (PIND & xPD7) >> 7; //Pin 6 
  boolean buttonY = (PINE & xPE6) >> 6; //Pin 7

  boolean buttonLB = (PIND & xPD4) >> 4; //Pin 4
  boolean buttonRB = (PINC & xPC6) >> 6; //Pin 5

  boolean buttonBack  = (PINF & xPF7) >> 7; //Pin A0
  boolean buttonStart = (PINF & xPF6) >> 6; //Pin A1
  
  boolean buttonLogo = (PIND & xPD3) >> 3; //Pin 0

  boolean buttonTriggerL = (PINB & xPB4) >> 4; //Pin 8
  boolean buttonTriggerR = (PINB & xPB5) >> 5; //Pin 9

  boolean buttonL3 = (PINF & xPF4) >> 4; //Pin A3
  boolean buttonR3 = (PINF & xPF5) >> 5; //Pin A2
  
  boolean dpadUp = (PINB & xPB1) >> 1; //Pin 15
  boolean dpadDown = (PINB & xPB2) >> 2; //Pin 16
  boolean dpadLeft = (PINB & xPB3) >> 3; //Pin 14 
  boolean dpadRight =(PINB & xPB6) >> 6; //Pin 10


  //Guardamos los valores de lectura de los pines asignados al D-Pad en una matriz
  
  int pinesstick[4] = {!dpadLeft,!dpadRight,!dpadUp,!dpadDown};

 
  //Pasamos al gamepad los valores leídos en los pines
        XInput.setButton(BUTTON_A, !buttonA);
        XInput.setButton(BUTTON_B, !buttonB);
        XInput.setButton(BUTTON_X, !buttonX);
        XInput.setButton(BUTTON_Y, !buttonY);
        XInput.setButton(BUTTON_LB, !buttonLB);
        XInput.setButton(BUTTON_RB, !buttonRB);
        XInput.setButton(BUTTON_L3, !buttonL3);
        XInput.setButton(BUTTON_R3, !buttonR3);
        XInput.setButton(TRIGGER_LEFT, !buttonTriggerL);
        XInput.setButton(TRIGGER_RIGHT, !buttonTriggerR);
        XInput.setButton(BUTTON_BACK, !buttonBack);
        XInput.setButton(BUTTON_START, !buttonStart);
        XInput.setButton(BUTTON_LOGO, !buttonLogo);
        

   if (stickType == 0)
        XInput.setDpad(!dpadUp, !dpadDown, !dpadLeft, !dpadRight);
    
    
  if (stickType == 1)
  {  
      // Stick como palanca analógica
    for (int index = 0; index < 4; index++)
    {
      int currentButtonState = pinesstick[index];  
      
     if (currentButtonState != lastButtonState[index])
     {
        switch (index) {
          case 0:
            if (currentButtonState)
                  {
                    XInput.setJoystickX(JOY_LEFT,0);
                  } else 
                    {
                        XInput.setJoystickX(JOY_LEFT,511);
                    }
           break;
           case 1:
            if (currentButtonState)
                  {
                    XInput.setJoystickX(JOY_LEFT,1023);
                  } else 
                    {
                        XInput.setJoystickX(JOY_LEFT,511);
                    }
           break;
           case 2:
            if (currentButtonState)
                  {
                    XInput.setJoystickY(JOY_LEFT,1023);
                  } else 
                    {
                        XInput.setJoystickY(JOY_LEFT,511);
                    }
           break;
           case 3:
            if (currentButtonState)
                  {
                    XInput.setJoystickY(JOY_LEFT,0);
                  } else 
                    {
                        XInput.setJoystickY(JOY_LEFT,511);
                    }
           break;
        }
        lastButtonState[index] = currentButtonState;
      }
    }
  }
  if (stickType == 2)
  {  
      // Stick derecho como palanca analógica
    for (int index = 0; index < 4; index++)
    {
      int currentButtonState = pinesstick[index];  
      
     if (currentButtonState != lastButtonState[index])
     {
        switch (index) {
          case 0:
            if (currentButtonState)
                  {
                    XInput.setJoystickX(JOY_RIGHT,0);
                  } else 
                    {
                        XInput.setJoystickX(JOY_RIGHT,511);
                    }
           break;
           case 1:
            if (currentButtonState)
                  {
                    XInput.setJoystickX(JOY_RIGHT,1023);
                  } else 
                    {
                        XInput.setJoystickX(JOY_RIGHT,511);
                    }
           break;
           case 2:
            if (currentButtonState)
                  {
                    XInput.setJoystickY(JOY_RIGHT,1023);
                  } else 
                    {
                        XInput.setJoystickY(JOY_RIGHT,511);
                    }
           break;
           case 3:
            if (currentButtonState)
                  {
                    XInput.setJoystickY(JOY_RIGHT,0);
                  } else 
                    {
                        XInput.setJoystickY(JOY_RIGHT,511);
                    }
           break;
        }
        lastButtonState[index] = currentButtonState;
      }
    }
  }
  // Send control data to the computer
  XInput.send();
}
