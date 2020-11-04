#include <PololuMaestro.h> //Załadowanie biblioteki Pololu
#include <SoftwareSerial.h> //Załadowanie bilbioteki odpowiedzialnej za obsługę wirtualnego portu szeregowego
SoftwareSerial maestroSerial(10, 11); //Definicja wirtualnego portu szeregowego 10 RX 11 TX

MicroMaestro maestro(maestroSerial); //Definicja sterownika - Pololu micro maestro

boolean incData = false; //Zmienna symbolizująca nowe nadchodzące informacje
String Data[4]; //Zmienna przechowująca części przychodzącego strumienia danych
String Data1; //Pierwsza część macierzy Data definiuje co ma zostać wykonane
float Data2,Data3,Data4; //Parametry używane do obsługi poleceń
int i = 0;
char a = 'b' ;
 
void setup() {
  //Uruchomienie obu portów szeregowych - głównego portu Arduino oraz wirtualnego portu Pololu
  Serial.begin(9600);
  maestroSerial.begin(9600);
}

void loop() {
  //Wywołanie dwóch głównych funkcji w pętli
  receiveEndMarker(); //Odbiór danych i podział ich na części składowe
  ExecuteCommand(); //Wykonywanie polecenia w zależności od odebranych danych.
}

void receiveEndMarker(){
 static char EndMarker = ','; //Znacznik końca polecenia
 static char Divider = ':'; //Znacznik dzielący polecenie
 char receive; //Zmienna w którą zapisywany jest bajt odebrany
 String Databuf1,Databuf2,Databuf3,Databuf4; //Bufer zmiennych  - tylko do chwilowego przechowania danych służacy do zmiany ich typu

 while (Serial.available() >0 && incData == false){
  receive = Serial.read();
  if(receive == Divider){
    i++;
  }
  if(receive != EndMarker && receive != Divider){
    Data[i] += receive;    
  }
  if(receive == EndMarker){
    incData = true;    
    i=0;
  }
  //Zmiana typu dancyh na taki, który może zostać użyty w przyszłości *note to self*może da sie to ładniej zrobić?
    Databuf1 = Data[0];
    Databuf2 = Data[1];
    Databuf3 = Data[2];
    Databuf4 = Data[3];
    Data1 = Databuf1;
    Data2 = Databuf2.toFloat();
    Data3 = Databuf3.toFloat();
    Data4 = Databuf4.toFloat();
 }
}


void ExecuteCommand() {
 if(incData == true){
    CommandList(); //Funkcja ,w której są zapisane wszelkie polecenia do wykonania przez arduino, które są wywoływane z Matlaba.
      for(int k =0;k<=3;k++){
        //Wyczyszczenie macierzy Data
        Data[k]="\0";
      }
  }   
  incData = false;
}

void CommandList(){
  if(Data1 == "servo"){
    //Po wpisaniu do konsoli: 'servo:Data2:Data3:Data4,' sterownik wysterowuje serwomechanizm,
    //Data2 jest tutaj kanałem sterownika, Data3 prędkością obrotową, Data4 przyspieszeniem.
    maestro.setAcceleration((int) Data2, (int)Data4);
    maestro.setTarget((int) Data2,(int) Data3);
    }   
   if(Data1 == "test"){
    //polecenie testowe, ma za zadnie wyświetlić wartości użyte w poleceniu.
    Serial.println(Data1);
    Serial.println((int)Data2);
    Serial.println((int)Data3);
    Serial.println((int)Data4);    
   }   
   if(Data1 == "a"){
    Serial.println('a');    
   }
}
