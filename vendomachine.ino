#include <Keypad.h>
#include <SPI.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16,2);
#include <Servo.h>

Servo servo1, servo2, servo3, servo4;

//IR PIN
const int irPin1 =6;
const int irPin2 =5;
const int irPin3 =4;
const int irPin4 = 3;

const int ROW_NUM = 4; //four rows
const int COLUMN_NUM = 3; //three columns

char keys[ROW_NUM][COLUMN_NUM] = {
  {'1','2','3'},
  {'4','5','6'},
  {'7','8','9'},
  {'*','0','#'}
};

//coinslot


#define coinSlot 2

int coinSlotStatus;
int pulse;

byte pin_rows[ROW_NUM] = {7, 8, 9, 10}; //connect to the row pinouts of the keypad
byte pin_column[COLUMN_NUM] = {11, 10, 13}; //connect to the column pinouts of the keypad

Keypad keypad = Keypad( makeKeymap(keys), pin_rows, pin_column, ROW_NUM, COLUMN_NUM );

void setup(){
  Serial.begin(9600);
  servo1.attach(A0);
  servo1.attach(A1);
  servo1.attach(A2);
  servo1.attach(A3);

  //IR Input
  pinMode(irPin1, INPUT);
  pinMode(irPin2, INPUT);
  pinMode(irPin3, INPUT);
  pinMode(irPin4, INPUT);



  //coinslot
  pinMode(coinSlot, INPUT_PULLUP);


  lcd.init();
  lcd.clear();
  lcd.backlight();
  lcd.begin(16,2);

    lcd.clear();
    lcd.print("Vending Machine");
    lcd.setCursor(0,1);
    lcd.print("~INSERT COIN!~");
    delay(1000);
  

}

void loop(){

  
    displayItem();
  
    


}

void displayLCD(){
    lcd.clear();
    lcd.print("Vending Machine");
    lcd.setCursor(0,1);
    lcd.print("~INSERT COIN!~");
    delay(1000);

    lcd.clear();
    lcd.print("Vending Machine");
    lcd.setCursor(1,1);
    lcd.print("P1 P5 P10 P20");
    delay(1000);
  

}

void displayDeliver(){
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Vending Machine");
    lcd.setCursor(0,1);
    lcd.print("Delivering...");
}

void displayCoinAccepted(){
  
    lcd.setCursor(0,1);
    lcd.print("Coin Accepted");
    delay(2000);
    lcd.clear();
    lcd.print("Select an Item");
}

void displayItemDelivered(){
    lcd.clear();
    lcd.print("Item Delivered");
    delay(3000);

     lcd.clear();
    lcd.print("Vending Machine");
    lcd.setCursor(0,1);
    lcd.print("~INSERT COIN!~");
    delay(5000);

}


void displayItem(){
char key = keypad.getKey();
int state1 = digitalRead(irPin1);
int state2 = digitalRead(irPin2);
int state3 = digitalRead(irPin3);
int state4 = digitalRead(irPin4);


//coinslot code
coinSlotStatus = digitalRead(coinSlot);
delay(20);



 if (coinSlotStatus == false) {
     pulse += 1;  
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Credit:");
    lcd.print(pulse);
    delay(50);
    }
      if(key == '1') {
        if(pulse >= 6){
        servo1.write(180);
       delay(15);
       displayDeliver();
       pulse = 0;
        }else {
          lcd.clear();
          lcd.print("Insufficient Bal");
          delay(2000);
          lcd.clear();
          lcd.setCursor(0,0);
          lcd.print("Credit:");  
          lcd.print(pulse);
          delay(50);
         }
     
     }else if(key == '2') {
         if(pulse >= 12){
       servo2.write(180);
       delay(15);
       displayDeliver();
       pulse = 0;
         } else {
          lcd.clear();
          lcd.print("Insufficient Bal");
          delay(2000);
          lcd.clear();
          lcd.setCursor(0,0);
          lcd.print("Credit:");  
          lcd.print(pulse);
          delay(50);
         }
     }else if(key == '3') {
       if(pulse >= 5){
       servo3.write(180);
       delay(15);
       displayDeliver();
       pulse = 0;
      }else {
          lcd.clear();
          lcd.print("Insufficient Bal");
          delay(2000);
          lcd.clear();
          lcd.setCursor(0,0);
          lcd.print("Credit:");  
          lcd.print(pulse);
          delay(50);
         }

     }else if(key == '4') {
       if(pulse >= 9){
       servo4.write(180);
       delay(15);
       displayDeliver();
       pulse = 0;
      }else {
          lcd.clear();
          lcd.print("Insufficient Bal");
          delay(2000);
          lcd.clear();
          lcd.setCursor(0,0);
          lcd.print("Credit:");  
          lcd.print(pulse);
          delay(50);
         }
     }
    else if (state1 == LOW) {
      servo1.write(90);
      delay(15);
      displayItemDelivered();
    } else if(state2 == LOW){
      servo2.write(90);
      delay(15);
      displayItemDelivered();
    } else if(state3 == LOW){
      servo3.write(90);
      delay(15);
      displayItemDelivered();
    } else if(state4 == LOW){
      servo4.write(90);
      delay(15);
      displayItemDelivered();
    } 
 

  
  
   } 
   /*else if(coinSlotStatus == true){
    if(key == '1' || key =='2' || key == '3' || key =='4'){
      
    }*/
 



