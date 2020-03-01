
/*
 * Wheels 1.0.1
 * 
 * Written by Nikolai Patrick
 * ##########################
 * 
 * A sketch for an automated vehicle driving two motors, 
 * headlights, indicator lights and tail lights automated with
 * an LDR sensor. It also includes support for an analog ultrasonic
 * distance sensor and a rear one in the future. The vehicle detects
 * when it gets close to a wall then backs out and turns around until
 * it hits another wall. The motors are driven by an L239D and will
 * be able to track lines in the future with a GY - 31 colour module.
 * 
 * You may use, modify, and re-distribute this code under the terms
 * of the GNU GPL 3.0 General Public Licence
 * https://www.gnu.org/licenses/gpl-3.0.html
 * 
 */
int DevisedLeft;
int DevisedForward;
int DevisedBackward;
int DevisedRight;
int DistanceValue;
int DiceRoll;
int LightValue;
int LeftHeadLight = 4;
int RightHeadLight = 13;
int LeftBlinker = 11;
int RightBlinker = 12;
int LeftTailLight = 8;
int RightTailLight = 7;
void DisableAll() { //Turn off all motors
  digitalWrite(10, LOW);//D10- right forward
  digitalWrite(9, LOW); //D9 - right backward
  digitalWrite(6, LOW); //D6 - left backward
  digitalWrite(5, LOW); //D5 - left forward
}
void MoveForward(int ForwardLength, int ForwardSpeed) { //Move the vehicle forwards (seconds, speed)
  analogWrite(5, ForwardSpeed);
  analogWrite(10, ForwardSpeed);
  DevisedForward = ForwardLength;
  delay(DevisedForward);
  analogWrite(5, 0);
  analogWrite(10, 0);
}
void MoveBackward(int BackwardLength, int BackwardSpeed) { //Move the vehicle backwards (seconds, speed)
  analogWrite(6, BackwardSpeed);
  analogWrite(9, BackwardSpeed);
  DevisedBackward = BackwardLength * 1000;
  delay(DevisedBackward);
  analogWrite(6, 0);
  analogWrite(9, 0);
}
void MoveLeft(int LeftLength, int LeftSpeed) { //Turn the vehicle left (seconds, speed)
  analogWrite(6, LeftSpeed);
  analogWrite(10, LeftSpeed);
  DevisedLeft = LeftLength * 1000;
  delay(DevisedLeft);
  analogWrite(6, 0);
  analogWrite(10, 0);
}
void MoveRight(int RightLength, int RightSpeed) { //Turn the vehicle right (seconds, speed)
  analogWrite(5, RightSpeed);
  analogWrite(9, RightSpeed);
  DevisedRight = RightLength * 1000;
  delay(DevisedRight);
  analogWrite(5, 0);
  analogWrite(9, 0);
}
void MoveLeftOrRight(int LeftOrRightSpeed) {
  DiceRoll = random(1, 2);
  if (DiceRoll==1) {
    MoveLeft(LeftOrRightSpeed, 255);
  }
  if (DiceRoll==2) {
    MoveRight(LeftOrRightSpeed, 255);
  }
}
void LightsOff() {
  analogWrite(LeftHeadLight, 0);
  analogWrite(RightHeadLight, 0);
  analogWrite(LeftBlinker, 0);
  analogWrite(RightBlinker, 0);
  analogWrite(LeftTailLight, 0);
  analogWrite(RightTailLight, 0);
}
void LightsOn(int allbrightness) {
  analogWrite(LeftHeadLight, allbrightness);
  analogWrite(RightHeadLight, allbrightness);
  analogWrite(LeftBlinker, allbrightness);
  analogWrite(RightBlinker, allbrightness);
  analogWrite(LeftTailLight, allbrightness);
  analogWrite(RightTailLight, allbrightness);
}
void HeadLightsOn(int headbrightness) {
  analogWrite(LeftHeadLight, headbrightness);
  analogWrite(RightHeadLight, headbrightness)
}
void HeadLightsOff() {
  analogWrite(LeftHeadLight, 0);
  analogWrite(RightHeadLight, 0)
}
void TailLightsOn(int tailbrightness) {
  analogWrite(LeftTailLight, tailbrightness);
  analogWrite(RightTailLight, tailbrightness);
}
void TailLightsOff() {
  analogWrite(LeftTailLight, 0);
  analogWrite(RightTailLight, 0);
}
void HazardsOn(int hazardbrightness, int hazardtime) {
  for(int hazardcount; hazardcount < hazardtime; hazardcount++) {
  analogWrite(LeftBlinker, allbrightness);
  analogWrite(RightBlinker, allbrightness);
  delay(500);
  analogWrite(LeftBlinker, 0);
  analogWrite(RightBlinker, 0);
  delay(500);
  }
}
void setup() {
  Serial.begin(9600);
  LightsOn(255);
}

void loop() {
  delay(1000);
  LightValue = analogRead(A1);
  DistanceValue = analogRead(A0);
  Serial.println(LightValue);
  if (DistanceValue > 590) {
   MoveBackward(2, 255);
   MoveLeftOrRight(2);
  }
  MoveForward(10, 255);
}
