#include <SimpleMessageSystem.h>
#include <digitalWriteFast.h>
#define NUMP 10
#define NUMLED 90

boolean offgate = true;
int ct = 0;
int nummsg;
int pins[NUMP] = {2, 3, 4, 5, 6, 7, 8, 9, 10, 16};
int lednum[NUMLED][2] = {
  {5, 9}, {9, 8}, {9, 7}, {9, 6}, {9, 1}, {9, 5}, {9, 3}, {9, 2}, {9, 0}, {9, 4},
  {5, 8}, {8, 9}, {8, 7}, {8, 1}, {8, 6}, {8, 0}, {8, 2}, {8, 3}, {8, 4}, {8, 5},
  {5, 7}, {7, 8}, {7, 9}, {7, 6}, {7, 1}, {7, 2}, {7, 3}, {7, 0}, {7, 4}, {7, 5},
  {5, 6}, {6, 2}, {6, 8}, {6, 9}, {6, 7}, {6, 1}, {6, 5}, {6, 4}, {6, 3}, {6, 0},
  {5, 4}, {4, 6}, {4, 8}, {4, 7}, {4, 9}, {4, 3}, {4, 2}, {4, 1}, {4, 0}, {4, 5},
  {5, 3}, {3, 6}, {3, 4}, {3, 8}, {3, 7}, {3, 9}, {3, 1}, {3, 2}, {3, 5}, {3, 0},
  {5, 2}, {2, 4}, {2, 6}, {2, 7}, {2, 8}, {2, 3}, {2, 9}, {2, 1}, {2, 0}, {2, 5},
  {5, 1}, {1, 7}, {1, 6}, {1, 4}, {1, 3}, {1, 8}, {1, 0}, {1, 9}, {1, 2}, {1, 5},
  {5, 0}, {0, 3}, {0, 2}, {0, 1}, {0, 4}, {0, 7}, {0, 8}, {0, 6}, {0, 9}, {0, 5}
};
int pinstate[NUMLED];

void setup() {
  Serial.begin(9600);
  for (int i = 0; i < NUMLED; i++) pinstate[i] = 0;
  for (int i = 0; i < NUMP; i++) pinModeFast(pins[i], INPUT);
}

void loop() {
  //sms code from supercollider (nummsgs, lednum, ledstate ... )
  nummsg = 0;
  if (messageBuild() > 0) { // Checks to see if the message is complete and erases any previous messages
       nummsg =  messageGetInt();
      for(int i=0;i<nummsg;i++){
        pinstate[messageGetInt()] = messageGetInt();
      }
  }
  ct = 0; //so loop doesn't repeat alloff() func, just an efficency
  for (int i = 0; i < NUMLED; i++) {
    if (pinstate[i] == 1) {
      alloff();
      on(lednum[i][0], lednum[i][1]);
      ct = ct + 1; //so loop doesn't repeat alloff() func, just an efficency
      offgate = true; //so loop doesn't repeat alloff() func, just an efficency
      delayMicroseconds(100);
    }
  }
  if (ct == 0) if (offgate) {
      alloff();
      offgate = false;
    }
}

void on(int x, int y) {
  pinModeFast(pins[x], OUTPUT);
  digitalWriteFast(pins[x], HIGH);
  pinModeFast(pins[y], OUTPUT);
  digitalWriteFast(pins[y], LOW);

}

void alloff() {
  for (int i = 0; i < NUMP; i++) pinModeFast(pins[i], INPUT);
}


