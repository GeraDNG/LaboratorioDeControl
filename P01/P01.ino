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
    //Check if the format is ok:
    if(x>="0" && x<="5.1")
    {
      //Converting the variable of the input from String to Float:
      float y=x.toFloat();
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
      else
        Serial.println("Rango incorrecto");
    }
    else
      Serial.println("Error de formato");
  }
}
