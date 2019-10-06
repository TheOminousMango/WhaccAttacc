/*
  AnalogReadSerial

  Reads an analog input on pin 0, prints the result to the Serial Monitor.
  Graphical representation is available using Serial Plotter (Tools > Serial Plotter menu).
  Attach the center pin of a potentiometer to pin A0, and the outside pins to +5V and ground.

  This example code is in the public domain.

  http://www.arduino.cc/en/Tutorial/AnalogReadSerial
*/
#define PADS_NUM 6

// the setup routine runs once when you press reset:

int padsf[PADS_NUM];
int padsi[PADS_NUM];
  
void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(256000);

  for(int i = 0; i < PADS_NUM; i++) {
    padsf[i] = analogRead(i+14);
    padsi[i] = 0;
  }
  
  
}

// the loop routine runs over and over again forever:
void loop() {
  // read the input on analog pin 0:

  //Serial.println(A1);
  
  //pads[2] = analogRead(A2); 
  //pads[2] = 0;
  // print out the value you read:
  //Serial.println(sensorValue);
  for(int i = 0; i < PADS_NUM; i++) {
    if (padsf[i]- padsi[i] > 500) {
    //Serial.println("DRUM HIT - " + String(float((sensorValue-900.0)/100)));
     Serial.print(String(i) + "-");
     Serial.println(abs(int( ( (padsf[i]-500.0)/524.0)*100) ),HEX);
    }

    padsi[i] = padsf[i];
    padsf[i] = analogRead(14+i);
  }

  //delay(500);        // delay in between reads for stability
}
