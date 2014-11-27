#include <LiquidCrystal.h>

int sensorvalue = 0;          // variable for reading the IR sensor status
int triggerState = 0;         // variable for reading the pushbutton status

int health = 100;             // variable for user health

int trigger = 0;              // variable for delaying the trigger
int hit = 0;              // variable for delaying the possibility to get hit
int countdown = 0;            // variable for countdown when dead


const int sensorPin = 0;     // the number of the sensor pin
const int buttonPin = 5;     // the number of the pushbutton pin
const int ledPin =  7;      // the number of the LED pin

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);   // initialize the library with the numbers of the interface pins


// SETUP
void setup() {

  pinMode(sensorPin, INPUT);     // initialize the sensor pin as an input
  pinMode(buttonPin, INPUT);     // initialize the pushbutton pin as an input

  pinMode(ledPin, OUTPUT);      // initialize the LED pin as an output


 lcd.begin(16, 2);  // set up the LCD's number of columns and rows
 lcd.setCursor(4, 0);
 lcd.print("INVITA");   // Print a message to the LCD.
 lcd.setCursor(0, 1);
 lcd.print("welcomes you!");
 delay(500);
 }

// MAIN LOOP
void loop() {
 sensorvalue =analogRead(sensorPin);       // read the state of the sensor value:
 triggerState = analogRead(buttonPin);     // read the state of the pushbutton value

 // set the cursor to column 0, line 0
 // (note: line 1 is the second row, since counting begins with 0):
 lcd.setCursor(0, 0);

 // When hit
 if ((sensorvalue < 15) && (hit < 3)) { hit = 10; health= health-20;}  // if hit and if hit delay is lower than 3, hit delay will be 10 and health will drop with 20
 if (hit > 1) {lcd.print("you're hit!"); hit = hit - 1;}        // print geraakt

// when dead
 if (health <= 0) {countdown = 20;}               // countdown naar 30 seconden
 while (health <= 0)                              // loop while health is lower or equal to 0
 {
  lcd.clear();                                        // clear LCD
  lcd.setCursor(0,0); lcd.print("Deactivated!");
  lcd.setCursor(0,1); lcd.print("Wait");
  lcd.setCursor(5,1); lcd.print(countdown);
  lcd.setCursor(7,1); lcd.print("sec");

  delay(1000);
  countdown--;                                    // int countdown minus 1
  if (countdown <= 0) {health=100;}                // if countdown reaches 0 reset the health to 100 and exit the while loop
}

//schieten:
 if ((triggerState >= 1023) && (trigger <= 0)) // check if the pushbutton is pressed and if the trigger delay is finished
    {digitalWrite(ledPin, HIGH); trigger = 15;}  // turn LED on and set trigger delay to 5
 if (trigger > 0) {trigger = trigger - 1;}     // if trigger delay is bigger than 0  reduce the trigger delay by 1




 // health laten zien
 if (health > 1) {lcd.setCursor(0, 1);lcd.print("health="); lcd.setCursor(7, 1);lcd.print(health);lcd.setCursor(10, 1);lcd.print("%");}

 // sensor waarden
 lcd.setCursor(12, 0);
 lcd.print(triggerState);


delay(100);   //  vertraging;

lcd.clear();   // clear the lcd
digitalWrite(ledPin, LOW);   // turn LED off


}
