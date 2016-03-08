//int lastTime = 0;
int ledState = LOW;
int buttonState;
int lastButtonState = LOW;
int flag=0;
long lastDebounceTime = 0;
long debounceDelay = 20;
int speakerPin = 1;
 
int length = 29; // the number of notes
char notes[] = "ddedggFddedaagddDbgFeCCbgaag "; // a space represents a rest
int beats[] = { 1, 1, 2, 
2, 1, 1, 4, 1, 1, 2, 2, 1, 1, 4, 1, 1, 2, 2, 2, 2, 4, 1, 1, 2, 2, 1, 1, 4, 4 };
int tempo = 150;
void playTone(int tone, int duration) {
  for (long i = 0; i < duration * 1000L; i += tone * 2) {
    digitalWrite(speakerPin, HIGH);
    delayMicroseconds(tone);
    digitalWrite(speakerPin, LOW);
    delayMicroseconds(tone);
  }
}
 
void playNote(char note, int duration) {
  char names[] = { 'c', 'd', 'e', 'f', 'F', 'g', 'a', 'b', 'C','D' };
  int tones[] = { 1915, 1700, 1519, 1432,1351, 1275, 1136, 1014, 956, 851 };
  
  // play the tone corresponding to the note name
  for (int i = 0; i < 8; i++) {
    if (names[i] == note) {
      playTone(tones[i], duration);
    }
  }
}
void setup() {
  pinMode(3, INPUT);
  pinMode(2, OUTPUT);
  digitalWrite(2, ledState);
  pinMode(speakerPin, OUTPUT);
}
void loop() {
  int reading = digitalRead(3);
  if (reading != lastButtonState) {
    lastDebounceTime = millis();
  }
  if ((millis() - lastDebounceTime) > debounceDelay) {
      buttonState = reading;
      if (buttonState == HIGH) {
         digitalWrite(2, HIGH);
         int millisend = 0;
         millisend = millis();
         for (int i = 0; i < length; i++) {
           if(millisend - millis() > 20){
              if(digitalRead(2)){
                 digitalWrite(2, LOW);
              }else{
                 digitalWrite(2, HIGH);
              }
             millisend = millis();
           }
          if (notes[i] == ' ') {
            delay(beats[i] * tempo); // rest
          } else {
            playNote(notes[i], beats[i] * tempo);
          }
          delay(tempo / 2); 
        }        
         digitalWrite(2, LOW);
      }
  }
  lastButtonState = reading;
}
 
