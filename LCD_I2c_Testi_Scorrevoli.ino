// LCD
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

#define I2C_ADDR 0x27 
#define BACKLIGHT_PIN 3
#define En_pin 2
#define Rw_pin 1
#define Rs_pin 0
#define D4_pin 4
#define D5_pin 5
#define D6_pin 6
#define D7_pin 7

LiquidCrystal_I2C lcd(I2C_ADDR,En_pin,Rw_pin,Rs_pin,D4_pin,D5_pin,D6_pin,D7_pin);

#define colonne 16
#define righe 2

String TXT="Era piu' difficile di quel che credevo =) ma l'ho risolto";

int pos= 0, lung_str= TXT.length(), attesa=1000; // attesa 1s

unsigned long T, dT, T1, dT1;


// ultrasuoni 
#define trig 3
#define echo 4

String distanza ();

void setup() {
  lcd.begin(colonne, righe);
  lcd.setBacklightPin(BACKLIGHT_PIN,POSITIVE);
  lcd.setBacklight(HIGH);
 // metto degli spazi all'inizio della stringa per 
 // falsa iniziare dall'inizio del display
  for (byte i=0; i < colonne; i++){
    TXT=" " + TXT;
    }
  // Metto uno spazio dopo la stringa per visualizzarla tutta
  TXT + TXT+ " ";

  // ultrasuoni
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);

 // segno il tempo
 T=millis();
 T1=millis();
}

void loop () {
   //timer non bloccante
  dT = millis() - T;
  if (dT >= attesa){
 
      lcd.setCursor(0,0);
      // substring (i, f ) mi stampa la striga dall'indice "i" a "f"
      lcd.print (TXT.substring (pos, pos + colonne));
      pos += 1;
      // verifico di essere arrivato all'ultimo della stringa se è vero ricomincio
      if (pos > lung_str) pos = 0;   
      
    // Segno il tempo attuale
    T = millis();
    }

    dT1 = millis() - T1;
    if (dT1 >= 1000){
      lcd.setCursor (0,1);
      lcd.print ("                ");
      lcd.setCursor (0,1);
      lcd.print (distanza());
      T1 = millis();
    }
  }

String distanza (){
String str;

//porta bassa l'uscita del trigger
digitalWrite( trig, LOW );
//invia un impulso di 10microsec su trigger
digitalWrite( trig, HIGH );
delayMicroseconds( 10 );
digitalWrite( trig, LOW );
 
long durata = pulseIn( echo, HIGH );
 
long distanza = 0.034 * durata / 2;
 
Serial.print("distanza: ");
 
//dopo 38ms è fuori dalla portata del sensore
if( distanza> 38000 ){
str = "fuori portata";
}
else{ 
str= "Dist= " + (String)distanza + " cm";
}
return str;
}
