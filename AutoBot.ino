/* BlueTooth car design Version 1.0
    ATAL Tinkering Lab
*/

#define Right_1  2
#define Right_2  3
#define Left_1   4
#define Left_2   5
#define En_Right 9
#define En_Left  10
char data;
#define In_Right 6
#define In_Left  7
#define Flash    12
#define Buzzer   8
int FlashState = LOW;
int LongFrontState = LOW;
int LongBackState  = LOW;
int En_RightState  = LOW;
int En_LeftState   = LOW;

void setup() {
  pinMode(Right_1,  OUTPUT);
  pinMode(Right_2,  OUTPUT);
  pinMode(Left_1,   OUTPUT);
  pinMode(Left_2,   OUTPUT);
  pinMode(En_Right, OUTPUT);
  pinMode(En_Left,  OUTPUT);
  pinMode(In_Right, OUTPUT);
  pinMode(In_Left,  OUTPUT);
  pinMode(Flash,    OUTPUT);
  pinMode(Buzzer,   OUTPUT);
  //analogWrite(En_Right, 0);
  //analogWrite(En_Left,  0);
  Serial.begin(9600);
//-------------------------------StartUp Signal-----------------------
 delay(1000);
  for (int i = 0; i < 4; i++) {
    digitalWrite(Buzzer, HIGH);
    delay(50);
    digitalWrite(Buzzer, LOW);
    delay(50);
  }
//--------------------------------------------------------------------
}
void loop() {
  if (Serial.available() > 0) {
    data = Serial.read();
    //Serial.println(Serial.read());
    FB();
    RL();
    flash();
    Start();
    LongFront();
  }
}
void Start() {
  if (data == 83) {
    En_RightState = !En_RightState;
    En_LeftState  = !En_LeftState;
    digitalWrite(En_Right, En_RightState);
    digitalWrite(En_Left,  En_LeftState);

    for (int i = 0; i < 3 ; i++) {
      digitalWrite(In_Right, HIGH);
      digitalWrite(In_Left,  HIGH);
      digitalWrite(Buzzer,   HIGH);
      delay(100);
      digitalWrite(In_Right, LOW);
      digitalWrite(In_Left,  LOW);
      digitalWrite(Buzzer,   LOW);
      delay(100);
    }
  }
}
void Stop() {
  digitalWrite(Right_1, LOW);
  digitalWrite(Right_2, LOW);
  digitalWrite(Left_1,  LOW);
  digitalWrite(Left_2,  LOW);
}
void FB() {

  if (data == 65) {
    digitalWrite(Right_1, HIGH);
    digitalWrite(Right_2, LOW);
    digitalWrite(Left_1, HIGH);
    digitalWrite(Left_2, LOW);
    delay(1500);
    Stop();
  }
  else if (data == 66) {
    digitalWrite(Right_1, LOW);
    digitalWrite(Right_2, HIGH);
    digitalWrite(Left_1, LOW);
    digitalWrite(Left_2, HIGH);
    digitalWrite(In_Right, HIGH);
    digitalWrite(In_Left,  HIGH);
    delay(1500);
    digitalWrite(In_Right, LOW);
    digitalWrite(In_Left,  LOW);
    Stop();
  }

}
void RL() {
  if (data  == 67) {           //Left
    digitalWrite(Right_1, LOW);
    digitalWrite(Right_2, HIGH);
    digitalWrite(Left_1,  HIGH);
    digitalWrite(Left_2,  LOW);
    digitalWrite(In_Right, HIGH);
    delay(500);
    digitalWrite(In_Right, LOW);
    Stop();
  }
  else if (data == 68) {       //Right
    digitalWrite(Right_1, HIGH);
    digitalWrite(Right_2, LOW);
    digitalWrite(Left_1, LOW);
    digitalWrite(Left_2, HIGH);
    digitalWrite(In_Left, HIGH);
    delay(500);
    digitalWrite(In_Left, LOW);
    Stop();
  }
}


void flash() {

  if (data == 70) {
    FlashState = !FlashState;
    digitalWrite(Flash, FlashState);
  }
}

void LongFront() {
  if (data == 120) {
    LongFrontState = !LongFrontState;
    digitalWrite(Right_1, LongFrontState);
    digitalWrite(Left_1,  LongFrontState);
    digitalWrite(Right_2, !LongFrontState);
    digitalWrite(Left_2 , !LongFrontState);
  }
  else if (data == 88) {
    Stop();
  }
}

