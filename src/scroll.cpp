#include "scroll.h"
#include "matrix.h"
#include <Adafruit_Protomatter.h>
#include <Fonts/FreeSansBold24pt7b.h>
#include <Fonts/FreeSansBold18pt7b.h>
#include <Fonts/FreeSansBold12pt7b.h>

int16_t  textX = matrix.width(), // Current text position (X)
         textY,                  // Current text position (Y)
         textMin,                // Text pos. (X) when scrolled off left edge
         hue = 0;

String curScrMsgText;
GFXfont curScrMsgFont;
uint16_t curScrMsgColor;

uint16_t getColor(String color) {
  const uint16_t colorBlue = 31;
  const uint16_t colorRed = 63488;
  const uint16_t colorGreen = 2016;
  const uint16_t colorCyan = 2047;
  const uint16_t colorMagenta = 63519;
  const uint16_t colorYellow = 65504;
  const uint16_t colorWhite = 65535;

  if (color == "Blue") return colorBlue;
  if (color == "Red") return colorRed;
  if (color == "Green") return colorGreen;
  if (color == "Cyan") return colorCyan; 
  if (color == "Magenta") return colorMagenta;
  if (color == "Yellow") return colorYellow;
  if (color == "White") return colorWhite;
  else return colorWhite;
}

GFXfont getFont(String font) {
  const GFXfont *large = &FreeSansBold24pt7b;
  const GFXfont *medium = &FreeSansBold18pt7b;
  const GFXfont *small = &FreeSansBold12pt7b;

  if (font == "Large") return *large;
  if (font == "Medium") return *medium;
  if (font == "Small") return *small;
  else return *medium;
}

void updateDisplay(String msgText, String msgColor, String msgFont) {
  curScrMsgText = msgText;
  curScrMsgFont = getFont(msgFont);
  curScrMsgColor = getColor(msgColor);
}

void startScrollDisplay() {
  // Set up the scrolling message...
  // sprintf(str, "Watch my balls on my %dx%d display", matrix.width(), matrix.height());
  // sprintf(str, "Watch My Balls Bounce");
  // matrix.setFont(&FreeSansBold18pt7b); // Use nice bitmap font
  // matrix.setTextWrap(false);           // Allow text off edge
  // matrix.setTextColor(0xFFFF);         // White
  // int16_t  x1, y1;
  // uint16_t w, h;
  // matrix.getTextBounds(curScrMsgText, 0, 0, &x1, &y1, &w, &h); // How big is it?
  // textMin = -w; // All text is off left edge when it reaches this point
  // textY = matrix.height() / 2 - (y1 + h / 2); // Center text vertically
  // Note: when making scrolling text like this, the setTextWrap(false)
  // call is REQUIRED (to allow text to go off the edge of the matrix),
  // AND it must be BEFORE the getTextBounds() call (or else that will
  // return the bounds of "wrapped" text).
}

void scrollTheText() {

  matrix.setFont(&curScrMsgFont);
  matrix.setTextColor(curScrMsgColor);
  matrix.setCursor(textX, textY);
  matrix.print(curScrMsgText);
  int16_t x1, y1;
  uint16_t w,h;
  matrix.getTextBounds(curScrMsgText, 0, 0, &x1, &y1, &w, &h); 
  textMin = -w;
  textY = matrix.height() / 2 - (y1 + h / 2);

  // Update text position for next frame. If text goes off the
  // left edge, reset its position to be off the right edge.
  if((--textX) < textMin) textX = matrix.width();
}