#include <LiquidCrystal.h>
#include "pitches.h"

// notes in the melody:
int melody[] = {
  NOTE_DS8, NOTE_DS8,NOTE_DS8, NOTE_DS8, NOTE_DS8,0, NOTE_DS8, NOTE_DS8};

// note durations: 4 = quarter note, 8 = eighth note, etc.:
int noteDurations[] = {
  4, 8, 8, 4,4,4,4,4 };

int sensorValue = 0;          // variable for reading the IR sensor status
int triggerState = 0;         // variable for reading the pushbutton status

int health = 100;             // variable for user health
int ammo = 10;                 // variable for user ammo

int triggerDelay = 0;              // variable for delaying the trigger
int hitDelay = 0;              // variable for delaying the possibility to get hit
int ammoDelay = 0;             // variable for ammo reload
int ammoTrigger = 0;           // trigger to give new ammo
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
  delay(1000);
}

// MAIN LOOP
void loop() {
  sensorValue =analogRead(sensorPin);       // read the state of the sensor value:
  triggerState = analogRead(buttonPin);     // read the state of the pushbutton value

  // set the cursor to column 0, line 0
  // (note: line 1 is the second row, since counting begins with 0):
  lcd.setCursor(0, 0);

  // When hit
  if ((sensorValue < 15) && (hitDelay < 3)) {
     hitDelay = 10; health= health-20;}  // if hit and if hit delay is lower than 3, hit delay will be 10 and health will drop with 20
  if (hitDelay > 1) {
    lcd.print("you're hit!"); hitDelay = hitDelay - 1;}        // print geraakt

  // when dead
  if (health <= 0) {countdown = 15; // countdown naar 30 seconden
      // iterate over the notes of the melody:
      for (int thisNote = 0; thisNote < 8; thisNote++) {

      // to calculate the note duration, take one second
      // divided by the note type.
      //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
      int noteDuration = 1000/noteDurations[thisNote];
      tone(8, melody[thisNote],noteDuration);

      // to distinguish the notes, set a minimum time between them.
      // the note's duration + 30% seems to work well:
      int pauseBetweenNotes = noteDuration * 1.30;
      delay(pauseBetweenNotes);
      // stop the tone playing:
      noTone(8);}
    }

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
  if ((triggerState >= 1023) && (triggerDelay <= 0) && (ammo > 0)) // check if the pushbutton is pressed and if the trigger delay is finished
    {digitalWrite(ledPin, HIGH); triggerDelay = 20; ammo = ammo -1;}  // turn LED on and set trigger delay to 5
  if (triggerDelay > 0) {triggerDelay = triggerDelay - 1;}     // if trigger delay is bigger than 0  reduce the trigger delay by 1

  //ammo:
  if ((ammo == 0) && (ammoDelay == 0) && (ammoTrigger == 0)){ammoDelay = 250;ammoTrigger = 1;}
  if (ammoDelay > 0){ammoDelay = ammoDelay - 1;}
  if ((ammo == 0) && (ammoDelay == 0) && (ammoTrigger == 1 )) {ammo = 10; ammoTrigger = 0;}


  // health laten zien
  if (health > 1) {lcd.setCursor(0, 1);lcd.print("H="); lcd.setCursor(2, 1);lcd.print(health);lcd.setCursor(5, 1);lcd.print("%");}

  //ammo print
  if (ammo > 0) {lcd.setCursor(8, 1);lcd.print("A=");lcd.setCursor(10, 1);lcd.print(ammo);}
  if (ammo == 0) {lcd.setCursor(8, 1);lcd.print("R.L.");lcd.setCursor(12, 1);lcd.print(ammoDelay);}


  delay(10);   //  vertraging;

  lcd.clear();   // clear the lcd
  digitalWrite(ledPin, LOW);   // turn LED off


}
