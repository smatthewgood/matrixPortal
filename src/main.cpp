#include "matrix.h"
#include "scroll.h"
#include "app01.h"
#include "network.h"

void setup(void) {
    Serial.begin(115200);

    startTheNetwork();

    Serial.println("Starting the matrix...");

    startTheMatrix();

    setupTheBalls();

    startScrollDisplay();

    Serial.println("Setup complete.  Starting the loop.");
}

void loop(void) {
    matrix.fillScreen(0);
    bounceTheBalls();
    scrollTheText();
    matrix.show();
    mqttClient.poll();
    delay(20);
}