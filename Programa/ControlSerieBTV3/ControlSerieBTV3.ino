// *******************************************************************************************************
// *******************************************************************************************************
// ********  PROGRAMA RESUELVE SIGUELINEAS DE IGNACIO OTERO CONCURSO OSHWDEM 2019 CORUÑA          *********
// *******************************************************************************************************
// *******************************************************************************************************
// ************       NOMBRE PROPUESTO DEL BICHO TESELA (¡---- --------!)                     *************
// *******************************************************************************************************
// *******************************************************************************************************
// Versión 9.3 Primera versión que funciona con bolita y sin bolita! 26/10/2019

// Parámetros configurables en "Configuracion.h"
/*
  Sistema de guiado a través de Bluetooth, para ajuste de siguelineas
  
  Lee los comandos que llegan por BT y ajusta la velocidad y dirección

  El circuito:
  -Control de motores conectados pines PWM 3,5,6,11
  -Control de servo conectado a pin 4
  -Entradas analógicas conectadas a pines A1, A2, A3, A4
 
  created 4 octubre 2019
  modified 24 octubre 2019
  Por Ignacio Otero

  
*/

#include "Configuracion.h"
#include <Servo.h>
Servo myservo;  // create servo object to control a servo


// Variables generales
boolean Autopilot = false;    // Indica el estado del vehículo, en movimiento o parado
int ValorPinDir = 0;      // Valor de lectura del potenciometro dirección
int SalidaPinDir = central;  // Valor de salida servo (-180,180) limitado en margen
                             // Los valores están comprendidos entre central-margen y central+margen (50, 120)
                             // A parte del servo se van a utilizar para cambiar la velodidad de los motores
// Velocidades motores
int Vel_Motor_D=0;
int Vel_Motor_I=0;
                             
int ValorPinVel = 0;      // Valor de lectura del potenciómetro velocidad
int SalidaPinVel = 0;     // Valor de salida de la velocidad (-255, 255). Negativo es inversa
                          // En siguelineas no vamos a trabajar con valores negativos para la dirección
                          // Probamos con el doble del valor de SalidaPinDir, de tal manera que:
                          //              - si es menor de 85, frenamos motor izquierdo Freno=2*(85-SalidaPinDir)
                          //              - si es mayor de 85, frenamos motor derecho   Freno=2*(SalidaPinDir-85)
                          //              - Evidentemente si no hay freno ponemos       Freno=0
int pos = 0;              // Almacena el valor del servo  
int Freno=0;              // Valor de freno en cada momento

// Variables de sensores analógicos
int SensorD2=0;
int SensorD1=0;
int SensorI1=0;
int SensorI2=0;
int Posicion=0;


void setup() {
  Serial.begin(9600);
 
  Serial.println(F("\n\n-------------------------------------------"));
  Serial.println(F("Configuración Zumo, versión 9.3, 25/10/2019"));
  Serial.println(F("             Ignacio Otero"));
  Serial.println(F("-------------------------------------------\n\n"));

  // Configuramos la entrada de Boton como pullup
  pinMode(BOTON, INPUT_PULLUP);

  // Colocamos servo en PinServo
  myservo.attach(PinServo);  // 
  
  // Dirección del servo al centro 
  myservo.write(SalidaPinDir);

  // Paramos motores
  Serial.println("Motores parados:");
  PonemosMotores(0,0); 
 
}

void loop() {
 // Leemos BT
 LeemosBT();

 // Leemos Botón
 LeemosBoton();

 // Leemos Sensores IR
 LeemosIR();
 
 // Calculamos la poiscion del sensor IR en la línea negra
 // Inicialmente esta función nos da el valor de SalidaPinDir y Velocidad
 // central-margen< SalidaPinDir < central+margen
 // -255 < Velocidad < 255 
 CalculamosPos();  

 // Colocamos la direcciòn de las ruedas por el servo
  myservo.write(SalidaPinDir);
      
  // Calculamos el freno en función del desvío del sensor a la línea negra
  // El freno será 0 cuando SalidaPinDir = central
  // Cuando el freno el máximo para el motor correspondiente
  // El freno será la velocidad cuando SalidaPinDir=central+/-margen
  // -SalidaPinVel < Freno < SalidaPinVel
  Freno= SalidaPinVel*(central-SalidaPinDir)/margen;   //3*(central-SalidaPinDir); // Máximo de 3 veces el margen
  Serial.print("\t Freno=");
  Serial.print("\t");
  Serial.println(Freno);  
    
   // Colocamos velocidad
   // SI EL FRENO ES POSITIVO MOVIMIENTO A LA IZQUIERDA
   if(Freno>=0){ // Fenamos motor I
         Vel_Motor_D=SalidaPinVel;
         Vel_Motor_I=SalidaPinVel-Freno;
         }
  
   // SI EL FRENO ES NEGATIVO MOVIMIENTo A LA DERECHA
   else {
         Vel_Motor_D=SalidaPinVel+Freno;
         Vel_Motor_I=SalidaPinVel;
         }
   if(Autopilot) PonemosMotores(Vel_Motor_I,Vel_Motor_D);      
  
  // 
  delay(20);
}

//***********************************************
//****       FUNCIÓN LEEMOS BLUETOOTH        ****
//***********************************************
void LeemosBT() {
   char opcion = Serial.read();
  if (opcion == '0')  {
    SalidaPinDir= central;    
    SalidaPinVel=0;
  }
  else if (opcion == '1')  {
    SalidaPinDir= central;    
  }
  else if (opcion =='D') {
    SalidaPinDir=SalidaPinDir+5;
    if(SalidaPinDir<central-margen) SalidaPinDir=central-margen;
  }
  else if (opcion =='I') {
    SalidaPinDir=SalidaPinDir-5;
    if(SalidaPinDir>central+margen) SalidaPinDir=central+margen;
  }
   else if (opcion =='A') {
    SalidaPinVel=SalidaPinVel+10;
    if(SalidaPinVel>255) SalidaPinVel=255;
  }
   else if (opcion =='R') {
    SalidaPinVel=SalidaPinVel-10;
    if(SalidaPinVel<-255) SalidaPinVel=-255;
  }
  else if (opcion =='P') {
    Autopilot=!Autopilot;
  }

} // Fin función leemos BT


//***********************************************
//****      FUNCIÓN LEEMOS INICIO    PARADA  ****
//***********************************************
void LeemosBoton() {
   if(!digitalRead(BOTON)) {
        Autopilot=!Autopilot;  // Cada vez que se pulsa cambia de estado
        if(Autopilot) Serial.println("\nAutopilot ON");
        else {
           Serial.println("\Autopilot OFF");
           // Paramos motores
           Serial.println("Motores parados:");
           PonemosMotores(0,0); 
        }
        delay(100);
   }
}


//***********************************************
//****  FUNCIÓN LEEMOS SENSORES INFRARROJOS  ****
//***********************************************
void LeemosIR() {

 // Leemos las entradas, menos de 100 está en la línea:
      SensorD2=analogRead(A1);
      SensorD1=analogRead(A2);
      SensorI1=analogRead(A3);
      SensorI2=analogRead(A4);
  

   // Ponemos el valor
  //Serial.println("A4 \tA3 \tA2 \tA1 \t\tPos \tDir \tVel");
  //Serial.print(SensorI2);
  //Serial.print("\t");
  //Serial.print(SensorI1);
  //Serial.print("\t");
  //Serial.print(SensorD1);
  //Serial.print("\t");
  //Serial.print(SensorD2);
  //Serial.print("\t\t");

} // Fin funcion leemos IR


//***********************************************
//****      FUNCIÓN CALCULAMOS POSICIÓN      ****
//***********************************************
void CalculamosPos() {  
  // Calculamos la posicion
  // Fuera de linea es 999
  // Cuando esta fuera de línea tiene que saber cual era la última posición
  // Giramos +/- en función de la posición
  // Cuando no está en linea tiene que seguir el rumbo de la posición anterior o incrementarla
  if((SensorI2>NEGRO)&(SensorI1>NEGRO)&(SensorD1>NEGRO)&(SensorD2>NEGRO)) {
          Serial.println("Fuera de linea");// no cambiamos la Posicion = 999;
          SalidaPinVel=V_MIN;
          }
  else if((SensorI2<NEGRO)&(SensorI1>NEGRO)&(SensorD1>NEGRO)&(SensorD2>NEGRO)) {
          Posicion = -3;
          SalidaPinDir=central-margen;
          SalidaPinVel=V_MIN;
        }
  else if((SensorI2<NEGRO)&(SensorI1<NEGRO)&(SensorD1>NEGRO)&(SensorD2>NEGRO)) {
          Posicion = -2;
          SalidaPinDir=central-margen/2;
          SalidaPinVel=V_MED;
        }
  else if((SensorI2>NEGRO)&(SensorI1<NEGRO)&(SensorD1>NEGRO)&(SensorD2>NEGRO)) {
          Posicion = -1;
          SalidaPinDir=central-margen/4;
          SalidaPinVel=V_MAX;
        }
  else if((SensorI2>NEGRO)&(SensorI1<NEGRO)&(SensorD1<NEGRO)&(SensorD2>NEGRO)) {
          Posicion =  0;
          SalidaPinDir=central;
          SalidaPinVel=V_MAX;
        }
  else if((SensorI2>NEGRO)&(SensorI1>NEGRO)&(SensorD1<NEGRO)&(SensorD2>NEGRO)) {
          Posicion =  1;
          SalidaPinDir=central+margen/4;
          SalidaPinVel=V_MAX;
        }
  else if((SensorI2>NEGRO)&(SensorI1>NEGRO)&(SensorD1<NEGRO)&(SensorD2<NEGRO)) {
          Posicion =  2;
          SalidaPinDir=central+margen/2;
          SalidaPinVel=V_MED;
        }
  else if((SensorI2>NEGRO)&(SensorI1>NEGRO)&(SensorD1>NEGRO)&(SensorD2<NEGRO)) {
         Posicion =  3;
         SalidaPinDir=central+margen;
         SalidaPinVel=V_MIN;
        }

  // Limitamos SalidaPinDir en el margen
  if(SalidaPinDir<central-margen) SalidaPinDir=central-margen;  
  if(SalidaPinDir>central+margen) SalidaPinDir=central+margen;   
  // Ponemos el valor de salida del servo
  Serial.print("\tDir=");
  Serial.print(SalidaPinDir);
  
  // Ponemos la posición
  Serial.print("\tPos=");
  Serial.print(Posicion);
  Serial.print("\t");
} // Fin funcion calcula la posición


//***********************************************
//****        FUNCIÓN PONEMOS MOTORES        ****
//***********************************************
void PonemosMotores(int VelIzq, int VelDer) {
// Si la velocidad es menor que 10 no hacemos nada  
        //MOTOR D
        //if((VelDer>10)||(VelDer<-10)){ // No tenemos en cuenta valores menores que 10
              if(VelDer>=0) {
                  analogWrite(MDA,VelDer);
                  analogWrite(MDB,0);
              } else {
                  analogWrite(MDA,0);
                  analogWrite(MDB,-VelDer);          
              }
        //}
        
        //MOTOR I
        //if((VelIzq>10)||(VelIzq<-10)){ // No tenemos en cuenta valores menores que 10        
              if(VelIzq>=0) {
                  analogWrite(MIA,VelIzq);
                  analogWrite(MIB,0);
              } else {
                  analogWrite(MIA,0);
                  analogWrite(MIB,-VelIzq);          
              }
  //}
  // Ponemos información motores
  Serial.print("\t VI=");
  Serial.print("\t");
  Serial.print(VelIzq);
  Serial.print("\t VD=");
  Serial.print("\t");
  Serial.print(VelDer);
} // Fin función ponemos motores
