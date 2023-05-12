#include "app01.h"
#include "matrix.h"

// This app bounces balls on the screen

int8_t   ball[5][4] = {
  {  3,  0,  1,  1 },            // Initial X,Y pos+velocity of 3 bouncy balls
  { 17, 15,  1, -1 },
  { 27,  4, -1,  1 }
  , { 99, 4, -1, -1 }
  , { 127, 15, 1, -1 }
};
uint16_t ballcolor[5];           // Colors for bouncy balls (init in setup())

void setupTheBalls() {
  ballcolor[0] = matrix.color565(0, 20, 0); // Dark green
  ballcolor[1] = matrix.color565(0, 0, 20); // Dark blue
  ballcolor[2] = matrix.color565(20, 0, 0); // Dark red
  ballcolor[3] = matrix.color565(20, 20, 0); // Yellow
  ballcolor[4] = matrix.color565(20, 0, 20); // pink
}

void bounceTheBalls() {
    for(byte i=0; i<5; i++) {
    // Draw 'ball'
    matrix.fillCircle(ball[i][0], ball[i][1], 5, ballcolor[i]);
    // Update ball's X,Y position for next frame
    ball[i][0] += ball[i][2];
    ball[i][1] += ball[i][3];
//    ball[i][2] += ball[i][4];
//    ball[i][3] += ball[i][5];
    // Bounce off edges
    if((ball[i][0] == 0) || (ball[i][0] == (matrix.width() - 1)))
      ball[i][2] *= -1;
    if((ball[i][1] == 0) || (ball[i][1] == (matrix.height() - 1)))
      ball[i][3] *= -1;
  }
}

