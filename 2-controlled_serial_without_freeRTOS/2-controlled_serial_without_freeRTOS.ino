//----------------------------------------------------------
// To control the led and print on a serial monitor without FreeRTOS
//----------------------------------------------------------

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(10, INPUT);
  pinMode(13, OUTPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
  if(digitalRead(10) == HIGH){
    digitalWrite(13, LOW); // Turn off led
    while(digitalRead(10) == HIGH);
  }else digitalWrite(13, HIGH); // Turn on led
  Serial.println("PRINTLN");
  delay(1000);
}
