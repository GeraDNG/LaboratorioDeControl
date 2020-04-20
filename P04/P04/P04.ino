void setup() {
  // initialize the serial communication:
  Serial.begin(9600);
  // initialize the pin 10 as the PWM output:
  pinMode(10, OUTPUT);
  pinMode(6, OUTPUT);
}

// Variable declaration:
String aux, valor="xxxx";
char F,x1,x2,x3,C[7];
int i=0, value=0, HUL=5.1, HLL=-5.1, G;
unsigned long T0, T1;
float y=0.0, e=0.0, r=0.0, u=0.0, u_ant=0.0, e_ant=0.0, T=0.1387, T_us, Kp=9.0, Ki=0.3;
bool Y;

void loop() {
  //Contador:
  T0 = micros();
  Y = !Y;
  if(Y)
    analogWrite(6,255);
  else if(Y!=true)
    analogWrite(6,0);
  
  // check if data has been sent from the computer:
  if (Serial.available()) 
  {
    aux = Serial.readStringUntil('\0');     // Read the "FxxxxC"; F=Format, xxxx=value and C=Controller
    //Validar cantidad de datos ingresados:
    if((aux.length()-1) != 6)
    {
      Serial.print("El número de variables del string es de: ");
      Serial.print(aux.length()-1);
      Serial.println(". Debe ingresar un formato FxxxxC.");
      Serial.println("Donde F es el formato. Puede ser: R=RPM o V=Voltaje."); 
      Serial.println("xxxx es el valor. 0<RPM<3060. 0<Voltaje<5V.");
      Serial.println("C es el tipo de controlador deseado. O=ON/OFF, H=ON/OFF con Histéresis, P=P, I=PI, D=PID.");  
      Serial.println();
    }
    else
    {
      //Convertir String a Arreglo de Caracteres:
      aux.toCharArray(C,aux.length());

      //Validar el formato introducido:
      if((C[0]>'V') || (C[0]<'V') && (C[0]<'R') || (C[0]<'R'))  
        Serial.println("Error de formato para F");
      if((C[1]>'9' || C[1]<'0') && (C[2]>'9' || C[2]<'0') && (C[3]>'9' || C[3]<'0') && (C[4]>'9' || C[4]<'0'))
        Serial.println("Error en formato para xxxx");
      if((C[5]>'O' || C[5]<'O') && (C[5]>'H' || C[5]<'H') && (C[5]>'P' || C[5]<'P') && (C[5]>'I' || C[5]<'I') && (C[5]>'D' || C[5]<'D'))
        Serial.println("Error de formato para C");
      else
      {
        //Asignar el valor dado por el usuario a la variable "valor":
        for(i=0;i<4;i++)
        {
          valor.setCharAt(i,C[i+1]);
        }
        //Convertir valor a Int:
        value = valor.toInt();
        //Asignar el valor a R, convirtiendo a las unidades correctas:
        //r = map(value,0,3060,0,255);
        r = (int)value * (float)(255.0/3060.0);
        //Selección de tipo de controlador:
        switch(C[5])
        {
          case 'O':
            Serial.println("Se seleccionó el controlador ON/OFF.");
            G = 1;
            break;
          case 'H':
            Serial.println("Se seleccionó el controlador ON/OFF con Histéresis.");
            G = 2;
            break;
          case 'P':
            Serial.println("Se seleccionó el controlador P.");
            G = 3;
            break;
          case 'I':
            Serial.println("Se seleccionó el controlador PI.");
            G = 4;
            break;
          case 'D':
            Serial.println("Se seleccionó el controlador PID.");
            G = 5;
            break;    
          default:
            //Serial.println("Formato correcto.");
            break;
        }
      }
    }
  }
  
  //Lectura de Y:
  y = analogRead(A0);
  y = y*(float)(255.0/1023.0);
  
  //Calcular error:
  e = r - y;
  
  //Controlador ON/OFF:
  if (G == 1)
  {
    if (e > 0.0)
      u = 255.0;
    if (e < 0.0)
      u = 0.0;
  }
  //Controlador ON/OFF con histéresis:
  else if (G == 2)
  {
    if (e > HUL)
      u = 255.0;
    if (e < HLL)
      u = 0.0;
  }
  //Controlador P:
  else if (G == 3)
  {
    u = Kp * e;
    if (u > 255.0)
      u = 255.0;
    else if (u < 0.0)
      u = 0.0;
  }
  //Controlador PI:
  else if (G == 4)
  {
    u = u_ant + e*(Kp+(Ki*(T/2))) + e_ant*(-Kp+Ki*(T/2));
    u_ant = u;
    e_ant = e;
  }
  
  //Escribir el valor de U:
  analogWrite(10, u);

  //Cierre de contador:
  T1 = micros();

  T_us = (4*T/25)*1000000;

  //Delay:
  delayMicroseconds(T_us-(T1-T0));

}
