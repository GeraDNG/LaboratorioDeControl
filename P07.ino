void setup() {
  Serial.begin(9600);
}

char convertir(int numero){
  switch(numero)
  {
    case 1:
      return '1'; 
      break;
    case 2:
      return '2';
      break;
    case 3:
      return '3';
      break;
    case 4:
      return '4';
      break;
    case 5:
      return '5';
      break;
    case 6:
      return '6';
      break;
    case 7:
      return '7';
      break;
    case 8:
      return '8';
      break;
    case 9:
      return '9';
      break;
    case 0:
      return '0';
      break;
  }
}

void loop() {
  char aux[8];
  int i=0, j=0;
  for (j=0;j<100;j++)
  {
    for (i=0;i<8;i++)
    {
      if(i == 0)
        aux[i] = '#';
      else if (i == 7)
        aux[i] = '&';
      else if (i == 1)
        aux[i] = '0';
      else if (i == 4)
        aux[i] = '1';
      else
        aux[i] = convertir(random(0,9));
    }
    delay(1000);
    Serial.print(aux);
  }
  Serial.end();
}
