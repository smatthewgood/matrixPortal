#include "mqtt_msg_parser.h"
#include "network.h"

void newMqttMsgReceived(int messageSize) {
    Serial.print("Received a message with ");
    Serial.print(messageSize);
    Serial.println(" bytes");

    char msgPayload[160];

    while (mqttClient.available()) {
        int i;
        for (i = 0; i<messageSize; i++) {
            msgPayload[i]=mqttClient.read();
        }
        msgPayload[i] = '\0';
        #ifdef MG_TESTING
            Serial.println(msgPayload);
        #endif
    }
}
