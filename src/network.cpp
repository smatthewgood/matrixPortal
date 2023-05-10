#include "network.h"
#include "secrets.h"
#include "mqtt_msg_parser.h"

const char mqtt_client[] = MQTT_CLIENT_NAME;
const char hostname[] = DEVICE_HOSTNAME;

char ssid[] = SECRET_WIFI_SSID;
char pass[] = SECRET_WIFI_PASS;
char mqtt_user[] = MQTT_USERNAME;
char mqtt_pass[] = MQTT_PASSWORD;
const char broker[] = MQTT_BROKER;
int mqtt_tcp_port     = MQTT_TCP_PORT;
const char topic[]  = MQTT_TOPIC;

WiFiClient wifiClient;
MqttClient mqttClient(wifiClient);

int status = WL_IDLE_STATUS;

void printWiFiStatus() {
    Serial.print("SSID: ");
    Serial.println(WiFi.SSID());

    IPAddress ip = WiFi.localIP();
    Serial.print("IP Address: ");
    Serial.println(ip);

    long rssi = WiFi.RSSI();
    Serial.print("Signal Strength (RSSI): ");
    Serial.print(rssi);
    Serial.println(" dBm");
}

void startMqttClient() {
    mqttClient.setId(mqtt_client);
    mqttClient.setUsernamePassword(mqtt_user, mqtt_pass);

    Serial.print("Attempting to connect to the MQTT broker: ");
    Serial.println(broker);

    if (!mqttClient.connect(broker,mqtt_tcp_port)) {
        Serial.print("MQTT connection failed!  Error code = ");
        Serial.println(mqttClient.connectError());

        while (1);
    }

    Serial.println("Connection Established!");
    Serial.println();

    mqttClient.onMessage(newMqttMsgReceived);

    mqttClient.subscribe(topic);

    Serial.print("Waiting for messages on topic: ");
    Serial.println(topic);
    Serial.println();
}

void startTheNetwork() {
    WiFi.setHostname(hostname);

    while (WiFi.status() == WL_NO_MODULE) {
        Serial.println("Communication with Wi-Fi module failed!");
        delay(1000);
    }

    String fv = WiFi.firmwareVersion();
    if (fv < "1.0.0") Serial.println("Please upgrade the firmware!");

    Serial.print("Attempting to connect to SSID: ");
    Serial.println(ssid);

    do {
        status = WiFi.begin(ssid, pass);
        delay(100);
    } while (status != WL_CONNECTED);
    Serial.println("Connected to Wi-Fi!");
    
    printWiFiStatus();

    startMqttClient();
}


