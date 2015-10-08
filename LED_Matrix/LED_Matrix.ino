/* Made numbers for the matrix
 * Starting clock code soon (make it loop through 00:00 - 99:99 in a short time span)
 * Data being sent to registers are 48 Bits or 6 Bytes, 1 Byte for row and 5 for columns
 * Data transmitted must be in the order of Col4, Col3, Col2, Col1, Col0, Rows (last shift is first register)
 * Data transmitted must be inverted for Col0-4 (since we need to drive the ones we want on LOW for GND
 * wrote numbers[][] as if it would be driven HIGH for my own sanity
 */

 

byte row[8]         =  {B00000001, B00000010, B00000100, B00001000, B00010000, B00100000, B01000000, B10000000};  // Layer activation
byte colon[8]       =  {B00000000, B00011000, B00011000, B00000000, B00000000, B00011000, B00011000, B00000000};  // :
byte numbers[10][8] = {{B01111110, B11111111, B11100111, B11100111, B11100111, B11100111, B11111111, B01111110},  // 0
                       {B00001110, B00000111, B00000111, B00000111, B00000111, B00000111, B00000111, B00000111},  // 1
                       {B11111110, B11111111, B00000111, B01111111, B11111110, B11100000, B11111111, B11111111},  // 2
                       {B11111110, B11111111, B00000111, B00111110, B00111110, B00000111, B11111111, B11111110},  // 3
                       {B11100111, B11100111, B11100111, B11111111, B01111111, B00000111, B00000111, B00000111},  // 4
                       {B11111111, B11111111, B11110000, B11111110, B01111111, B00000111, B11111111, B11111110},  // 5
                       {B00111110, B01111110, B11100000, B11111110, B11111111, B11100111, B11100111, B01111110},  // 6
                       {B01111111, B01111111, B00000111, B00001111, B00011110, B00111100, B01111000, B01110000},  // 7
                       {B01111110, B11100111, B11100111, B01111110, B01111110, B11100111, B11100111, B01111110},  // 8
                       {B01111110, B11100111, B11100111, B11111111, B01111111, B00000111, B01111110, B01111100}}; // 9
byte alphabet[26][8] ={{B00001110, B00010001, B00010001, B00011111, B00010001, B00010001, B00010001, B00010001},  // A
                       {B00011110, B00010001, B00010001, B00011110, B00010001, B00010001, B00010001, B00011110},  // B
                       {B00001111, B00010000, B00010000, B00010000, B00010000, B00010000, B00010000, B00001111},  // C
                       {B00011110, B00010001, B00010001, B00010001, B00010001, B00010001, B00010001, B00011110},  // D
                       {B00011111, B00010000, B00010000, B00011110, B00010000, B00010000, B00010000, B00011111},  // E
                       {B00011111, B00010000, B00010000, B00011110, B00010000, B00010000, B00010000, B00010000},  // F
                       {B00001110, B00010001, B00010000, B00010000, B00010111, B00010001, B00010001, B00001110},  // G
                       {B00010001, B00010001, B00010001, B00011111, B00010001, B00010001, B00010001, B00010001},  // H
                       {B00011111, B00000100, B00000100, B00000100, B00000100, B00000100, B00000100, B00011111},  // I
                       {B00011111, B00000010, B00000010, B00000010, B00000010, B00000010, B00010010, B00011110},  // J
                       {B00010001, B00010010, B00010100, B00011000, B00011000, B00010100, B00010010, B00010001},  // K
                       {B00010000, B00010000, B00010000, B00010000, B00010000, B00010000, B00010000, B00011111},  // L
                       {B00010001, B00011011, B00010101, B00010001, B00010001, B00010001, B00010001, B00010001},  // M
                       {B00010001, B00010001, B00011001, B00010101, B00010011, B00010001, B00010001, B00010001},  // N
                       {B00001110, B00010001, B00010001, B00010001, B00010001, B00010001, B00010001, B00001110},  // O
                       {B00011110, B00010001, B00010001, B00011110, B00010000, B00010000, B00010000, B00010000},  // P
                       {B00001110, B00010001, B00010001, B00010001, B00010001, B00010101, B00010010, B00001101},  // Q
                       {B00011110, B00010001, B00010001, B00011110, B00011000, B00010100, B00010010, B00010001},  // R
                       {B00001111, B00010000, B00010000, B00001110, B00000001, B00000001, B00000001, B00011110},  // S
                       {B00011111, B00000100, B00000100, B00000100, B00000100, B00000100, B00000100, B00000100},  // T
                       {B00010001, B00010001, B00010001, B00010001, B00010001, B00010001, B00010001, B00001110},  // U
                       {B00010001, B00010001, B00010001, B00010001, B00001010, B00001010, B00001010, B00000100},  // V
                       {B00010001, B00010001, B00010001, B00010001, B00010101, B00010101, B00010101, B00001010},  // W
                       {B00010001, B00001010, B00001010, B00000100, B00001010, B00001010, B00001010, B00010001},  // X
                       {B00010001, B00010001, B00001010, B00001010, B00000100, B00000100, B00000100, B00000100},  // Y
                       {B00011111, B00000001, B00000010, B00000100, B00001000, B00010000, B00010000, B00011111}}; // Z
int latchPin = 8;  //Pin connected to ST_CP of 74HC595
int clockPin = 12; //Pin connected to SH_CP of 74HC595
int dataPin = 11;  //Pin connected to DS of 74HC595
int counter = 0; // 0 - 9999
int steps = 0;
int option = 1;
long int timer;
boolean flag[8] = {1,1,1,1,1,1,1};
char msg[256]; // HELLO WORLD
String message = "YOU ARE THE REAL MVP       ";
byte data[6][8]; // 0 - Rows; 5 - Col4
byte temp[5], ch;

void setup() {
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
  digitalWrite(latchPin, HIGH);
  message.toCharArray(msg, 256);
}

void loop() {
  if(option == 0){
    if(counter > 9999)
      counter = 0;  
    int digits[4]; // Digits in time 01:23
    digits[0] = counter/1000;
    digits[1] = (counter/100)%10;
    digits[2] = (counter/10)%10;
    digits[3] = counter%10;
    
    timer = millis();
    
    while(millis() < timer + 50){
      for(int i = 0; i < 8; i++){
        byte data[6][0]; // 0 - Rows; 5 - Col4
        byte temp = 0;
        // Compute the row data
        data[0][0] = row[i];
        
        temp = numbers[digits[0]][i] >> 1;
        data[1][0] = temp;
        
        temp = 0;
        temp = numbers[digits[0]][i] << 7;
        temp |= numbers[digits[1]][i] >> 2;
        data[2][0] = temp;
        
        temp = 0;
        temp = numbers[digits[1]][i] << 6;
        temp |= colon[i];
        temp |= numbers[digits[2]][i] >> 6;
        data[3][0] = temp;
        
        temp = 0;
        temp = numbers[digits[2]][i] << 2;
        temp |= numbers[digits[3]][i] >> 7;
        data[4][0] = temp;
        
        temp = 0;
        temp = numbers[digits[3]][i] << 1;
        data[5][0] = temp;
        
        digitalWrite(latchPin, LOW);
        shiftOut(dataPin, clockPin, LSBFIRST, ~data[5][0]);
        shiftOut(dataPin, clockPin, LSBFIRST, ~data[4][0]); 
        shiftOut(dataPin, clockPin, LSBFIRST, ~data[3][0]); 
        shiftOut(dataPin, clockPin, LSBFIRST, ~data[2][0]); 
        shiftOut(dataPin, clockPin, LSBFIRST, ~data[1][0]); 
        shiftOut(dataPin, clockPin, LSBFIRST, data[0][0]);  
        digitalWrite(latchPin, HIGH);
      }
    }  
    counter++;
  }else if(option == 1){
    timer = millis();
  
    flag[0] = 1;
    flag[1] = 1;
    flag[2] = 1;
    flag[3] = 1;
    flag[4] = 1;
    flag[5] = 1;
    flag[6] = 1;
    flag[7] = 1;
    
    while(millis() < timer + 125){ //controlles stretch
      for(int i = 0; i < 8; i++){
        ch = 0;
        if(steps % 6 != 5){  
          int pos = 4 - (steps % 6);
          if(msg[(steps/6)%message.length()] != ' '){
            ch = alphabet[msg[(steps/6)%message.length()] - 'A'][i];
            ch >>= pos;
            ch &= 1;
          }else{
            ch = 0;
          }
        }
        if(flag[i]){
          flag[i] = 0;
          temp[0] = data[1][i];
          temp[1] = data[2][i];
          temp[2] = data[3][i];
          temp[3] = data[4][i];
          temp[4] = data[5][i];
          
          data[1][i] <<= 1;
          data[2][i] <<= 1;
          data[3][i] <<= 1;
          data[4][i] <<= 1;
          data[5][i] <<= 1;
          
          data[5][i] |= ch;
          temp[4] >>= 7;
          data[4][i] |= temp[4];
          temp[3] >>= 7;
          data[3][i] |= temp[3];
          temp[2] >>= 7;
          data[2][i] |= temp[2];
          temp[1] >>= 7;
          data[1][i] |= temp[1];
        }
   
        digitalWrite(latchPin, LOW);
        shiftOut(dataPin, clockPin, LSBFIRST, ~data[5][i]);
        shiftOut(dataPin, clockPin, LSBFIRST, ~data[4][i]); 
        shiftOut(dataPin, clockPin, LSBFIRST, ~data[3][i]); 
        shiftOut(dataPin, clockPin, LSBFIRST, ~data[2][i]); 
        shiftOut(dataPin, clockPin, LSBFIRST, ~data[1][i]); 
        shiftOut(dataPin, clockPin, LSBFIRST, row[i]);  
        digitalWrite(latchPin, HIGH);
        
      } 
    }
    steps++;
  }else if(option == 2){
    long timer = millis();
    for(int i = 0; i < 8; i++){
      if((millis() < timer + 500) && i == 0){
        int rand = millis() % 40;
        if(0 <= rand < 8){
          data[1][0] |=  1 << rand;
        }else if(8 <= rand < 16){
          rand %= 8;
          data[2][0] |=  1 << rand;
        }else if(16 <= rand < 24){
          rand %= 8;
          data[3][0] |=  1 << rand;
        }else if(24 <= rand < 32){
          rand %= 8;
          data[4][0] |=  1 << rand;
        }else{
          rand %= 8;
          data[5][0] |=  1 << rand;
        }
      }
      if(i != 0){
        
      }
      
      
      digitalWrite(latchPin, LOW);
      shiftOut(dataPin, clockPin, LSBFIRST, ~data[5][i]);
      shiftOut(dataPin, clockPin, LSBFIRST, ~data[4][i]); 
      shiftOut(dataPin, clockPin, LSBFIRST, ~data[3][i]); 
      shiftOut(dataPin, clockPin, LSBFIRST, ~data[2][i]); 
      shiftOut(dataPin, clockPin, LSBFIRST, ~data[1][i]); 
      shiftOut(dataPin, clockPin, LSBFIRST, row[i]);  
      digitalWrite(latchPin, HIGH);
    }
  }
}
