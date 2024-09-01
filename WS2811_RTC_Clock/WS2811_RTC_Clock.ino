/*
  S.Ashan Kalubowila

*/

#include <FastLED.h>
#include <Wire.h>
#include <ds3231.h>

struct ts t;

#define LED_PIN_1     3
#define LED_PIN_2     5
#define LED_PIN_3     6
#define LED_PIN_4     9


#define NUM_LEDS    14

#define CHIPSET     WS2811
#define COLOR_ORDER GRB
CRGB leds1[NUM_LEDS];
CRGB leds2[NUM_LEDS];
CRGB leds3[NUM_LEDS];
CRGB leds4[NUM_LEDS];

long Ctime = 0;
long Ptime = 0;
boolean LedState = LOW;

#define BRIGHTNESS  128


boolean numbers_pattern [10][14] = {
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

};
void setup() {
  pinMode(13, OUTPUT);
  Serial.begin(9600);
  Wire.begin();
  delay( 3000 );
  FastLED.addLeds<CHIPSET, LED_PIN_1, COLOR_ORDER>(leds, NUM_LEDS).setCorrection( TypicalSMD5050 );
  FastLED.addLeds<CHIPSET, LED_PIN_2, COLOR_ORDER>(leds2, NUM_LEDS).setCorrection( TypicalSMD5050 );
  FastLED.addLeds<CHIPSET, LED_PIN_3, COLOR_ORDER>(leds, NUM_LEDS).setCorrection( TypicalSMD5050 );
  FastLED.addLeds<CHIPSET, LED_PIN_4, COLOR_ORDER>(leds2, NUM_LEDS).setCorrection( TypicalSMD5050 );
  FastLED.setBrightness( BRIGHTNESS );

}

void loop() {
  DS3231_get(&t);
  int hour_first_digit = t.hour / 10;
  display_hour_first_digit(hour_first_digit);
  int hour_second_digit = t.hour % 10;
  display_hour_second_digit(hour_second_digit);
  int min_first_digit = t.min / 10;
  display_min_first_digit(min_first_digit);
  int min_second_digit = t.min % 10;
  display_min_second_digit(min_second_digit);

  Ctime = millis();
  if (Ctime - Ptime == 1000) {
    digitalWrite(13, !LedState);
    LedState = !LedState;
    Ptime = Ctime;

  }

}

void display_hour_first_digit(int no) {

  for (int i = 0 ; i < 14; i++) {
    if (numbers_pattern[no][i]) {
      leds1[i] = CRGB::Red;

    } else {
      leds1[i] = CRGB::Black;

    }
    FastLED.show();
  }

}
void display_hour_second_digit(int no) {

  for (int i = 0 ; i < 14; i++) {
    if (numbers_pattern[no][i]) {
      leds2[i] = CRGB::Red;

    } else {
      leds2[i] = CRGB::Black;

    }
    FastLED.show();
  }

}
void display_min_first_digit(int no) {

  for (int i = 0 ; i < 14; i++) {
    if (numbers_pattern[no][i]) {
      leds3[i] = CRGB::Red;

    } else {
      leds3[i] = CRGB::Black;

    }
    FastLED.show();
  }

}
void display_min_second_digit(int no) {
  for (int i = 0 ; i < 14; i++) {
    if (numbers_pattern[no][i]) {
      leds4[i] = CRGB::Red;

    } else {
      leds4[i] = CRGB::Black;

    }
    FastLED.show();
  }

}


