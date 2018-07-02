//Ultrasonido
const int Trigger = 11;   //Pin digital 2 para el Trigger del sensor
const int Echo = 3;   //Pin digital 3 para el Echo del sensor
//Seguidor
 # define AIN1 A1    // pin 1 de direcci�n del Motor Izquierdo
 # define AIN2 A2   // pin 2 de direcci�n del Motor Izquierdo
 # define PWMA 6    // pin PWM del Motor Izquierdo
 # define BIN1 A3   // pin 1 de direcci�n del Motor Derecho
 # define BIN2 A4   // pin 2 de direcci�n del Motor Derecho
 # define PWMB 5    // pin PWM del Motor Derecho  
 # define STBY A0  // Control de Funcionamiento de los motores General

 # define SensorI 7   // pin 2 de direcci�n del Motor Derecho
 # define SensorC 4    // pin PWM del Motor Derecho  
 # define SensorD 2    // Control de Funcionamiento de los motores General
 int SEN_IZQUIERDA, SEN_MEDIO,SEN_DERECHA;
//garra

#include <Servo.h>

Servo arm; // Servo de elevacion
Servo aga;  // Servo de agarre

void setup() {
 //ultrasonido
   Serial.begin(9600);//iniciailzamos la comunicación
  pinMode(Trigger, OUTPUT); //pin como salida
  pinMode(Echo, INPUT);  //pin como entrada
  digitalWrite(Trigger, LOW);//Inicializamos el pin con 0
 
  // put your setup code here, to run once:
  pinMode(AIN1, OUTPUT);
  pinMode(AIN2, OUTPUT);
  pinMode(PWMA, OUTPUT);
  pinMode(BIN1, OUTPUT);
  pinMode(BIN2, OUTPUT);
  pinMode(PWMB, OUTPUT); 
  pinMode(STBY, OUTPUT);

  pinMode(SensorI, INPUT);
  pinMode(SensorC, INPUT); 
  pinMode(SensorD, INPUT); 
  //garra
  arm.attach(10);
  aga.attach(9);
  arm.write(130);
  aga.write(160);
  Motor(50,50);
  delay(2000);
  Motor(0,0);
}

void loop() {
 
long t; //timepo que demora en llegar el eco
  long d; //distancia en centimetros

  digitalWrite(Trigger, HIGH);
  delayMicroseconds(10);          //Enviamos un pulso de 10us
  digitalWrite(Trigger, LOW);
  t = pulseIn(Echo, HIGH); //obtenemos el ancho del pulso
  d = t/59;             //escalamos el tiempo a una distancia en cm
  
    Serial.print("Distancia: ");
    Serial.print(d);      //Enviamos serialmente el valor de la distancia
    Serial.print("cm");
    Serial.println();
delay(30);
    if(d<=15){
      delay(50);
      Motor(-10, -10);
    delay(400);
      Motor(0, 0);
      recoger();
      if(d<=15){
        Motor(70,70);
        delayMicroseconds(5);
        delay(50);
      Motor(-10, -10);
    delay(400);
      Motor(0, 0);
      recoger();
      }
   }   
   else
    {
    SEN_IZQUIERDA = digitalRead(SensorI);
       SEN_MEDIO = digitalRead(SensorC);
    SEN_DERECHA = digitalRead(SensorD);
    Serial.print(SEN_IZQUIERDA);
    Serial.print('\n');
    Serial.print(SEN_MEDIO);
    Serial.print('\n');
    Serial.print(SEN_DERECHA);
    Serial.print('\n');
    if(SEN_IZQUIERDA==1 && SEN_MEDIO==0 && SEN_DERECHA==1){
    Motor(75, 75);
    
    Serial.print("ADELANTE");
    Serial.println();
    delay(20);
  }
    if(SEN_IZQUIERDA==0 && SEN_MEDIO==1 && SEN_DERECHA==0){
    Motor(75, 75);
    Serial.print("ADELANTE");
    Serial.println();
    delay(20);
  }
//0 es negro 1 es blanco. 
// en este caso estamos sobre la linea y seguimos
  if(SEN_IZQUIERDA==0 && SEN_MEDIO==0 && SEN_DERECHA==0){
    Motor(75, 75);
    Serial.print("ADELANTE");
    Serial.println();
    delay(20);
  }
//en este caso estamos desviandonos un poco a izquierda
//giramos a la derecha UN POCO!!
  if(SEN_IZQUIERDA==1 && SEN_MEDIO==0 && SEN_DERECHA==0){
    Motor(70,75);
    Serial.print("DERECHA  UN POCO");
    Serial.println();
    //delay(20);
  }
//en este caso estamos desviandonos un MUCHO a izquierda
//giramos a la derecha MUCHO!!
  if(SEN_IZQUIERDA==1 && SEN_MEDIO==1 && SEN_DERECHA==0){
    Motor(-50,75); 
    Serial.print(" DERECHA MUCHO");
    Serial.println();
    //delay(20);
  }
  //en este caso estamos desviandonos un poco a la derecha
//giramos a la izquierda UN POCO!!
  if(SEN_IZQUIERDA==0 && SEN_MEDIO==0 && SEN_DERECHA==1){
    Motor(65,60);
    Serial.print("IZQUIERDA UN POCO");
    Serial.println();
    //delay(20);
  }

  if(SEN_IZQUIERDA==0 && SEN_MEDIO==1 && SEN_DERECHA==1){
    Motor(65,-40);
    Serial.print("IZQUIERDA MUCHO");
    Serial.println();
    //delay(20);
  }

  if(SEN_IZQUIERDA==1 && SEN_MEDIO==1 && SEN_DERECHA==1){
    Motor(-60,-60);
    Serial.print("RETROCESO");
    Serial.println();
    delay(20);
  }
      //gfhdaS}
    
}
}


void MotorIz(int value) //value -255 a 255
{
  if(value>=0)
  {
    digitalWrite(BIN1,HIGH); //Adelante
    digitalWrite(BIN2,LOW);
  }
  else
  {
    digitalWrite(BIN1,LOW); //Atras
    digitalWrite(BIN2,HIGH);
    value *=-1;
  }
  analogWrite(PWMB,value);
}
void MotorDe(int value) //value -255 a 255
{
  if(value>=0)
  {
    digitalWrite(AIN1,HIGH);//Adelante
    digitalWrite(AIN2,LOW);
  }
  else
  {
    digitalWrite(AIN1,LOW); //Atras
    digitalWrite(AIN2,HIGH);
    value*=-1;
  }
  analogWrite(PWMA,value);
}
void Motor( int left, int right) //value -255 a 255
{
  digitalWrite(STBY,HIGH);
  MotorIz(left);
  MotorDe(right);
  Serial.print("motores");  
}
void freno(boolean left, boolean right, int value) // value 0 a 255---left,right, HIGH o LOW
{
  digitalWrite(STBY,HIGH);
  if(left)
  {
    digitalWrite(BIN1,HIGH);
    digitalWrite(BIN2,HIGH);
    analogWrite(PWMB, value);
  }
  if(right)
  {
    digitalWrite(AIN1,HIGH);
    digitalWrite(AIN2,HIGH);
    analogWrite(PWMA, value);
  } 
}

void angulomas(int angle,int secs){
  for (int i=0;i<=angle;i++){
    arm.write(i);
    delay(secs);
  }
}
void angulomenos(int angle,int secs){
  for (int i=0;i<=angle;i++){
    arm.write(angle-i);
    delay(secs);
  }
}
void ctrlangulomas(int angle){
  angulomas(angle,10);
}
void ctrlangulomenos(int angle){
  angulomenos(angle,10);
  
}
void recoger(){
  //  Bajar Brazo
  ctrlangulomenos(130);
  delay(200);
  // Agarrar Cubo
  aga.write(90);
  delay(200);
  // Levantar Brazo
  ctrlangulomas(130);
  //delay(200);
  // Soltar Cubo
  aga.write(160);

}

void descanso(){
  Serial.print("Posicion Inicial de la Garra");
  arm.write(130);
  aga.write(130);
}

