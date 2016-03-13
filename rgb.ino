#include <RCSwitch.h>

#define RED_PIN 3
#define GREEN_PIN 5 
#define BLUE_PIN 6
#define DEVICE_ID 15

unsigned long deviseOff =  (DEVICE_ID * 10);

unsigned long deviseOn =  deviseOff + 1;

unsigned long powerState = 0;

unsigned long redStateLow = deviseOn * 1000;
unsigned long redStateHigh = redStateLow + 255;
unsigned long greenStateLow = redStateHigh + 1;
unsigned long greenStateHigh = greenStateLow + 255;

unsigned long blueStateLow = greenStateHigh + 1;
unsigned long blueStateHigh = blueStateLow + 255;


RCSwitch mySwitch = RCSwitch();

int redValue = 0;
int greenValue = 0;
int blueValue = 0;


void setup() {
    Serial.begin(9600);
    Serial.write("Start Listening\n");
    Serial.println( redStateLow );
    Serial.println( redStateHigh );
    Serial.println( greenStateLow );
    Serial.println( greenStateHigh );
    Serial.println( blueStateLow );
    Serial.println( blueStateHigh );

    mySwitch.enableReceive(0);  // Receiver on inerrupt 0 => that is pin #2}
}

void loop() {
    
    if (mySwitch.available()) {
        unsigned long value = mySwitch.getReceivedValue();
        if (value == 0) {
          Serial.print("Unknown encoding\n");
        } else {
            if (value == deviseOn) {
                if(powerState != 1) {
                    Serial.write("switching on\n");
                    powerState = 1;
                }
            } else if (value == deviseOff){
                if(powerState != 0) {
                    Serial.write("switching off\n");
                    powerState = 0;
                }
            }
             if(value >= redStateLow && value <= redStateHigh) {
                  redValue = value - redStateLow;
                  //printrgb();

              }
              else if(value >= greenStateLow && value <= greenStateHigh) {
                  greenValue = value - greenStateLow;
                  //printrgb();
              }
              else if(value >= blueStateLow && value <= blueStateHigh) {
                  blueValue = value - blueStateLow;
                  //printrgb();
              }    
        }
        mySwitch.resetAvailable();
      }
      if(powerState == 1) {           
          analogWrite(RED_PIN, redValue);
          analogWrite(GREEN_PIN, greenValue);
          analogWrite(BLUE_PIN, blueValue);
      }
}

void printrgb() {
  Serial.println( redValue );
  Serial.println( blueValue );
  Serial.println( greenValue );
}

