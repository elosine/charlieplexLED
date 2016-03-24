#include <SimpleMessageSystem.h>
#include <digitalWriteFast.h>

#define NUMPINS 10

#define PIN_CONFIG 0
#define PIN_STATE 1

#define LCT 40

int pn[10] = {2, 3, 4, 5, 6, 7, 8, 9, 10, 16};

int lst[LCT] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
int ledorder[LCT] = {12, 0, 4, 6, 14, 1, 2, 8, 16, 5, 3, 10, 18, 7, 9, 11, 19, 13, 15, 17, 38, 20, 24, 26, 32, 21, 22, 28, 34, 25, 23, 30, 36, 27, 29, 31, 33, 35, 37, 39};
int lednum;
int ledstate;
int bank;
boolean ofg = false;
int ct = 0;

int matrix[LCT][2][10] = {
  //           PIN_CONFIG                              PIN_STATE
  //    A       B       C      D      E      F      G      H      I      J         A     B    C    D    E    F    G    H    I    J
  { { OUTPUT, OUTPUT, INPUT, INPUT, INPUT, INPUT, INPUT, INPUT, INPUT, INPUT }, { HIGH, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW } }, // AB 0
  { { OUTPUT, OUTPUT, INPUT, INPUT, INPUT, INPUT, INPUT, INPUT, INPUT, INPUT }, { LOW, HIGH, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW } }, // BA 1
  { { INPUT, OUTPUT, OUTPUT, INPUT, INPUT, INPUT, INPUT, INPUT, INPUT, INPUT }, { LOW, HIGH, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW } }, // BC 2
  { { INPUT, OUTPUT, OUTPUT, INPUT, INPUT, INPUT, INPUT, INPUT, INPUT, INPUT }, { LOW, LOW, HIGH, LOW, LOW , LOW, LOW, LOW, LOW, LOW} }, // CB 3
  { { OUTPUT, INPUT, OUTPUT, INPUT, INPUT, INPUT, INPUT, INPUT, INPUT, INPUT }, { HIGH, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW } }, // AC 4
  { { OUTPUT, INPUT, OUTPUT, INPUT, INPUT, INPUT, INPUT, INPUT, INPUT, INPUT }, { LOW, LOW, HIGH, LOW, LOW, LOW, LOW, LOW, LOW, LOW } }, // CA 5
  { { OUTPUT, INPUT, INPUT, OUTPUT, INPUT, INPUT, INPUT, INPUT, INPUT, INPUT }, { HIGH, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW } }, // AD 6
  { { OUTPUT, INPUT, INPUT, OUTPUT, INPUT, INPUT, INPUT, INPUT, INPUT, INPUT }, { LOW, LOW, LOW, HIGH, LOW, LOW, LOW, LOW, LOW, LOW } }, // DA 7
  { { INPUT, OUTPUT, INPUT, OUTPUT, INPUT, INPUT, INPUT, INPUT, INPUT, INPUT }, { LOW, HIGH, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW } }, // BD 8
  { { INPUT, OUTPUT, INPUT, OUTPUT, INPUT, INPUT, INPUT, INPUT, INPUT, INPUT }, { LOW, LOW, LOW, HIGH, LOW, LOW, LOW, LOW, LOW, LOW } }, // DB 9
  { { INPUT, INPUT, OUTPUT, OUTPUT, INPUT, INPUT, INPUT, INPUT, INPUT, INPUT }, { LOW, LOW, HIGH, LOW, LOW, LOW, LOW, LOW, LOW, LOW } }, // CD 10
  { { INPUT, INPUT, OUTPUT, OUTPUT, INPUT, INPUT, INPUT, INPUT, INPUT, INPUT }, { LOW, LOW, LOW, HIGH, LOW, LOW, LOW, LOW, LOW, LOW } },  // DC 11
  { { OUTPUT, INPUT, INPUT, INPUT, OUTPUT, INPUT, INPUT, INPUT, INPUT, INPUT }, { HIGH, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW } },  // AE 12
  { { OUTPUT, INPUT, INPUT, INPUT, OUTPUT, INPUT, INPUT, INPUT, INPUT, INPUT }, { LOW, LOW, LOW, LOW, HIGH, LOW, LOW, LOW, LOW, LOW } },  // EA 13
  { { INPUT, OUTPUT, INPUT, INPUT, OUTPUT , INPUT, INPUT, INPUT, INPUT, INPUT}, { LOW, HIGH, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW } },  // BE 14
  { { INPUT, OUTPUT, INPUT, INPUT, OUTPUT, INPUT, INPUT, INPUT, INPUT, INPUT }, { LOW, LOW, LOW, LOW, HIGH, LOW, LOW, LOW, LOW, LOW } },  // EB 15
  { { INPUT, INPUT, OUTPUT, INPUT, OUTPUT, INPUT, INPUT, INPUT, INPUT, INPUT }, { LOW, LOW, HIGH, LOW, LOW, LOW, LOW, LOW, LOW, LOW } },  // CE 16
  { { INPUT, INPUT, OUTPUT, INPUT, OUTPUT, INPUT, INPUT, INPUT, INPUT, INPUT }, { LOW, LOW, LOW, LOW, HIGH, LOW, LOW, LOW, LOW, LOW } },  // EC 17
  { { INPUT, INPUT, INPUT, OUTPUT, OUTPUT, INPUT, INPUT, INPUT, INPUT, INPUT }, { LOW, LOW, LOW, HIGH, LOW, LOW, LOW, LOW, LOW, LOW } },  // DE 18
  { { INPUT, INPUT, INPUT, OUTPUT, OUTPUT, INPUT, INPUT, INPUT, INPUT, INPUT }, { LOW, LOW, LOW, LOW, HIGH, LOW, LOW, LOW, LOW, LOW } },  // ED 19
  { { INPUT, INPUT, INPUT, INPUT, INPUT, OUTPUT, OUTPUT, INPUT, INPUT, INPUT }, { LOW, LOW, LOW, LOW, LOW, HIGH, LOW, LOW, LOW, LOW } }, // AB 0
  { { INPUT, INPUT, INPUT, INPUT, INPUT, OUTPUT, OUTPUT, INPUT, INPUT, INPUT }, { LOW, LOW, LOW, LOW, LOW, LOW, HIGH, LOW, LOW, LOW } }, // BA 1
  { { INPUT, INPUT, INPUT, INPUT, INPUT, INPUT, OUTPUT, OUTPUT, INPUT, INPUT }, { LOW, LOW, LOW, LOW, LOW, LOW, HIGH, LOW, LOW, LOW } }, // BC 2
  { { INPUT, INPUT, INPUT, INPUT, INPUT, INPUT, OUTPUT, OUTPUT, INPUT, INPUT }, { LOW, LOW, LOW, LOW, LOW, LOW, LOW, HIGH, LOW, LOW } }, // CB 3
  { { INPUT, INPUT, INPUT, INPUT, INPUT, OUTPUT, INPUT, OUTPUT, INPUT, INPUT }, { LOW, LOW, LOW, LOW, LOW, HIGH, LOW, LOW, LOW, LOW } }, // AC 4
  { { INPUT, INPUT, INPUT, INPUT, INPUT, OUTPUT, INPUT, OUTPUT, INPUT, INPUT }, { LOW, LOW, LOW, LOW, LOW, LOW, LOW, HIGH, LOW, LOW } }, // CA 5
  { { INPUT, INPUT, INPUT, INPUT, INPUT, OUTPUT, INPUT, INPUT, OUTPUT, INPUT }, { LOW, LOW, LOW, LOW, LOW, HIGH, LOW, LOW, LOW, LOW } }, // AD 6
  { { INPUT, INPUT, INPUT, INPUT, INPUT, OUTPUT, INPUT, INPUT, OUTPUT, INPUT }, { LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, HIGH, LOW } }, // DA 7
  { { INPUT, INPUT, INPUT, INPUT, INPUT, INPUT, OUTPUT, INPUT, OUTPUT, INPUT }, { LOW, LOW, LOW, LOW, LOW, LOW, HIGH, LOW, LOW, LOW } }, // BD 8
  { { INPUT, INPUT, INPUT, INPUT, INPUT, INPUT, OUTPUT, INPUT, OUTPUT, INPUT }, { LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, HIGH, LOW } }, // DB 9
  { { INPUT, INPUT, INPUT, INPUT, INPUT, INPUT, INPUT, OUTPUT, OUTPUT, INPUT }, { LOW, LOW, LOW, LOW, LOW, LOW, LOW, HIGH, LOW, LOW } }, // CD 10
  { { INPUT, INPUT, INPUT, INPUT, INPUT, INPUT, INPUT, OUTPUT, OUTPUT, INPUT }, { LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, HIGH, LOW } },  // DC 11
  { { INPUT, INPUT, INPUT, INPUT, INPUT, OUTPUT, INPUT, INPUT, INPUT, OUTPUT }, { LOW, LOW, LOW, LOW, LOW, HIGH, LOW, LOW, LOW, LOW } },  // AE 12
  { { INPUT, INPUT, INPUT, INPUT, INPUT, OUTPUT, INPUT, INPUT, INPUT, OUTPUT }, { LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, HIGH } },  // EA 13
  { { INPUT, INPUT, INPUT, INPUT, INPUT, INPUT, OUTPUT, INPUT, INPUT, OUTPUT }, { LOW, LOW, LOW, LOW, LOW, LOW, HIGH, LOW, LOW, LOW } },  // BE 14
  { { INPUT, INPUT, INPUT, INPUT, INPUT, INPUT, OUTPUT, INPUT, INPUT, OUTPUT }, { LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, HIGH } },  // EB 15
  { { INPUT, INPUT, INPUT, INPUT, INPUT, INPUT, INPUT, OUTPUT, INPUT, OUTPUT }, { LOW, LOW, LOW, LOW, LOW, LOW, LOW, HIGH, LOW, LOW } },  // CE 16
  { { INPUT, INPUT, INPUT, INPUT, INPUT, INPUT, INPUT, OUTPUT, INPUT, OUTPUT }, { LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, HIGH } },  // EC 17
  { { INPUT, INPUT, INPUT, INPUT, INPUT, INPUT, INPUT, INPUT, OUTPUT, OUTPUT }, { LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, HIGH, LOW } },  // DE 18
  { { INPUT, INPUT, INPUT, INPUT, INPUT, INPUT, INPUT, INPUT, OUTPUT, OUTPUT }, { LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, HIGH } }  // ED 19
};

void setup() {
  Serial.begin(9600);
}

void loop() {
  //sms code from supercollider (nummsgs, lednum, ledstate)
  if (messageBuild() > 0) { // Checks to see if the message is complete and erases any previous messages
    int nummsgs =  messageGetInt();
    for (int i = 0; i < nummsgs; i++) {
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
      delayMicroseconds(100);
     // delay(15);
      ofg = true;
    }
    if (i == (LCT - 1)) if (ct == 0) if (ofg) {
          off();
          ofg = false;
        }
  }
}

void turnOn( int led ) {
  for (int i = 0; i < NUMPINS; i++) {
    pinModeFast( pn[i], matrix[led][PIN_CONFIG][i] );
  }
  for (int i = 0; i < NUMPINS; i++) {
    digitalWriteFast( pn[i], matrix[led][PIN_STATE][i] );
  }
}

void off() {
  for (int i = 0; i < NUMPINS; i++) {
    pinModeFast( pn[i], INPUT);
  }
  for (int i = 0; i < NUMPINS; i++) {
    digitalWriteFast( pn[i], LOW);
  }
}





