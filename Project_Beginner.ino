int led = 13;
void setup() {
  // put your setup code here, to run once:
  serial.begin(9600);
  pinMode(led, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(led, HIGH);
  serial.println("LED is ON");
  delay(1000);
  digitalWrite(led, LOW);
  serial.println("LED is OFF");
  delay(1000);
}