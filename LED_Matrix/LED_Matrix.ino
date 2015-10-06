/* Made numbers for the matrix
 * Starting clock code soon (make it loop through 00:00 - 99:99 in a short time span)
 * Data being sent to registers are 48 Bits or 6 Bytes, 1 Byte for row and 5 for columns
 * Data transmitted must be in the order of Col4, Col3, Col2, Col1, Col0, Rows (last shift is first register)
 * Data transmitted must be inverted for Col0-4 (since we need to drive the ones we want on LOW for GND
 * wrote numbers[][] as if it would be driven HIGH for my own sanity
 */

byte row[8]         =  {B00000001, B00000010, B00000100, B00001000, B00010000, B00100000, B01000000, B10000000};  // Layer activation
byte colon[8]       =  {    B0000,     B0110,     B0110,     B0000,     B0000,     B0110,     B0110,     B0000};  // :
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
                               

int latchPin = 8;  //Pin connected to ST_CP of 74HC595
int clockPin = 12; //Pin connected to SH_CP of 74HC595
int dataPin = 11;  //Pin connected to DS of 74HC595
int counter = 0; // 0 - 9999


void setup() {
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
  digitalWrite(latchPin, HIGH);

}

void loop() {
  if(counter > 9999)
    counter = 0;  
  int digits[4]; // Digits in time 01:23
  digits[0] = counter/1000;
  digits[1] = (counter/100)%10;
  digits[2] = (counter/10)%10;
  digits[3] = counter%10;
  
  long int timer = millis();
  
  while(millis() < timer + 10){
    for(int i = 0; i < 8; i++){
      byte data[6]; // 0 - Rows; 5 - Col4
      byte temp = 0;
      // Compute the row data
      data[0] = row[i];
      
      temp = numbers[digits[0]][i] >> 1;
      data[1] = ~temp;
      
      temp = 0;
      temp = numbers[digits[0]][i] << 7;
      temp |= numbers[digits[1]][i] >> 2;
      data[2] = ~temp;
      
      temp = 0;
      temp = numbers[digits[1]][i] << 6;
      temp |= colon[i] << 2;
      temp |= numbers[digits[2]][i] >> 6;
      data[3] = ~temp;
      
      temp = 0;
      temp = numbers[digits[2]][i] << 2;
      temp |= numbers[digits[3]][i] >> 7;
      data[4] = ~temp;
      
      temp = 0;
      temp = numbers[digits[3]][i] << 1;
      data[5] = ~temp;
      
      digitalWrite(latchPin, LOW);
      shiftOut(dataPin, clockPin, LSBFIRST, data[5]);
      shiftOut(dataPin, clockPin, LSBFIRST, data[4]); 
      shiftOut(dataPin, clockPin, LSBFIRST, data[3]); 
      shiftOut(dataPin, clockPin, LSBFIRST, data[2]); 
      shiftOut(dataPin, clockPin, LSBFIRST, data[1]); 
      shiftOut(dataPin, clockPin, LSBFIRST, data[0]);  
      digitalWrite(latchPin, HIGH);
    }
  }  
  counter++;
}
