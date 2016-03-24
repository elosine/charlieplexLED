#include <SimpleMessageSystem.h>
#include <digitalWriteFast.h>

#define NSET 2
#define NP 5
#define LCT 20

#define PIN_CONFIG 0
#define PIN_STATE 1


int PIN[NSET][NP] = { {2,3,4,5,6}, {7,8,9,10,16} };


int lst[NSET][LCT] = {
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
};

int ledorder[NSET][LCT] = {
  {12,0,4,6,14,1,2,8,16,5,3,10,18,7,9,11,19,13,15,17},
  {18,0,4,6,12,1,2,8,14,5,3,10,16,7,9,11,13,15,17,19}
};
int nummsgs;
int banknum;
int lednum;
int ledstate;
boolean ofg[NSET] = {false, false};
int ct[NSET] = {0, 0};

int matrix[NSET][LCT][2][5] = {
  {
    //           PIN_CONFIG                              PIN_STATE
    //    A       B       C      D      E         A     B    C    D    E
    { { OUTPUT, OUTPUT, INPUT, INPUT, INPUT }, { HIGH, LOW, LOW, LOW, LOW } }, // AB 0
    { { OUTPUT, OUTPUT, INPUT, INPUT, INPUT }, { LOW, HIGH, LOW, LOW, LOW } }, // BA 1
    { { INPUT, OUTPUT, OUTPUT, INPUT, INPUT }, { LOW, HIGH, LOW, LOW, LOW } }, // BC 2
    { { INPUT, OUTPUT, OUTPUT, INPUT, INPUT }, { LOW, LOW, HIGH, LOW, LOW } }, // CB 3
    { { OUTPUT, INPUT, OUTPUT, INPUT, INPUT }, { HIGH, LOW, LOW, LOW, LOW } }, // AC 4
    { { OUTPUT, INPUT, OUTPUT, INPUT, INPUT }, { LOW, LOW, HIGH, LOW, LOW } }, // CA 5
    { { OUTPUT, INPUT, INPUT, OUTPUT, INPUT }, { HIGH, LOW, LOW, LOW, LOW } }, // AD 6
    { { OUTPUT, INPUT, INPUT, OUTPUT, INPUT }, { LOW, LOW, LOW, HIGH, LOW } }, // DA 7
    { { INPUT, OUTPUT, INPUT, OUTPUT, INPUT }, { LOW, HIGH, LOW, LOW, LOW } }, // BD 8
    { { INPUT, OUTPUT, INPUT, OUTPUT, INPUT }, { LOW, LOW, LOW, HIGH, LOW } }, // DB 9
    { { INPUT, INPUT, OUTPUT, OUTPUT, INPUT }, { LOW, LOW, HIGH, LOW, LOW } }, // CD 10
    { { INPUT, INPUT, OUTPUT, OUTPUT, INPUT }, { LOW, LOW, LOW, HIGH, LOW } },  // DC 11
    { { OUTPUT, INPUT, INPUT, INPUT, OUTPUT }, { HIGH, LOW, LOW, LOW, LOW } },  // AE 12
    { { OUTPUT, INPUT, INPUT, INPUT, OUTPUT }, { LOW, LOW, LOW, LOW, HIGH } },  // EA 13
    { { INPUT, OUTPUT, INPUT, INPUT, OUTPUT }, { LOW, HIGH, LOW, LOW, LOW } },  // BE 14
    { { INPUT, OUTPUT, INPUT, INPUT, OUTPUT }, { LOW, LOW, LOW, LOW, HIGH } },  // EB 15
    { { INPUT, INPUT, OUTPUT, INPUT, OUTPUT }, { LOW, LOW, HIGH, LOW, LOW } },  // CE 16
    { { INPUT, INPUT, OUTPUT, INPUT, OUTPUT }, { LOW, LOW, LOW, LOW, HIGH } },  // EC 17
    { { INPUT, INPUT, INPUT, OUTPUT, OUTPUT }, { LOW, LOW, LOW, HIGH, LOW } },  // DE 18
    { { INPUT, INPUT, INPUT, OUTPUT, OUTPUT }, { LOW, LOW, LOW, LOW, HIGH } }  // ED 19
  },

  {
    //           PIN_CONFIG                              PIN_STATE
    //    A       B       C      D      E         A     B    C    D    E
    { { OUTPUT, OUTPUT, INPUT, INPUT, INPUT }, { HIGH, LOW, LOW, LOW, LOW } }, // AB 0
    { { OUTPUT, OUTPUT, INPUT, INPUT, INPUT }, { LOW, HIGH, LOW, LOW, LOW } }, // BA 1
    { { INPUT, OUTPUT, OUTPUT, INPUT, INPUT }, { LOW, HIGH, LOW, LOW, LOW } }, // BC 2
    { { INPUT, OUTPUT, OUTPUT, INPUT, INPUT }, { LOW, LOW, HIGH, LOW, LOW } }, // CB 3
    { { OUTPUT, INPUT, OUTPUT, INPUT, INPUT }, { HIGH, LOW, LOW, LOW, LOW } }, // AC 4
    { { OUTPUT, INPUT, OUTPUT, INPUT, INPUT }, { LOW, LOW, HIGH, LOW, LOW } }, // CA 5
    { { OUTPUT, INPUT, INPUT, OUTPUT, INPUT }, { HIGH, LOW, LOW, LOW, LOW } }, // AD 6
    { { OUTPUT, INPUT, INPUT, OUTPUT, INPUT }, { LOW, LOW, LOW, HIGH, LOW } }, // DA 7
    { { INPUT, OUTPUT, INPUT, OUTPUT, INPUT }, { LOW, HIGH, LOW, LOW, LOW } }, // BD 8
    { { INPUT, OUTPUT, INPUT, OUTPUT, INPUT }, { LOW, LOW, LOW, HIGH, LOW } }, // DB 9
    { { INPUT, INPUT, OUTPUT, OUTPUT, INPUT }, { LOW, LOW, HIGH, LOW, LOW } }, // CD 10
    { { INPUT, INPUT, OUTPUT, OUTPUT, INPUT }, { LOW, LOW, LOW, HIGH, LOW } },  // DC 11
    { { OUTPUT, INPUT, INPUT, INPUT, OUTPUT }, { HIGH, LOW, LOW, LOW, LOW } },  // AE 12
    { { OUTPUT, INPUT, INPUT, INPUT, OUTPUT }, { LOW, LOW, LOW, LOW, HIGH } },  // EA 13
    { { INPUT, OUTPUT, INPUT, INPUT, OUTPUT }, { LOW, HIGH, LOW, LOW, LOW } },  // BE 14
    { { INPUT, OUTPUT, INPUT, INPUT, OUTPUT }, { LOW, LOW, LOW, LOW, HIGH } },  // EB 15
    { { INPUT, INPUT, OUTPUT, INPUT, OUTPUT }, { LOW, LOW, HIGH, LOW, LOW } },  // CE 16
    { { INPUT, INPUT, OUTPUT, INPUT, OUTPUT }, { LOW, LOW, LOW, LOW, HIGH } },  // EC 17
    { { INPUT, INPUT, INPUT, OUTPUT, OUTPUT }, { LOW, LOW, LOW, HIGH, LOW } },  // DE 18
    { { INPUT, INPUT, INPUT, OUTPUT, OUTPUT }, { LOW, LOW, LOW, LOW, HIGH } }  // ED 19
  }

};

void setup() {
  Serial.begin(9600);
}

void loop() {
  //sms code from supercollider (nummsgs, banknum, lednum, ledstate)
  if (messageBuild() > 0) { // Checks to see if the message is complete and erases any previous messages
    nummsgs =  messageGetInt();
    for (int i = 0; i < nummsgs; i++) {
      banknum = messageGetInt();
      lednum = messageGetInt();
      ledstate = messageGetInt();
      lst[banknum][lednum] = ledstate;
    }
  }
  //Turn On LEDs
  for (int i = 0; i < LCT; i++) {
    for (int j = 0; j < NSET; j++) {
      ct[j] = 0;
      if (lst[j][i] == 1) {
        turnOn(j, ledorder[j][i]);
        ct[j] = ct[j] + 1;
        ofg[j] = true;
      }
      if (i == (LCT - 1)) if (ct[j] == 0) if (ofg[j]) {
            off(j);
            ofg[j] = false;
          }
    }
    delayMicroseconds(500);
   // delay(3);
  }

}

void turnOn( int bank, int led ) {
    for (int j = 0; j < NP; j++) {
      pinModeFast( PIN[bank][j], matrix[bank][led][PIN_CONFIG][j] );
    }
    for (int j = 0; j < NP; j++) {
      digitalWriteFast( PIN[bank][j], matrix[bank][led][PIN_STATE][j] );
    }
  
}


void off(int bank) {
    for (int j = 0; j < NP; j++) {
      pinModeFast( PIN[bank][j], INPUT );
    }
    for (int j = 0; j < NP; j++) {
      digitalWriteFast( PIN[bank][j], LOW);
    }
}





