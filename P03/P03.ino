void setup() {
  // initialize the serial communication:
  Serial.begin(9600);
   // initialize the pin 10 as the PWM output:
  pinMode(10, OUTPUT);
}

void loop() {
  // check if data has been sent from the computer:
  if (Serial.available()) {
    // read the Serial String:
    String x = Serial.readString();
    //Converting the variable of the input from String to Float:
    float y = x.toFloat();
    //Check if the format is ok:
    //Checking if the value of the input is ok:
    if(y>=0.0 && y<=5.0)
    {
      //Making the convertion:
      y=(y*255.0)/5.0;
      //PWM on the output (pin 10):
      analogWrite(10,y);
      //Print on Serial Monitor:
      Serial.print("Generando PWM de: ");
      Serial.println(y);
    }
  }
}
