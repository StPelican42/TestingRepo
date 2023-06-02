///////////////////////////////////////////////////////////////////////////////
// Circuit Playground Total Acceleration
//
// Author: Carter Nelson
// MIT License (https://opensource.org/licenses/MIT)

#include <Adafruit_CircuitPlayground.h>
int pixelArray[10]={0,1,2,3,4,5,6,7,8,9};
int colorValOne, colorValTwo, colorValThree;
int shakeNum=15;
int shakeVal;
int done;
int x;
float X, Y, Z, totalAccel;

  
///////////////////////////////////////////////////////////////////////////////
void setup() {
  Serial.begin(9600);

  CircuitPlayground.begin();
  randomSeed(analogRead(0));
  CircuitPlayground.setAccelRange(LIS3DH_RANGE_8_G);
}

///////////////////////////////////////////////////////////////////////////////
void loop() {
  X = 0;
  Y = 0;
  Z = 0;
  for (int i=0; i<10; i++) {
    X += CircuitPlayground.motionX();
    Y += CircuitPlayground.motionY();
    Z += CircuitPlayground.motionZ();
    delay(1);
  }
  X /= 10;
  Y /= 10;
  Z /= 10;

  totalAccel = sqrt(X*X + Y*Y + Z*Z);

  Serial.println(totalAccel);

  delay(100);
  if(totalAccel>=shakeNum){
    shakeVal=map(totalAccel,10,150,0,255);
    CircuitPlayground.clearPixels();
    done=0;
    sparkle(10);
    
  }else{
    randomFill();
  }
  }



void sparkle(int num){
  for (int i=0;i<20;i++){
  CircuitPlayground.setPixelColor(random(10), shakeVal, shakeVal, shakeVal);
  CircuitPlayground.setPixelColor(random(10), shakeVal, shakeVal, shakeVal);
  CircuitPlayground.setPixelColor(random(10), shakeVal, shakeVal, shakeVal);
  CircuitPlayground.setPixelColor(random(10), shakeVal, shakeVal, shakeVal);
  CircuitPlayground.setPixelColor(random(10), shakeVal, shakeVal, shakeVal);
  CircuitPlayground.setPixelColor(random(10), shakeVal, shakeVal, shakeVal);
  CircuitPlayground.setPixelColor(random(10), shakeVal, shakeVal, shakeVal);
  delay(num/2);
  CircuitPlayground.clearPixels();
  delay(num/2);
  }
}

void randomFill(){     // randomly lights each pixel with a random color.
  for (int i=0;i<10;i++){
        pixelArray[i]=i;  //resets the pixelArray array to be used again.
      }                 
  colorValOne=random(255);
  colorValTwo=random(255);
  colorValThree=random(255);
  //CircuitPlayground.clearPixels();
  while(done==0){ // bool that waits until all pixels have been lit.
  x=random(10);
  if (pixelArray[x]==11){   // if the value for the array has been used, it was set to 11.
    while(pixelArray[x]==11){  // x will repeat finding random values until the array value for 
      x=random(10);            // the xth item is not 11, meaning it has not been lit.
    }
  }
  CircuitPlayground.setPixelColor(x, colorValOne, colorValTwo, colorValThree);
  delay(100);
  pixelArray[x]=11;// Marking the array value so the code doesn't light the same pixel twice.
  for (int i=0;i<10;i++){
    if (pixelArray[i]!=11){
      done=0;
      break;// Breaks out of loop if there is any light that has not been lit
    }else{
      done=1;// If none of the array values are not 11, then everything has been lit, meaning
      }      // the function is done.
    }
  }
}

