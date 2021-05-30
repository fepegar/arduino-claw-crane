/*

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
const int yLimitPin0 = 2;
const int yLimitPin1 = 3;


boolean xLimit0;
boolean xLimit1;
boolean yLimit0;
boolean yLimit1;

const int delayTime = 50;  // ms

int direction;


void setup() {
  Serial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);
  configMotorX();
  configMotorY();

  direction = TO_MOTORS;
}

boolean success;

void loop() {
  success = moveX(128, direction);
  if (!success) {
    if (direction == TO_MOTORS) {
      direction = FROM_MOTORS;
    } else if (direction == FROM_MOTORS) {
      direction = TO_MOTORS;
    }
  }
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
  pinMode(yLimitPin0, INPUT);
  pinMode(yLimitPin1, INPUT);

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

  // Read limit switches (pull-up resistors)
  xLimit0 = digitalRead(xLimitPin0) == LOW;
  xLimit1 = digitalRead(xLimitPin1) == LOW;
  delay(delayTime);

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

  // Read limit switches (pull-up resistors)
  yLimit0 = digitalRead(yLimitPin0) == LOW;
  yLimit1 = digitalRead(yLimitPin1) == LOW;
  delay(delayTime);

  if (direction == 0) {  // down
    if (yLimit0) {  // already at the limit
      Serial.println("yLimit0");
      digitalWrite(yDirectionPin0, LOW);
      digitalWrite(yDirectionPin1, LOW);
      return false;
    }

    // Set rotation direction
    Serial.println("Moving down");
    digitalWrite(yDirectionPin0, HIGH);
    digitalWrite(yDirectionPin1, LOW);

  } else if (direction == 1) {  // up
    if (yLimit1) {  // already at the limit
      Serial.println("yLimit1");
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

void stopAll() {
  digitalWrite(xDirectionPin0, LOW);
  digitalWrite(xDirectionPin1, LOW);

  digitalWrite(yDirectionPin0, LOW);
  digitalWrite(yDirectionPin1, LOW);
}
