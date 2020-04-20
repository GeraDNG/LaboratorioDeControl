void setup() {
  // initialize the serial communication:
  Serial.begin(9600);
  // initialize the pin 10 as the PWM output:
  pinMode(10, OUTPUT);
  pinMode(6, OUTPUT);
}

// Variable declaration:
String aux, valor="xxxx", valorWHH="xx", valorWHL="nn", valorFrac="x", valorEnt="xx";
char F, x1, x2, x3, C[7];
int i=0, value=0, HUL=5, HLL=-5, G;
unsigned long T0, T1;
float y=0.0, e=0.0, r=0.0, u=0.0, u_ant=0.0, e_ant=0.0, T=0.1387, T_us, Kp_p=1.0, Kp_pi=1.0, Ki=1.0, Ent=0.0, Frac=0.0;
bool Y;


void loop() {
  // Contador:
  T0 = micros();
  // Bandera booleana para medir el tiempo con el osciloscopio:
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
      //Desplegar menú:
      Serial.print("El número de variables del string es de: ");
      Serial.print(aux.length()-1);
      Serial.println(". Debe ingresar un formato FxxxxC.");
      Serial.println("Donde F es el formato. Puede ser: R=RPM o V=Voltaje."); 
      Serial.println("xxxx es el valor. 0<RPM<3060. 0<Voltaje<5V.");
      Serial.println("C es el tipo de controlador deseado. O=ON/OFF, H=ON/OFF con Histéresis, P=P, I=PI, D=PID.");  
      Serial.println();
      Serial.println("WHxxnn -> Windows size for On/Off-H controller (xx = high & nn = low)");
      Serial.println("P±nn.n -> Kp gain for P controller");
      Serial.println("p±nn.n -> Kp gain for PI controller");
      Serial.println("i±nn.n -> ip gain for PI controller");
      Serial.println();
    }
    else
    {
      //Convertir String a Arreglo de Caracteres:
      aux.toCharArray(C,aux.length());

      //Validar el formato introducido:      
      if((C[0]=='V' || C[0]=='R' || C[0]=='W' || C[0]=='P' || C[0]=='p' || C[0]=='i') &&
         (C[1]=='9' || C[1]=='8' || C[1]=='7' || C[1]=='6' || C[1]=='5' || C[1]=='4' || C[1]=='3' || C[1]=='2' || C[1]=='1' || C[1]=='0' || C[1]=='+' || C[1]=='-' || C[1]=='H') && 
         (C[2]=='9' || C[2]=='8' || C[2]=='7' || C[2]=='6' || C[2]=='5' || C[2]=='4' || C[2]=='3' || C[2]=='2' || C[2]=='1' || C[2]=='0') && 
         (C[3]=='9' || C[3]=='8' || C[3]=='7' || C[3]=='6' || C[3]=='5' || C[3]=='4' || C[3]=='3' || C[3]=='2' || C[3]=='1' || C[3]=='0') && 
         (C[4]=='9' || C[4]=='8' || C[4]=='7' || C[4]=='6' || C[4]=='5' || C[4]=='4' || C[4]=='3' || C[4]=='2' || C[4]=='1' || C[4]=='0' || C[4]=='.') && 
         (C[5]=='9' || C[5]=='8' || C[5]=='7' || C[5]=='6' || C[5]=='5' || C[5]=='4' || C[5]=='3' || C[5]=='2' || C[5]=='1' || C[5]=='0' || C[5]=='O' || C[5]=='H' || C[5]=='P' || C[5]=='I' || C[5]=='D'))
      {
       
        //Asignar el valor dado por el usuario a la variable "valor":
        for(i=0;i<4;i++)
        {
          valor.setCharAt(i,C[i+1]);
        }
        //Convertir valor a Int:
        value = valor.toInt();
        //Asignar el valor a R, convirtiendo a las unidades correctas:
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
        switch(C[0])
        {
          case 'W':
            //Asignar el valor dado por el usuario a la variable "valorWH":
            for(i=0;i<2;i++)
            {
              valorWHH.setCharAt(i,C[i+2]);
              valorWHL.setCharAt(i,C[i+4]);
            }
            //Convertir valorWH a Int:
            HUL = ((valorWHH.toInt())*(r/100));
            HLL = ((valorWHL.toInt())*(r/100));
            Serial.println("Se cambió el tamaño de la ventana.");
            break;
          case 'P':
            if(C[1]=='+')
            {
              for(i=0;i<2;i++)
              {
                valorEnt.setCharAt(i,C[i+3]);
              }
              valorFrac.setCharAt(0,C[5]);
              Ent = valorEnt.toInt();
              Frac = valorFrac.toInt();
              Kp_p = Ent+(Frac*0.1);
            }
            else if(C[1]=='-')
            {
              for(i=0;i<2;i++)
              {
                valorEnt.setCharAt(i,C[i+3]);
              }
              valorFrac.setCharAt(0,C[5]);
              Ent = valorEnt.toInt();
              Frac = valorFrac.toInt();
              Kp_p = -(Ent+(Frac*0.1));
            }
            Serial.println("Valor de Kp para controlador P cambiado a: ");
            Serial.println(Kp_p);
            Serial.println();
            break;
          case 'p':
            if(C[1]=='+')
            {
              for(i=0;i<2;i++)
              {
                valorEnt.setCharAt(i,C[i+3]);
              }
              valorFrac.setCharAt(0,C[5]);
              Ent = valorEnt.toInt();
              Frac = valorFrac.toInt();
              Kp_pi = Ent+(Frac*0.1);
            }
            else if(C[1]=='-')
            {
              for(i=0;i<2;i++)
              {
                valorEnt.setCharAt(i,C[i+3]);
              }
              valorFrac.setCharAt(0,C[5]);
              Ent = valorEnt.toInt();
              Frac = valorFrac.toInt();
              Kp_pi = -(Ent+(Frac*0.1));
            }
            Serial.println("Valor de Kp para controlador PI cambiado a: ");
            Serial.println(Kp_pi);
            Serial.println();
            break;
          case 'i':
            if(C[1]=='+')
            {
              for(i=0;i<2;i++)
              {
                valorEnt.setCharAt(i,C[i+3]);
              }
              valorFrac.setCharAt(0,C[5]);
              Ent = valorEnt.toInt();
              Frac = valorFrac.toInt();
              Ki = Ent+(Frac*0.1);
            }
            else if(C[1]=='-')
            {
              for(i=0;i<2;i++)
              {
                valorEnt.setCharAt(i,C[i+3]);
              }
              valorFrac.setCharAt(0,C[5]);
              Ent = valorEnt.toInt();
              Frac = valorFrac.toInt();
              Ki = -(Ent+(Frac*0.1));
            }
            Serial.println("Valor de Ki para controlador PI cambiado a: ");
            Serial.println(Ki);
            Serial.println();
            break;
          default:
            break;
        }
      }
      else
      {
        Serial.println("Error de formato");
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
    u = Kp_p * e;
    if (u > 255.0)
      u = 255.0;
    else if (u < 0.0)
      u = 0.0;
  }
  //Controlador PI:
  else if (G == 4)
  {
    u = u_ant + e*(Kp_pi+(Ki*(T/2))) + e_ant*(-Kp_pi+Ki*(T/2));
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
