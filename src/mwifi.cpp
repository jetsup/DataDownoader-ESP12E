#include "mwifi.h"

bool connectWiFi(const char* ssid, const char* password) {
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  LOG("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    LOG(".");
  }
  LOG();
  LOG("Connected to the WiFi network");
  LOG("IP address", WiFi.localIP());
  LOG();
  return true;
}
void startWiFiManager(const char* ssid, const char* password) {
  ESP_WiFiManager wifiManager;
  wifiManager.autoConnect(ssid, password);
  LOG("Connected to the WiFi network");
  LOG("IP address", WiFi.localIP());
  LOG();

  IPAddress myIP(192, 168, 100, 100);
  WiFi.softAPConfig(myIP, myIP, IPAddress(255, 255, 255, 0));
  WiFi.softAP(WF_ACCESS_POINT_NAME, WF_PASSWORD);
}
