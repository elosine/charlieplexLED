#include <SimpleMessageSystem.h>
#include <digitalWriteFast.h>

#define A 2
#define B 3
#define C 4
#define D 5

#define I 6 //Pin addressed by supercollider

#define PIN_CONFIG 0
#define PIN_STATE 1

#define LED_COUNT 12
#define LCT 12

int lst[LCT] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
int lednum;
int ledstate;

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

void setup() {
  Serial.begin(9600);
  pinMode(I, INPUT);
}

void loop() {
  //sms code from supercollider (lednum, ledstate)
  if (messageBuild() > 0) { // Checks to see if the message is complete and erases any previous messages
    lednum = messageGetInt();
    ledstate = messageGetInt();
    lst[lednum] = ledstate;
  }

  //LED Shifter
  trigpinstate = digitalRead(I);
  if (trigpinstate == HIGH) {
    if (ledgate) {
      ledgate = false;
      ledstate = (ledstate + 1) % numstates;
    }
  }
  else {
    if (!ledgate) {
      ledgate = true;
    }
  }
  switch (ledstate) {
    case 0:
      turnOn(7);
      break;

    case 1:
      turnOn(11);
      break;

    case 2:
      turnOn(9);
      break;

    case 3:
      turnOn(5);
      break;

    case 4:
      turnOn(10);
      break;

    case 5:
      turnOn(3);
      break;

    case 6:
      turnOn(1);
      break;

    case 7:
      turnOn(2);
      break;

    case 8:
      turnOn(8);
      break;

    case 9:
      turnOn(6);
      break;

    case 10:
      turnOn(4);
      break;

    case 11:
      turnOn(0);
      break;

  }
}




void readpins() { // Read pins (analog or digital)

  switch (messageGetChar()) { // Gets the next word as a character

    case 'd': // READ digital pins

      messageSendChar('d');  // Echo what is being read
      for (char i = 2; i < 14; i++) {
        messageSendInt(digitalRead(i)); // Read pins 2 to 13
      }
      messageEnd(); // Terminate the message being sent
      break; // Break from the switch

    case 'a': // READ analog pins

      messageSendChar('a');  // Echo what is being read
      for (char i = 0; i < 6; i++) {
        messageSendInt(analogRead(i)); // Read pins 0 to 5
      }
      messageEnd(); // Terminate the message being sent

  }

}

void writepin() { // Write pin

  int pin;
  int state;

  switch (messageGetChar()) { // Gets the next word as a character

    case 'a' : // WRITE an analog pin

      pin = messageGetInt(); // Gets the next word as an integer
      state = messageGetInt(); // Gets the next word as an integer
      pinMode(pin, OUTPUT); //Sets the state of the pin to an output
      analogWrite(pin, state); //Sets the PWM of the pin
      break;  // Break from the switch


    // WRITE a digital pin
    case 'd' :

      pin = messageGetInt();  // Gets the next word as an integer
      state = messageGetInt();  // Gets the next word as an integer
      pinMode(pin, OUTPUT); //Sets the state of the pin to an output
      digitalWrite(pin, state); //Sets the state of the pin HIGH (1) or LOW (0)


  }

}
