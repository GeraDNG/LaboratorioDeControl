
void setup() {
  // initialize the serial communication:
  Serial.begin(9600);
   // initialize the pin 10 as the PWM output:
  pinMode(10, OUTPUT);
  pinMode(3, INPUT);
}

void loop() {
  // check if data has been sent from the computer:
  if (Serial.available()) {
    // read the Serial String:
    String x = Serial.readString();
    //Check if the format is ok:
    if(x>="0" && x<="3060.1")
    {
      //Converting the variable of the input from String to Float:
      float x2=x.toFloat();
      //Checking if the value of the input is ok:
      if(x2>=0.0 && x2<=3060.0)
      {
        int y=analogRead(3);
        float y2 = y*255.0/1023.0;
        Serial.print("Y(t) de: ");
        Serial.println(y2);
        
        float e=x2-y2;
        Serial.print("Error de: ");
        Serial.println(e);
        
        //Making the convertion:
        x2=(x2*256.0)/3260.0;
        //PWM on the output (pin 10):
        analogWrite(10,x2);
        //Print on Serial Monitor:
        Serial.print("Generando PWM de: ");
        Serial.println(x2);
      }
      else
        Serial.println("Rango incorrecto");
    }
    else
      Serial.println("Error de formato");
  }
}
