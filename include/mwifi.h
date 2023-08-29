#ifndef _MWIFI_H_
#define _MWIFI_H_

#include <ESP_WiFiManager.h>

#include "mlog.h"

const char *WF_MANAGER_SSID = "SaganaTR";
const char *WF_ACCESS_POINT_NAME = "Bench";
const char *WF_PASSWORD = "1234567890";

bool connectWiFi(const char *ssid, const char *password);
void startWiFiManager(const char *ssid, const char *password);
#endif  // _MWIFI_H_