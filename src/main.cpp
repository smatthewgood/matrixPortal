#include "matrix.h"
#include "scroll.h"
#include "app01.h"

void setup(void) {
    Serial.begin(115200);
    Serial.println("Starting the matrix...");

    startTheMatrix();

    setupTheBalls();

    // startScrollDisplay();

    Serial.println("Setup complete.  Starting the loop.");
}

void loop(void) {
    matrix.fillScreen(0);
    bounceTheBalls();
    //scrollTheText();
    matrix.show();
    delay(20);
}