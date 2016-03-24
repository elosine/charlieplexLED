#include <SimpleMessageSystem.h>
#include <digitalWriteFast.h>
#define NUMP 10
#define NUMMSG 0

int lstate;
int msgx, msgy;
int pins[NUMP] = {2, 3, 4, 5, 6, 7, 8, 9, 10, 16};

void setup() {
  Serial.begin(9600);
  for (int i = 0; i < NUMP; i++) {
    pinModeFast(pins[i], INPUT)
  };
}

void loop() {
  //sms code from supercollider (nummsgs, lednum, ledstate)
  if (messageBuild() > 0) { // Checks to see if the message is complete and erases any previous messages
    //  NUMMSG =  messageGetInt();
    // for (int i = 0; i < nummsgs; i++) {
    lstate = messageGetInt();
    
    if (lstate == 1) {
      msgx = messageGetInt();
      msgy = messageGetInt();
      on(msgx, msgy);
      delayMicroseconds(100);
    }
    else {
      msgx = messageGetInt();
      msgy = messageGetInt();
      off(msgx, msgy);
    }
    
    //  }
  }
}

void on(int x, int y) {
  pinModeFast(pins[x], OUTPUT);
  digitalWriteFast(pins[x], HIGH);
  pinModeFast(pins[y], OUTPUT);
  digitalWriteFast(pins[y], LOW);

}

void off(int x, int y) {
  pinModeFast(pins[x], INPUT);
  pinModeFast(pins[y], INPUT);
}


