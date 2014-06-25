/* wled  25/06/2014  D.J.Whale
 *
 * Write to a neopixel LED
 * Format is PiiRRGGBB
 * P means pixel
 * ii is the index of the LED (hex), FF means all LEDs
 * RR is the red part (hex)
 * GG is the green part (hex)
 * BB is the blue part (hex)
 */

// perhaps Pzppll configures pin pp as a strip of length ll
// perhaps Pypp selects strip on that pin as the default to write to with the P command

#include <Adafruit_NeoPixel.h>

#define PINA 9
#define PINB 10

#define ALL_LEDS 0xFF

Adafruit_NeoPixel* pStrip1;
Adafruit_NeoPixel* pStrip2;

uint8_t chIndex = 0;    // index of char being processed
uint8_t ledIndex;       // index of LED to control, or ALL_LEDS
uint8_t red;
uint8_t green;
uint8_t blue;

void setup() 
{
  pStrip1 = new Adafruit_NeoPixel(8, PINA, NEO_GRB + NEO_KHZ800);
  pStrip1->begin();
  pStrip1->show();

  pStrip2 = new Adafruit_NeoPixel(1, PINB, NEO_GRB + NEO_KHZ800);
  pStrip2->begin();
  pStrip2->show();
  
  Serial.begin(115200);
}


void loop() 
{
  if (parseSerial())
  {
    if (ledIndex == ALL_LEDS)
    {
      for (int i=0; i<pStrip1->numPixels(); i++)
      {
        pStrip1->setPixelColor(i, red, green, blue);
      }
      for (int i=0; i<pStrip2->numPixels(); i++)
      {
        pStrip2->setPixelColor(i, red, green, blue);      
      }      
    }
    else
    {
      if (ledIndex < pStrip1->numPixels())
      {
        pStrip1->setPixelColor(ledIndex, red, green, blue);
      }
      if (ledIndex < pStrip2->numPixels())
      {
        pStrip2->setPixelColor(ledIndex, red, green, blue);  
      }    
    }
    pStrip1->show();
    pStrip2->show();
  }
}

uint8_t gethex(char ch)
{
  if (ch >= '0' && ch <= '9')
  {
    return ch - '0';
  }
  if (ch >= 'A' && ch <= 'F')
  {
    return (ch - 'A') + 10;
  }
  return 0; /* unknown */
}

boolean parseSerial()
{
  char ch;
  
  if (Serial.available() == 0)
  {
    return false; /* Nothing to report */
  }
  
  ch = Serial.read();
  if (ch == 'P')
  { /* resync to command start */
    chIndex = 1;
    return false; /* nothing to report yet */
  }  
  
  switch (chIndex)
  {
    case 0: /* Do nothing until W command seen above */
    break;
    
    case 1: /* IH - high nybble of index */
      ledIndex = gethex(ch)<<4;
      chIndex++;
    break;
    
    case 2: /* IL - low nybble of index */
      ledIndex += gethex(ch);
      chIndex++;
    break;
    
    case 3: /* RH */
      red = gethex(ch) <<4;
      chIndex++;
    break;
    
    case 4: /* RL */
      red += gethex(ch);
      chIndex++;
    break;
    
    case 5: /* GH */
      green = gethex(ch) <<4;
      chIndex++;
    break;
    
    case 6: /* GL */
      green += gethex(ch);
      chIndex++;
    break;
    
    case 7: /* BH */
      blue = gethex(ch) <<4;
      chIndex++;
    break;
    
    case 8: /* BL */
      blue += gethex(ch);
      chIndex = 0;
      return true; /* we have a full command now */
    /* break */
  }
  return false; /* We don't have a command yet */
}


