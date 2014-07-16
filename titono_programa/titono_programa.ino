const int boton = 2;  //Control de la Tapa
boolean estado;
int led1 = 9;
int led2 = 10;
int led3 = 11;
int motor = 7;

int brillo1 = 0;
float suma = 5;

int soplo[300];
int soplido;
long general = 0;

int value = LOW;    
long cnt = 0;         
long low = 0;        
long high = 1000; 
int op = 3;
long a = 0;
int periodo = 0;
int contador = 0;
int scont = 0;
int tiempo = 0;

void setup(){
  Serial.begin(9600);

  pinMode(boton, INPUT);
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(motor, OUTPUT);
}

void loop(){
  estado = digitalRead(boton);

  if(estado == 0){
    soplido = analogRead(A0);
    scont = 0;
    tiempo = 0;
    digitalWrite(motor, LOW);
    //Cuando la tapa está abierta

    if(soplido > 52){
      int sumando = (int)map(soplido, 52, 200, 1, 5);
      general += sumando;

      brillo1 = map(soplido, 52, 200, 0, 255);
      brillo1 = constrain(brillo1, 0, 255);

      analogWrite(led1, brillo1);
      analogWrite(led2, brillo1);
      analogWrite(led3, brillo1);
    }
    else{
      analogWrite(led1, 0);
      analogWrite(led2, 0);
      analogWrite(led3, 0);
    }
  }
  else{
    //Cuando la tapa está cerrada
    soplido = 0;

    if(general > 100){

      periodo = map(general, 100, 1500, 200, 6000);
      periodo = constrain(periodo, 0, 6000);

      tiempo = map(general, 100, 1500, 0, 350);
      tiempo = constrain(tiempo, 0, 350);

      contador++;
      scont++;

      if(contador > 0){
        a += op;
        pulso(a, 10);
        if( a > 200 || a < 0 ) op *= -1;
      }

      if(contador == 600){
        general = 0;
        contador = 0;
        scont = 0;

        digitalWrite(led1, 0);
        digitalWrite(led2, 0);
        digitalWrite(led3, 0);
      }

      if(scont > tiempo){
        digitalWrite(motor, LOW);
      }
      else{
        digitalWrite(motor, HIGH);
      }
    }
    else{
      digitalWrite(motor, LOW);
    }
  }

  Serial.println(tiempo);
}


void pulso(long low, long high){ 
  int c = 2;
  while ( c > 0 ) {
    blink(low, high, periodo);
    c-=1;
  }
}

void blink(long low, long high, int periodo){
  long period = periodo;
  long pt = period * high / (low + high );
  int value = LOW;
  digitalWrite(led1, value);
  digitalWrite(led2, value);
  digitalWrite(led3, value);

  while( period > 0 ) {   
    if (period < pt && value == LOW ) { 
      value = HIGH;
      digitalWrite(led1, value);
      digitalWrite(led2, value);
      digitalWrite(led3, value);     
    }     
    period -= 1;
  } 
}



















