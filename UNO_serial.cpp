#include "Arduino.h"
#include <stdio.h>
#include <string.h>
#include "UNO_Serial.h"
#include <SoftwareSerial.h>

SoftwareSerial mySerial(5, 6);

int numOfBytes=0;         // used for getting buffer size
char received_data[70];   // Initialized variable to store recieved data

//array to store the receved data
char* element;
char *received_data_array[19];

// variables to hold records of previous launched time 
long previous1 = 0;
long previous2 = 0;
long previous3 = 0;
long previous4 = 0;

//*******************************************
// Initilise serial communication
//*******************************************
void UNO_Serial::serial_setup()
{
   mySerial.begin(9600);
   mySerial.write("S,0,0");
   Serial.begin(9600);      // initialise serial communication
   Serial.write("S,0,0");   // sent a request to ESP32 to send you its data
}

//********************************************************
// Function which converts the string to string array.
//********************************************************
void UNO_Serial::put_string_to_array(char string_array[]){
  
   element = strtok(string_array, " ");                   //split string into string array with delimiter " "
          received_data_array[0] = element;               //first element
          for(int i=1;i<19;i++){                          //all the othe elements
               element = strtok(NULL," ");
               received_data_array[i]=element;      
               Serial.println(element);
           }
}

//**************************************************************************************************
// Function which receives the ultrasonc data and the other's drone GPS coordnitaes from ESP32.
// it updates the according variable values and sends back to ESP32 the GPS coordinate of my drone. 
//**************************************************************************************************
void UNO_Serial::exchange_data_with_esp32(){
    unsigned long current_time = millis();                //get current elapsed time in ms
    delay(1000);
    if(mySerial.available()>0){
    //if(Serial.available()>0){                             //check if they are data in the buffer
       if (current_time - previous1 >= 20){               //wait 20 ms
           previous1 = current_time;
           numOfBytes = mySerial.available();
           Serial.println(numOfBytes);
           mySerial.readBytes(received_data,numOfBytes);
           //numOfBytes = Serial.available();               //get the buffer size
           //Serial.readBytes(received_data,numOfBytes);    //get the data from esp32 and store them to received_data char array  
           Serial.println(received_data);
           if (current_time - previous2 >= 30){           //wait 30 ms
               previous2 = current_time;
               if (strcmp(received_data[0],'m')==0){      //check if the data are from ESP32, hint "m" 
                  put_string_to_array(received_data);     //store the data into string array
                                    
                  if (current_time - previous3 >=60){     //wait 60 ms
                    previous3 = current_time;            
                    //send_my_gps_data();                   // send back to ESP32 my gps coordinates
                    mySerial.write("S,0,0");
                   }                                           
                }
                 
              if (current_time - previous4 >= 90){        //wait 90 ms
                  previous4 = current_time;
                  //set_variable_values();                  //update the variable values
              }
            }
       }      
   }
   else{                    //if there is no data on the buffer request again data from ESP32
    mySerial.begin(9600);
    mySerial.write("S,0,0");
    Serial.begin(9600);
    Serial.write("S,0,0");
   }
}
