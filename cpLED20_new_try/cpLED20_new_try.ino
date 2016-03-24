#include <SimpleMessageSystem.h>
#include <digitalWriteFast.h>

#define A 7
#define B 8
#define C 9
#define D 10
#define E 16

#define PIN_CONFIG 0
#define PIN_STATE 1

#define LED_COUNT 20
#define LCT 20

int lst[LCT] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
int ledorder[LCT] = {18, 0, 4, 6, 12, 1, 2, 8, 14, 5, 3, 10, 16, 7, 9, 11, 13, 15, 17, 19};
int lednum;
int ledstate;
boolean ofg = false;
int ct = 0;

int matrix[LED_COUNT][2][5] = {
  //           PIN_CONFIG                              PIN_STATE
  //    A       B       C      D      E      FA      G      H      I      J         A     B    C    D    E    FA    G    H    I    J
  { { OUTPUT, OUTPUT, INPUT, INPUT, INPUT, INPUT, INPUT, INPUT, INPUT, INPUT }, { HIGH, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW } }, // AB 0
  { { OUTPUT, OUTPUT, INPUT, INPUT, INPUT, INPUT, INPUT, INPUT, INPUT, INPUT }, { LOW, HIGH, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW } }, // BA 0
  { { OUTPUT, INPUT, OUTPUT, INPUT, INPUT, INPUT, INPUT, INPUT, INPUT, INPUT }, { HIGH, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW } }, // AC 0
  { { OUTPUT, INPUT, OUTPUT, INPUT, INPUT, INPUT, INPUT, INPUT, INPUT, INPUT }, { LOW, LOW, HIGH, LOW, LOW, LOW, LOW, LOW, LOW, LOW } }, // BA 0
  { { OUTPUT, INPUT, INPUT, OUTPUT, INPUT, INPUT, INPUT, INPUT, INPUT, INPUT }, { HIGH, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW } }, // AB 0
  { { OUTPUT, INPUT, INPUT, OUTPUT, INPUT, INPUT, INPUT, INPUT, INPUT, INPUT }, { LOW, LOW, LOW, HIGH, LOW, LOW, LOW, LOW, LOW, LOW } }, // BA 0
  { { OUTPUT, INPUT, INPUT, INPUT, OUTPUT, INPUT, INPUT, INPUT, INPUT, INPUT }, { HIGH, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW } }, // AC 0
  { { OUTPUT, INPUT, INPUT, INPUT, INPUT, INPUT, INPUT, INPUT, INPUT, INPUT }, { HIGH, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW } }, // BA 0
  { { OUTPUT, INPUT, INPUT, INPUT, INPUT, INPUT, INPUT, INPUT, INPUT, INPUT }, { LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW } }, // BA 0
};

void setup() {
  Serial.begin(9600);
}

void loop() {
  //sms code from supercollider (nummsgs, banknum, lednum, ledstate)
  if (messageBuild() > 0) { // Checks to see if the message is complete and erases any previous messages
    int nummsgs =  messageGetInt();
    for (int i = 0; i < nummsgs; i++) {
      int bank = messageGetInt();
      lednum = messageGetInt();
      ledstate = messageGetInt();
      lst[lednum] = ledstate;
    }
  }
  //Turn On LEDs
  ct = 0;
  for (int i = 0; i < LCT; i++) {
    if (lst[i] == 1) {
      turnOn(ledorder[i]);
      ct = ct + 1;
      delay(1);
      ofg = true;
    }
    if (i == (LCT - 1)) if (ct == 0) if (ofg) {
          off();
          ofg = false;
        }
  }
}

void turnOn( int led ) {
  pinModeFast( A, matrix[led][PIN_CONFIG][0] );
  pinModeFast( B, matrix[led][PIN_CONFIG][1] );
  pinModeFast( C, matrix[led][PIN_CONFIG][2] );
  pinModeFast( D, matrix[led][PIN_CONFIG][3] );
  pinModeFast( E, matrix[led][PIN_CONFIG][4] );
  digitalWriteFast( A, matrix[led][PIN_STATE][0] );
  digitalWriteFast( B, matrix[led][PIN_STATE][1] );
  digitalWriteFast( C, matrix[led][PIN_STATE][2] );
  digitalWriteFast( D, matrix[led][PIN_STATE][3] );
  digitalWriteFast( E, matrix[led][PIN_STATE][4] );
}

void off() {
  pinModeFast( A, INPUT);
  pinModeFast( B, INPUT);
  pinModeFast( C, INPUT);
  pinModeFast( D, INPUT);
  pinModeFast( E, INPUT);
  digitalWriteFast( A, LOW);
  digitalWriteFast( B, LOW);
  digitalWriteFast( C, LOW);
  digitalWriteFast( D, LOW);
  digitalWriteFast( E, LOW);
}





