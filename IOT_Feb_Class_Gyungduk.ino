/*
	# Input Output Things
	- by SeungBum Kim <picxenk@gmail.com>
	- Document : http://bit.ly/InputOutputThings
	- Artistic License 2.0  http://choosealicense.com/licenses/artistic-2.0/


	# IOT Hello Things
	- Things say HI! with LED	
*/
#include "pitches.h"

int digitalInput = 3;
int digitalOutput = 2;
int analogInput = A2;
int analogOutput = 1;
//int digitalOutput = 13; //arduino Test
//int analogOutput = 8;//arduino Test

float unit = 0.1; // morse code unit
int noteDuration = 100;
int noteDelay = 20;
int iotSong[] = {NOTE_C3, NOTE_D3, NOTE_E3, NOTE_F3, NOTE_G3, NOTE_A3, NOTE_B3};
int melody[] = {
  NOTE_C4, NOTE_G3, NOTE_G3, NOTE_A3, NOTE_G3, 0, NOTE_B3, NOTE_C4
};
int noteDurations[] = {
  4, 8, 8, 4, 4, 4, 4, 4
};
int notelength= 9;
int beats[]={2,1,1,2,4,2,2,2};
char notes[]="CggagBC ";
int tempo=150;

void playTone(int tone, int duration) {
  for (long i = 0; i < duration * 1000L; i += tone * 2) {
    digitalWrite(analogOutput, HIGH);
    delayMicroseconds(tone);
    digitalWrite(analogOutput, LOW);
    delayMicroseconds(tone);
  }
}
void playNote (char note, int duration){
   char names[] = { 'c', 'd', 'e', 'f', 'g', 'a', 'B', 'C' };
   int tones[] = { 1908, 1701, 1515, 1433, 1275, 1136, 1014, 956 };
  
  for(int i = 0; i<8 ; i++){
    if(names[i]==note){
      playTone(tones[i],duration);
      
    }
  }
}

void setup() {                
  pinMode(digitalInput, INPUT_PULLUP);
  pinMode(digitalOutput, OUTPUT);
  pinMode(analogOutput, OUTPUT);
  //Serial.begin(9600);//arduino Test
}


// ##########################  MAIN  ##########################
void loop() {
  if(readLight()<90) {
	on (0);
 for (int i=0; i< notelength; i++){
  playNote (notes[i], beats[i]*tempo);}
	delay(tempo/2);
 } else {
  off(0); 
 }
 //int sensorValue = analogRead(A2);
 //Serial.println(readLight());
 //delay(1); //arduino Test
}


// ########################## BLACK BOX ##########################
// ===== IOT Commands =====

// Digital Output
void blink(float sec) {
	on(sec);
	off(sec);
}



void on(float sec) {
	digitalWrite(digitalOutput, HIGH);
	wait(sec);
}

void off(float sec) {
	digitalWrite(digitalOutput, LOW);
	wait(sec);
}

// Digital Input
boolean isOn() {
	if (digitalRead(digitalInput) == LOW)
		return true;
	else
		return false;
}

boolean isOff() {
	if (digitalRead(digitalInput) == HIGH)
		return true;
	else
		return false;
}


// Analog Input
int readValue() {
	return map(analogRead(analogInput), 0, 1023, 0, 255);
}

int readLight() {
  int light;
  light = analogRead(analogInput);
  light = calibrateLightSensor(light);
  return map(light, 0, 1023, 0, 255);
}

int calibrateLightSensor(int light) {
    int mid = 600;
    int mid2 = 900;
    if ( light < mid) {
        light = int(round((40.0/mid)*light));
    } else if (light < mid2) {
        light = int(round((mid2-40)/(mid2-float(mid))* light) - 1680);
    }
    light = constrain(light, 0, 1023);    
    return light;
}


// Analog Output
void writeValue(int value) {
	analogWrite(analogOutput, value);
}

void slowOn(float waitSec) {
	for (int i=0; i<=255; i=i+5) {
		writeValue(i);
		wait(waitSec);
	}
}

void slowOff(float waitSec) {
	for (int i=255; i>=0; i=i-5) {
		writeValue(i);
		wait(waitSec);
	}	
}


 //승범샘 코드
/*void playTone(int value) {
	tone(analogOutput, value, noteDuration);
	delay(noteDelay);
	noTone(analogOutput);
}*/

void playOneTone(int value) {
	tone(analogOutput, value, 1000/4);
	delay(1000/4*1.3);
	noTone(analogOutput);
}

void playHalfTone(int value) {
	tone(analogOutput, value, 1000/8);
	delay(1000/8*1.3);
	noTone(analogOutput);
}

/*void playTones(int song[], int size) {
	for (int i=0; i<size; i++) {
		playOneTone(song[i]);
	}
	
} //승범샘 코드
/*void playTones(int song[], int noteDurations[], int size) {
      for(int i=0; i<size;i++){
        int noteDuration = 1000 / noteDurations[i]*1.30;
        tone(analogOutput, song[i], noteDuration);
        delay(noteDuration);
        noTone(analogOutput);
      }
  
}*///내가만든코드


// Common
void wait(float sec) {
	delay(sec*1000);
}


// ===== Morse Code Commands =====
// http://en.wikipedia.org/wiki/Morse_code
void dot() {
	on(unit);
	off(unit);
}

void dash() {
	on(3*unit);
	off(unit);
}

void lspace() {
	wait(3*unit);
}

void wspace() {
	wait(7*unit);
}
