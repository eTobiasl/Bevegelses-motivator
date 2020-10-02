// Setter verdiene til komponenter på Arduinoen.
int knapp = 7;
int piezo = 9;
int lys = 3;
int pot = A5;

// Variabler for å holde rede på tiden ved reset.
unsigned long startMillis = 0;
unsigned long currentMillis;
unsigned long elapsedMillis;

//Toner
int e = 329.63;
int dSharp = 311.13;
int b = 246.94;
int d = 293.66;
int c = 261.63;
int a = 220.00;
int gSharp = 207.65;
int e3 = 164.81;
int c3 = 130.81;

//Melodier
int del1[9] = {e, dSharp, e, dSharp, e, b, d, c, a};
int del2[9] = {c3, e3, a, b, e3, gSharp, b, c, e3};
int del3[9] = {e, dSharp, e, dSharp, e, b, d, c, a};
int del4[8] = {c3, e3, a, b, e3, c, b, a};

//Diverse variabler for å holde rede på ulike funksjoner til prototypen.
int periode = 0;
unsigned long permap = 0;
boolean lyser = false;
int teller;
boolean status; //status brukes for aa sorge for at bare et steg spilles av gangen.
boolean signal = false;

void setup() {
//Setter Lys og Piezo til Output, tar inputt fra knappen.
pinMode(lys, OUTPUT);
pinMode(piezo, OUTPUT);
pinMode(knapp, INPUT);
//Serial for debugging.
Serial.begin(9600);
}

void loop() {
  //Oppdaterer tiden for denne perioden.
  elapsedMillis = (millis() - startMillis);

  //Leser fra potensiometeret og gjør verdien om til det samme som millis.
  periode = analogRead(pot);
  permap = map(periode, 0, 1023, 0, 60000);

  //Sjekker om perioden er over. Hvis ja, skru på lys og sett variabel
  //for å stoppe print i terminal.
  if (elapsedMillis > permap){
    digitalWrite(lys, HIGH);
    if(lyser == false){
      tone(piezo, 130.81, 250);
      }
    lyser = true;
  }

  //Printer i terminalen hvis klokka går. Når perioden er over stopper den.
  if(lyser == false){
    //Serial.print(elapsedMillis);
    //Serial.print("\n");
  } else {
    }

  //Spiller av lyd, skrur av lyset, resetter timeren.
  if (digitalRead(knapp) == HIGH){
    lyd();
    digitalWrite(lys, LOW);
    lyser = false;
    startMillis = millis();
  }
}

//Vi lagde en egen funksjon for lyd da den ble litt komplisert
//og uoversiktelig å ha i void() loop.
void lyd(){

   teller++;
   status = false;
   Serial.print(teller);

  if(teller == 1 && status == false){ //Hvis brukeren har 1 poeng
  tone(piezo, 130.81, 500); //Spiller av tone 1
    status = true;
    delay(1000); //Delay brukt for å få riktig tone lengde
  }
  
  else if(teller == 2 && status == false){ //Hvis brukeren har 2 poeng
    tone(piezo, 130.81); //Spiller av tone 1
    delay(400); //Delay brukt for å få riktig tone lengde
  tone(piezo, 164.81, 500); //Spiller tone 2
    status = true;
    delay(1000); //Delay brukt for å få riktig tone lengde
  }
  
  else if (teller == 3 && status == false){ //Hvis brukeren har 3 poeng
    tone(piezo, 130.81); //spiller tone 1
    delay(400); //Delay brukt for å få riktig tone lengde
  tone(piezo, 164.81); //spiller tone 2
    delay(400); //Delay brukt for å få riktig tone lengde
    tone(piezo, 196.00, 500);
    status = true; //spiller tone 3
    delay(1000); //Delay brukt for å få riktig tone lengde
  }
  
  else if (teller == 4 && status == false){ //Hvis brukeren har 4 poeng
      for (int i=0; i<sizeof del1/sizeof del1[0]; i++) { //For-lokke som spiller av del 1 av tonenen i melodien Fur Elise
      int note = del1[i];
      tone(piezo, note);
      if (i == 8){
        delay(800); //Delay brukt for å få riktig tone lengde
      } else{
      delay(400); //Delay brukt for å få riktig tone lengde
      }
    }
  
    for (int i=0; i<sizeof del2/sizeof del2[0]; i++) { //For-lokke som spiller av del 2 av tonenen i melodien Fur Elise
      int note = del2[i];
      tone(piezo, note);
      if (i == 3 || i == 7){
        delay(800); //Delay brukt for å få riktig tone lengde
      } else{
      delay(400); //Delay brukt for å få riktig tone lengde
      }
    }
  
    for (int i=0; i<sizeof del3/sizeof del3[0]; i++) { //For-lokke som spiller av del 3 av tonenen i melodien Fur Elise
      int note = del3[i];
      tone(piezo, note);
      if (i == 8){
        delay(800); //Delay brukt for å få riktig tone lengde
      } else{
      delay(400); //Delay brukt for å få riktig tone lengde
      }
    }
  
  for (int i=0; i<sizeof del4/sizeof del4[0]; i++) { //For-lokke som spiller av del 4 av tonenen i melodien Fur Elise
      int note = del4[i];
      if (i == 3){
        tone(piezo, note);
      delay(800); //Delay brukt for å få riktig tone lengde
      } 
      else if(i == 7){
        tone(piezo, note, 400);
      }
      else{
        tone(piezo, note);
      delay(400); //Delay brukt for å få riktig tone lengde
      }
    }
    status = true;
    teller = 0;
  }
}
