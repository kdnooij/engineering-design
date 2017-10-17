#include <Servo.h>

/**
 * LED LIGHT
 */
int ledPin = 13;

/**
 * DC MOTORS
 */
int PWM1 = 3;
int PWM2 = 5;
int PWM3 = 6;
int PWM4 = 11;

/**
 * SERVO MOTORS
 */
Servo servoX;
Servo servoY;

int posY = 90;
int posX = 90;

int servoPinX = A0;
int servoPinY = A1;

/**
 * STEPPER MOTOR
 */
 
int IN1 = 8;
int IN2 = 9;
int IN3 = 10;
int IN4 = 11; // TODO: Resolve duplicate

int Steps = 0;
boolean Direction = true;
unsigned long last_time;
unsigned long currentMillis ;
int steps_left=4095;
long time;


//
// ─── SETUP ────────────────────────────────────────
//

void setup() {
  
  // LED
  pinMode(ledPin,OUTPUT);
  led_On();

  // ETHERNET/WIFI
  Serial1.begin(115200);
  Serial1.println("> Initializing...");

  // DC
  servoX.attach(servoPinX);
  servoY.attach(servoPinY);
  
  // SERVO
  servoX.write(posX); // move to middle position
  servoY.write(posY);

  analogWrite(PWM1,0);
  analogWrite(PWM2,0);
  analogWrite(PWM3,0);
  analogWrite(PWM4,0);
  
  // STEPPER
  pinMode(IN1, OUTPUT); 
  pinMode(IN2, OUTPUT); 
  pinMode(IN3, OUTPUT); 
  pinMode(IN4, OUTPUT); 


  // Clear input buffer
  while (Serial1.available()){
     Serial1.read();
  }

  Serial1.println("> Initialization complete!");
  led_Off();
}

//
// ─── LOOP ─────────────────────────────────────────
//

void loop() {
  // put your main code here, to run repeatedly:
  if(Serial1.available() > 0)

  {
    char Command = Serial1.read();
    switch(Command)
    {
      // STEERING
      case '5':
        dc_Off();
        break;
      case '8':
        dc_Forward();
        break;
      case '2':
        dc_Reverse();
        break;
      case '4':
        dc_Left();
        break;
      case '6':
        dc_Right();
        break;

      // GIMBAL CONTROL
      case 'w':
        servo_Up();
        break;
      case 'z':
        servo_Down();
        break;
      case 'a':
        servo_Left();
        break;
      case 'd':
        servo_Right();
        break;
      case ' ':
        servo_Reset();
        break;
    }
  }
}

//
// ─── LED ──────────────────────────────────────────
//

void led_On() {
  digitalWrite(ledPin,HIGH);
}

void led_Off() {
  digitalWrite(ledPin,LOW);
}

//
// ─── DC ───────────────────────────────────────────
//

void dc_Off() {
  analogWrite(PWM1,0);
  analogWrite(PWM2,0);
  analogWrite(PWM3,0);
  analogWrite(PWM4,0);
}

void dc_Forward() {
  analogWrite(PWM1,255);
  analogWrite(PWM2,0);
  analogWrite(PWM3,255);
  analogWrite(PWM4,0);
}

void dc_Reverse() {
  analogWrite(PWM1,0);
  analogWrite(PWM2,255);
  analogWrite(PWM3,0);
  analogWrite(PWM4,255);
}

void dc_Left() {
  analogWrite(PWM1,255);
  analogWrite(PWM2,0);
  analogWrite(PWM3,0);
  analogWrite(PWM4,255);
}

void dc_Right() {
  analogWrite(PWM1,0);
  analogWrite(PWM2,255);
  analogWrite(PWM3,255);
  analogWrite(PWM4,0);
}

//
// ─── SERVO ────────────────────────────────────────
//

void servo_Up() {
  posY = posY + 5;
  servoY.write(posY);
}


void servo_Down() {
  posY = posY - 5;
  servoY.write(posY);
}

void servo_Left() {
  posX = posX + 5;
  servoX.write(posX);
}

void servo_Right() {
  posX = posX - 5;
  servoX.write(posX);
}

void servo_Reset() {
  posX = 90;
  servoX.write(posX);
  posY = 90;
  servoY.write(posY);
}

//
// ─── BOARDING ─────────────────────────────────────
//

void hatch_Open(){
  
}

void hatch_Close() {
  
}

