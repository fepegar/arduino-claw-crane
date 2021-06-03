/*

- Joystick VRx, VRy and SW to A0, A1, A2.

Arduino:
- Pin 2 to pull-up resistor 10k to orange (yLimitUp)
- Pin 3 to pull-up resistor 10k to purple (yLimitDown)
- Pin 4 to pull-up resistor 10k to white (xLimit1)
- Pin 5 to pull-up resistor 10k to red (xLimit0)
- Pin 6 to L293D pin 2 (1A)
- Pin 8 to L293D pin 7 (2A)
- Pin 9 to L293D pin 15 (4A)
- Pin 10 to L293D pin 1 (1,2EN)
- Pin 11 to L293D pin 9 (3,4EN)
- Pin 12 to L293D pin 10 (3A)

L293D:
- Pins 4, 5, 12 and 13 to GND (important!)
- Vcc1 to Arduino 5 V
- Vcc2 to power supply 12 V
- Pin 3 (1Y) to crane (orange-white)
- Pin 6 (2Y) to crane (green)
- Pin 14 (4Y) to crane (orange-black)
- Pin 11 (3Y) to crane (pink)

*/

#define TO_MOTORS 0
#define FROM_MOTORS 1
#define DOWN 0
#define UP 1

const int xEnablePin = 10;
const int xDirectionPin0 = 6;
const int xDirectionPin1 = 8;
const int xLimitPin0 = 5;
const int xLimitPin1 = 4;

const int yEnablePin = 11;
const int yDirectionPin0 = 9;
const int yDirectionPin1 = 12;
const int yLimitPinDown = 3;
const int yLimitPinUp = 2;

const int delayTime = 50;  // ms

boolean xLimit0;
boolean xLimit1;
boolean yLimitDown;
boolean yLimitUp;

int direction;


void setup() {
  Serial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);
  configMotorX();
  configMotorY();
  configJoystick();

  direction = TO_MOTORS;
}

boolean success;

void loop() {
  readLimitSwitches();

   // Move for half a second
  /*success = moveX(255, direction);
  delay(5000);
  stopAll();
  Serial.println("Done.");
  while (true) {}
  */

  // // Move until the end
  //success = moveX(255, FROM_MOTORS);
  //if (!success) {
  //  stopAll();
  //  Serial.println("Done.");
  //  while (true) {}
  //

  // Bounce
  /*success = moveX(128, direction);
  if (!success) {
    if (direction == TO_MOTORS) {
      direction = FROM_MOTORS;
    } else if (direction == FROM_MOTORS) {
      direction = TO_MOTORS;
    }
  }*/

  moveJoystick();
}


void readLimitSwitches() {
  // Read limit switches (pull-up resistors)
  xLimit0 = digitalRead(xLimitPin0) == LOW;
  xLimit1 = digitalRead(xLimitPin1) == LOW;
  yLimitDown = digitalRead(yLimitPinDown) == LOW;
  yLimitUp   = digitalRead(yLimitPinUp)   == LOW;

  ///////////////////////
  if (yLimitUp) {
    digitalWrite(LED_BUILTIN, HIGH);
  } else {
    digitalWrite(LED_BUILTIN, LOW);
  }
  yLimitDown = false;
  ///////////////////////////////////////
  delay(delayTime);
}


void moveJoystick() {
  const int midSignal = 1024 / 2;

  int signalX = analogRead(A0);
  if (signalX > 400 && signalX < 600) {
    stopX();
  } else {
    int directionX;
    if (signalX > midSignal) {
      directionX = FROM_MOTORS;
    } else if (signalX < midSignal) {
      directionX = TO_MOTORS;
    }
    moveX(128, directionX);
  }

  int signalY = analogRead(A1);
  if (signalY > 400 && signalY < 600) {
    stopY();
  } else {
    int directionY;
    if (signalY > midSignal) {
      directionY = DOWN;
    } else if (signalX < midSignal) {
      directionY = UP;
    }
    moveY(255, directionY);
  }
}


void configJoystick() {
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
}


void configMotorX() {
  // Config limit switches
  pinMode(xLimitPin0, INPUT);
  pinMode(xLimitPin1, INPUT);

  pinMode(xEnablePin, OUTPUT);
  pinMode(xDirectionPin0, OUTPUT);
  pinMode(xDirectionPin1, OUTPUT);
}


void configMotorY() {
  // Config limit switches
  pinMode(yLimitPinDown, INPUT);
  pinMode(yLimitPinUp, INPUT);

  pinMode(yEnablePin, OUTPUT);
  pinMode(yDirectionPin0, OUTPUT);
  pinMode(yDirectionPin1, OUTPUT);
}


boolean moveX(int speed, int direction) {
  /*
  * Direction 0 means "towards the motors"
  * Direction 1 means "away from the motors"
  * Speed goes from 0 to (2**8)-1 = 255
  * Returns false if the limit switch for that direction is enabled
  * and true otherwise
  */

  if (direction == 0) {  // towards the motors
    if (xLimit0) {  // already at the limit
      Serial.println("xLimit0");
      digitalWrite(xDirectionPin0, LOW);
      digitalWrite(xDirectionPin1, LOW);
      return false;
    }

    // Set rotation direction
    Serial.println("Moving towards the motors");
    digitalWrite(xDirectionPin0, HIGH);
    digitalWrite(xDirectionPin1, LOW);

  } else if (direction == 1) {  // away from the motors
    if (xLimit1) {  // already at the limit
      Serial.println("xLimit1");
      digitalWrite(xDirectionPin0, LOW);
      digitalWrite(xDirectionPin1, LOW);
      return false;
    }

    // Set rotation direction
    Serial.println("Moving from the motors");
    digitalWrite(xDirectionPin0, LOW);
    digitalWrite(xDirectionPin1, HIGH);
  }
  // Set PWM
  analogWrite(xEnablePin, speed);
  return true;
}


boolean moveY(int speed, int direction) {
  /*
  * Direction 0 means "down"
  * Direction 1 means "up"
  * Speed goes from 0 to (2**8)-1 = 255
  * Returns false if the limit switch for that direction is enabled
  * and true otherwise
  */
  if (direction == 0) {  // down
    if (yLimitDown) {  // already at the limit
      Serial.println("yLimitDown");
      digitalWrite(yDirectionPin0, LOW);
      digitalWrite(yDirectionPin1, LOW);
      return false;
    }

    // Set rotation direction
    Serial.println("Moving down");
    digitalWrite(yDirectionPin0, HIGH);
    digitalWrite(yDirectionPin1, LOW);

  } else if (direction == 1) {  // up
    if (yLimitUp) {  // already at the limit
      Serial.println("yLimitUp");
      digitalWrite(yDirectionPin0, LOW);
      digitalWrite(yDirectionPin1, LOW);
      return false;
    }

    // Set rotation direction
    Serial.println("Moving up");
    digitalWrite(yDirectionPin0, LOW);
    digitalWrite(yDirectionPin1, HIGH);
  }
  // Set PWM
  analogWrite(yEnablePin, speed);
  return true;
}


void stopX() {
  digitalWrite(xDirectionPin0, LOW);
  digitalWrite(xDirectionPin1, LOW);
}


void stopY() {
  digitalWrite(yDirectionPin0, LOW);
  digitalWrite(yDirectionPin1, LOW);
}


void stopAll() {
  stopX();
  stopY();
}
