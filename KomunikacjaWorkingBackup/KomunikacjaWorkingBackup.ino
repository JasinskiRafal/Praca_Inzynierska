boolean incData = false;
String Data[4];
String PastData[4];
String Data1;
float Data2,Data3,Data4;
int i = 0;
 
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(7,OUTPUT);
  Serial.println("<Serial Setup>");
}

void loop() {
  // put your main code here, to run repeatedly:
  receiveEndMarker();
  showNewData();
}

void receiveEndMarker(){
 char EndMarker = ',';
 char Divider = ':';
 char receive;
 String Databuf1,Databuf2,Databuf3,Databuf4;

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


void showNewData() {
 if(incData == true){
  if(Data1 == "a"){
    Serial.println(Data1);
    Serial.println(Data2);
    Serial.println(Data3);
    Serial.println(Data4);
    }   
   for(int k =0;k<=3;k++){
     Data[k]="\0";
   }
  }
  incData = false;
}
