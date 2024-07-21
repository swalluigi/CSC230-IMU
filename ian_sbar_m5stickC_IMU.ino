/*
*******************************************************************************
* Copyright (c) 2021 by M5Stack
*                  Equipped with M5StickC-Plus sample source code
*                          配套  M5StickC-Plus 示例源代码
* Visit for more information: https://docs.m5stack.com/en/core/m5stickc_plus
* 获取更多资料请访问: https://docs.m5stack.com/zh_CN/core/m5stickc_plus
*
* Describe: IMU.
* Date: 2021/9/14
*modified by Ian Sbar, 2023/2/27, iansbar@uat.edu

*goal: make the M5stickCplus  display maximum accel value in each direction
*******************************************************************************
*/
#include <M5StickCPlus.h>
#define LED_BUILTIN 10

//3 variables for acceleration direction
float accX = 0.0F; 
float accY = 0.0F;
float accZ = 0.0F; // up and down

float maxX = 0.0f;
float maxY = 0.0f;
float maxZ = 0.0f;

float XSqr = 0.0f;
float YSqr = 0.0f;
float ZSqr = 0.0f;

float VectMag = 0.0f; //vector magnitude
float maxVectMag= 0.0f;


//spinning
float gyroX = 0.0F;
float gyroY = 0.0F;
float gyroZ = 0.0F;



/* After M5StickC Plus is started or reset
  the program in the setUp () function will be run, and this part will only be
  run once. 在 M5StickC Plus
  启动或者复位后，即会开始执行setup()函数中的程序，该部分只会执行一次。 */


void setup() {

    digitalWrite(LED_BUILTIN, HIGH);  
    M5.begin();             // Init M5StickC Plus.  初始化 M5StickC Plus
    M5.Imu.Init();          // Init IMU.  initializes IMU. allows it to record data
    pinMode(LED_BUILTIN, OUTPUT); //
    M5.Lcd.setRotation(3);  // Rotate the screen. 
    M5.Lcd.fillScreen(BLACK);
    M5.Lcd.setTextSize(1);
    M5.Lcd.setCursor(80, 15);  // set the cursor location.  设置光标位置
    M5.Lcd.println("IMU TEST");
    M5.Lcd.setCursor(30, 30);
    M5.Lcd.println("  X       Y       Z");
    M5.Lcd.setCursor(30, 70);
    M5.Lcd.println("  Max X   Max Y    Max Z");
    M5.Lcd.setCursor(80, 90);
    M5.Lcd.println("max Vector");
    

}

/* After the program in setup() runs, it runs the program in loop()
The loop() function is an infinite loop in which the program runs repeatedly
在setup()函数中的程序执行完后，会接着执行loop()函数中的程序
loop()函数是一个死循环，其中的程序会不断的重复运行 */

void loop() {
     M5.update();  // Read the press state of the key.  读取按键 A, B, C 的状态
  
    M5.IMU.getGyroData(&gyroX, &gyroY, &gyroZ); //gets gyro data
    M5.IMU.getAccelData(&accX, &accY, &accZ);// gets accerlation data

    //find Maxes
    if(maxX < accX){ // if maxX is smaller than accX, maxX is replaced with accX
      maxX = accX; 
    }

    if(maxY < accY){ // if maxY is smaller than accY, maxY is replaced with accY
      maxY = accY; 
    }

    if(maxZ < accZ){ // if maxZ is smaller than accZ, maxZ is replaced with accZ
      maxZ = accZ; 
    }

//make XSqr YSqr ZSqr
    XSqr = sq(accX);
    YSqr = sq(accY);
    ZSqr = sq(accZ);
    
    //determine vector magnitude by taking the square root of xsq+ysq+zsq
      VectMag =sqrt(XSqr+YSqr+ZSqr);

    //determine max vector magnitude
    if (VectMag > maxVectMag){
      maxVectMag = VectMag;

      //if vector mag is greater than 13
      if(maxVectMag > 13){
        //blink 3 times
        for (int i=0; i<3; i++){
          digitalWrite(LED_BUILTIN, LOW);  // turn the LED on (HIGH is the voltage level)
          delay(1000);                      // wait for a second
          digitalWrite(LED_BUILTIN, HIGH);   // turn the LED off by making the voltage LOW
          delay(1000);   
        }
              
      }
    }
    
    

    M5.Lcd.setCursor(30, 40);
    M5.Lcd.printf("%6.2f  %6.2f  %6.2f      ", gyroX, gyroY, gyroZ); //6.2 means there are two decimals places and numbers are mod 6. these apply to the inputs after the first comma
    M5.Lcd.setCursor(170, 40);
    M5.Lcd.print("o/s");
    M5.Lcd.setCursor(30, 50);
    M5.Lcd.printf(" %5.2f   %5.2f   %5.2f   ", accX, accY, accZ);//5.2 means there are two decimals places and numbers are mod 5. these apply to the inputs after the first comma
    M5.Lcd.setCursor(170, 50);
    M5.Lcd.print("G");
    M5.Lcd.setCursor(30, 80);
    M5.Lcd.printf(" %5.2f   %5.2f   %5.2f   ", maxX, maxY, maxZ);
    M5.Lcd.setCursor(90, 100);
    M5.Lcd.printf( "%5.2f", maxVectMag);




     //button stuff
    if (M5.BtnA.wasReleased()) {  // If the button A is pressed.  如果按键 A 被按下
      maxX = 0;
      maxY= 0;
      maxZ=0;
      maxVectMag = 0;

    } 
}
