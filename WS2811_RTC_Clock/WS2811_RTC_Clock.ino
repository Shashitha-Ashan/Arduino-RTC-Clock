/*
  S.Ashan Kalubowila

*/

#include <FastLED.h>
#include <Wire.h>
#include <ds3231.h>

struct ts t;

#define LED_PIN_1     3
#define LED_PIN_2     5


#define NUM_LEDS    14

#define CHIPSET     WS2811
#define COLOR_ORDER GRB
CRGB leds[NUM_LEDS];
CRGB leds2[NUM_LEDS];

long Ctime = 0;
long Ptime = 0;
boolean LedState = LOW;

#define BRIGHTNESS  128


boolean numbers_pattern [60][14] = {
  {1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 0}, //0
  {1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 0, 0}, //1
  {1, 1, 1, 1, 1, 1, 0, 1, 0, 1, 1, 0, 1, 1}, //2
  {1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1}, //3
  {1, 1, 1, 1, 1, 1, 0, 0, 1, 0, 1, 1, 0, 1}, //4
  {1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 0, 1, 1, 1}, //5
  {1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1}, //6
  {1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 0, 0}, //7
  {1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1}, //8
  {0, 0, 0, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1}, //9
  {0, 0, 0, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 0}, //10
  {0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 1, 1, 0, 0}, //11
  {0, 0, 0, 1, 1, 0, 0, 1, 0, 1, 1, 0, 1, 1}, //12
  {0, 0, 0, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 1}, //13
  {0, 0, 0, 1, 1, 0, 0, 0, 1, 0, 1, 1, 0, 1}, //14
  {0, 0, 0, 1, 1, 0, 0, 0, 1, 1, 0, 1, 1, 1}, //15
  {0, 0, 0, 1, 1, 0, 0, 1, 1, 1, 0, 1, 1, 1}, //16
  {0, 0, 0, 1, 1, 0, 0, 0, 0, 1, 1, 1, 0, 0}, //17
  {0, 0, 0, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1}, //18
  {0, 0, 0, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1}, //19

  {1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0}, //20
  {1, 0, 1, 1, 0, 1, 1, 0, 0, 0, 1, 1, 0, 0}, //21
  {1, 0, 1, 1, 0, 1, 1, 1, 0, 1, 1, 0, 1, 1}, //22
  {1, 0, 1, 1, 0, 1, 1, 0, 0, 1, 1, 1, 1, 1}, //23
  {1, 0, 1, 1, 0, 1, 1, 0, 1, 0, 1, 1, 0, 1}, //24
  {1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 1}, //25
  {1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1}, //26
  {1, 0, 1, 1, 0, 1, 1, 0, 0, 1, 1, 1, 0, 0}, //27
  {1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1}, //28
  {1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1}, //29

  {0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0}, //30
  {0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 0, 0}, //31
  {0, 0, 1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1}, //32
  {0, 0, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1}, //33
  {0, 0, 1, 1, 1, 1, 1, 0, 1, 0, 1, 1, 0, 1}, //34
  {0, 0, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1}, //35
  {0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1}, //36
  {0, 0, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 0, 0}, //37
  {0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, //38
  {0, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1}, //39

  {0, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0}, //40
  {0, 1, 0, 1, 1, 0, 1, 0, 0, 0, 1, 1, 0, 0}, //41
  {0, 1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 0, 1, 1}, //42
  {0, 1, 0, 1, 1, 0, 1, 0, 0, 1, 1, 1, 1, 1}, //43
  {0, 1, 0, 1, 1, 0, 1, 0, 1, 0, 1, 1, 0, 1}, //44
  {0, 1, 0, 1, 1, 0, 1, 0, 1, 1, 0, 1, 1, 1}, //45
  {0, 1, 0, 1, 1, 0, 1, 1, 1, 1, 0, 1, 1, 1}, //46
  {0, 1, 0, 1, 1, 0, 1, 0, 0, 1, 1, 1, 0, 0}, //47
  {0, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1}, //48
  {0, 1, 0, 1, 1, 0, 1, 0, 1, 1, 1, 1, 1, 1}, //49

  {0, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0}, //50
  {0, 1, 1, 0, 1, 1, 1, 0, 0, 0, 1, 1, 0, 0}, //51
  {0, 1, 1, 0, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1}, //52
  {0, 1, 1, 0, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1}, //53
  {0, 1, 1, 0, 1, 1, 1, 0, 1, 0, 1, 1, 0, 1}, //54
  {0, 1, 1, 0, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1}, //55
  {0, 1, 1, 0, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1}, //56
  {0, 1, 1, 0, 1, 1, 1, 0, 0, 1, 1, 1, 0, 0}, //57
  {0, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, //58
  {0, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1}, //59


};
void setup() {
  pinMode(13, OUTPUT);
  Serial.begin(9600);
  Wire.begin();
  delay( 3000 );
  FastLED.addLeds<CHIPSET, LED_PIN_1, COLOR_ORDER>(leds, NUM_LEDS).setCorrection( TypicalSMD5050 );
  FastLED.addLeds<CHIPSET, LED_PIN_2, COLOR_ORDER>(leds2, NUM_LEDS).setCorrection( TypicalSMD5050 );
  FastLED.setBrightness( BRIGHTNESS );

}

void loop() {
  DS3231_get(&t);
  display(t.hour);
  display2(t.min);

  Ctime = millis();
  if (Ctime - Ptime == 1000) {
    digitalWrite(13, !LedState);
    LedState = !LedState;
    Ptime = Ctime;

  }

}

void display(int no) {
  for (int i = 0 ; i < 14; i++) {
    if (numbers_pattern[no][i]) {
      leds[i] = CRGB::Red;

    } else {
      leds[i] = CRGB::Black;

    }
    FastLED.show();
  }

}
void display2(int no) {
  for (int i = 0 ; i < 14; i++) {
    if (numbers_pattern[no][i]) {
      leds2[i] = CRGB::Red;

    } else {
      leds2[i] = CRGB::Black;

    }
    FastLED.show();
  }

}


