#include <SPI.h>  
#include <Pixy.h>

Pixy pixy;

int sig_1, getX_1, getY_1, width_1, height_1;
int sig_2, getX_2, getY_2, width_2, height_2;

int found = 10;

int pinState = 2;

void setup()
{
  Serial.begin(115200);
  pinMode(pinState, OUTPUT);
  Serial.print("Starting...\n");
  pixy.init();
}

void loop()
{ 
  uint16_t blocks;
  
  blocks = pixy.getBlocks();

  if (blocks) {
    /*=== Check Sig 1 ===*/
    sig_1 = pixy.blocks[0].signature;
    getX_1 = pixy.blocks[0].x;
    width_1 = pixy.blocks[0].width;
    /*===================*/
    
    if (sig_1 == 1 && getX_1 > 150 && width_1 > 20) {
      
      sig_1 = pixy.blocks[0].signature;
      getX_1 = pixy.blocks[0].x;
      getY_1 = pixy.blocks[0].y;
      width_1 = pixy.blocks[0].width;
      height_1 = pixy.blocks[0].height;
      
      Serial.print("sig : "); Serial.print(sig_1);
      Serial.print(" x : "); Serial.print(getX_1);
      Serial.print(" y : "); Serial.print(getY_1);
      Serial.print(" w : "); Serial.print(width_1);
      Serial.print(" h : "); Serial.println(height_1);
      Serial.println("==========");
      
      /*=== Check Sig 2 ===*/
      sig_2 = pixy.blocks[1].signature;
      getX_2 = pixy.blocks[1].x;
      width_2 = pixy.blocks[1].width;
      /*===================*/
      
      if (sig_2 == 2) {
        sig_2 = pixy.blocks[1].signature;
        getX_2 = pixy.blocks[1].x;
        getY_2 = pixy.blocks[1].y;
        width_2 = pixy.blocks[1].width;
        height_2 = pixy.blocks[1].height;
        
        Serial.print("sig : "); Serial.print(sig_2);
        Serial.print(" x : "); Serial.print(getX_2);
        Serial.print(" y : "); Serial.print(getY_2);
        Serial.print(" w : "); Serial.print(width_2);
        Serial.print(" h : "); Serial.println(height_2);
        Serial.println("==========");
        found++;
        digitalWrite(pinState, 1);
        
      } else {
        found--;
      }

      if (found == 0) {
        stateOff();
      }

      delay(50);

    } else {
      Serial.println("Not Found");
      delay(50);
    }
    
  } else {
    stateOff();
  }
  
}

void stateOff() {
  digitalWrite(pinState, 0);
}

