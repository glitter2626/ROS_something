void setup()
{
  pinMode(A0, INPUT);
  Serial.begin(115200);
}

void loop()
{
int val=analogRead(A0); // read the sensor

Serial.println(10650.08 * pow(val,-0.935) - 10);  

delay(200);
}
