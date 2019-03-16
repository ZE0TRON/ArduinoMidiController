#include <MIDI.h>


MIDI_CREATE_DEFAULT_INSTANCE();

int val = 0;
int prevVal =0;
int bankNo = 0;
static const unsigned numberOfBanks = 3;
static const int bankPin = 2;
static const int knobPin = 2;


void setup()
{
  pinMode(2,     INPUT);
  MIDI.begin();
  Serial.begin(115200);
}
void readButtons(){
  if (digitalRead(bankPin) == HIGH) {
    bankNo= (bankNo+1) % numberOfBanks ;
    delay(100);
  }
}
void readPot() {
  val = analogRead(knobPin);
  if(val<prevVal-10 || val> prevVal+10) {
    MIDI.sendControlChange(65+bankNo,val/8,1);
    prevVal=val;
    delay(20);
  }
}
void loop()
{
    readPot();
    readButtons();
    delay(20);
    MIDI.read();
}
