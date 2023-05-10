#pragma once

#ifndef MG_NETWORK_H
#define MG_NETWORK_H

#include "secrets.h"
#include <WiFiNINA.h>
#include <ArduinoMqttClient.h>

//WiFiClient wifiClient;
extern MqttClient mqttClient;

void startTheNetwork();
void printWiFiStatus();

#endif