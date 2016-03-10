#include <CmdMessenger.h>


#include <digitalWriteFast.h>


#define A 2
#define B 3
#define C 4
#define D 5

#define PIN_CONFIG 0
#define PIN_STATE 1

#define LED_COUNT 12

int matrix[LED_COUNT][2][4] = {
  //           PIN_CONFIG                  PIN_STATE
  //    A       B       C      D         A     B    C    D
  { { OUTPUT, OUTPUT, INPUT, INPUT }, { HIGH, LOW, LOW, LOW } }, // AB 0
  { { OUTPUT, OUTPUT, INPUT, INPUT }, { LOW, HIGH, LOW, LOW } }, // BA 1
  { { INPUT, OUTPUT, OUTPUT, INPUT }, { LOW, HIGH, LOW, LOW } }, // BC 2
  { { INPUT, OUTPUT, OUTPUT, INPUT }, { LOW, LOW, HIGH, LOW } }, // CB 3
  { { OUTPUT, INPUT, OUTPUT, INPUT }, { HIGH, LOW, LOW, LOW } }, // AC 4
  { { OUTPUT, INPUT, OUTPUT, INPUT }, { LOW, LOW, HIGH, LOW } }, // CA 5
  { { OUTPUT, INPUT, INPUT, OUTPUT }, { HIGH, LOW, LOW, LOW } }, // AD 6
  { { OUTPUT, INPUT, INPUT, OUTPUT }, { LOW, LOW, LOW, HIGH } }, // DA 7
  { { INPUT, OUTPUT, INPUT, OUTPUT }, { LOW, HIGH, LOW, LOW } }, // BD 8
  { { INPUT, OUTPUT, INPUT, OUTPUT }, { LOW, LOW, LOW, HIGH } }, // DB 9
  { { INPUT, INPUT, OUTPUT, OUTPUT }, { LOW, LOW, HIGH, LOW } }, // CD 10
  { { INPUT, INPUT, OUTPUT, OUTPUT }, { LOW, LOW, LOW, HIGH } }  // DC 11
};

void turnOn( int led ) {
  pinModeFast( A, matrix[led][PIN_CONFIG][0] );
  pinModeFast( B, matrix[led][PIN_CONFIG][1] );
  pinModeFast( C, matrix[led][PIN_CONFIG][2] );
  pinModeFast( D, matrix[led][PIN_CONFIG][3] );
  digitalWriteFast( A, matrix[led][PIN_STATE][0] );
  digitalWriteFast( B, matrix[led][PIN_STATE][1] );
  digitalWriteFast( C, matrix[led][PIN_STATE][2] );
  digitalWriteFast( D, matrix[led][PIN_STATE][3] );
}

void setup() {}

void loop() {
   for( int i = 0; i < 2; i++ ) {
    turnOn( 0 );
    delay( 1 );
    turnOn(2);
    delay(1);
    turnOn( 3 );
    delay( 1 );
    turnOn(10);
    delay(1);
    turnOn( 9 );
    delay( 1 );
    turnOn( 7 );
    delay(1);
  }
  /*
  for( int l = 0; l < LED_COUNT; l++ ) {
    turnOn( l );
    delay( 1000 / LED_COUNT );
  }
  */
}
