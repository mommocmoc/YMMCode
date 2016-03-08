//int lastTime = 0;
int ledState = LOW;
int buttonState;
int lastButtonState = LOW;
int flag=0;
long lastDebounceTime = 0;
long debounceDelay = 20;
int speakerPin = 1;
 
int length = 30; // the number of notes
char notes[] = "cdegggfefedcbcabcccfecccedcbc "; // a space represents a rest
int beats[] = { 2, 2, 6, 2, 2, 4, 2, 3, 4, 4, 4, 4, 2,13,2,2,4,4,4,2,9,2,2,2,4,2,6,4,16,8};
int tempo = 100;
void playTone(int tone, int duration) {
  for (long i = 0; i < duration * 1000L; i += tone * 2) {
    digitalWrite(speakerPin, HIGH);
    delayMicroseconds(tone);
    digitalWrite(speakerPin, LOW);
    delayMicroseconds(tone);
  }
  
}
/* 
#define NOTE_C3  131
#define NOTE_D3  147
#define NOTE_DS3 156
#define NOTE_E3  165
#define NOTE_F3  175
#define NOTE_FS3 185
#define NOTE_G3  196
#define NOTE_GS3 208
#define NOTE_A3  220
#define NOTE_AS3 233
#define NOTE_B3  247
#define NOTE_C4  262
#define NOTE_CS4 277
#define NOTE_D4  294
#define NOTE_DS4 311
#define NOTE_E4  330
#define NOTE_F4  349
#define NOTE_FS4 370
#define NOTE_G4  392
#define NOTE_GS4 415
#define NOTE_A4  440
#define NOTE_AS4 466
#define NOTE_B4  494
#define NOTE_C5  523
 */
void playNote(char note, int duration) {
  char names[] = {'a','b','c', 'd', 'e', 'f', 'F', 'g', 'A', 'B', 'C','D' };
  int tones[] = {2272,2024,1915, 1700, 1519, 1432,1351, 1275, 1136, 1014, 956, 851 };
  
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
 
