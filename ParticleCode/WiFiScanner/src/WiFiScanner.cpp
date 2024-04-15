/* 
 * Project WiFiScanner
 * Author: Brian Rashap
 * Description: Determine which WiFi connections the Argon has stored and which are visible
 * Date: 19-OCT-2023
 */

// Include Particle Device OS APIs
#include "Particle.h"

// Let Device OS manage the connection to the Particle Cloud
SYSTEM_MODE(SEMI_AUTOMATIC);

WiFiAccessPoint ap[10];
WiFiAccessPoint aps[20];

int sectype;
int cytype;
int found;
int i;
byte mac[6];

String security[6] = {"WLAN_SEC_UNSEC", "WLAN_SEC_WEP", "WLAN_SEC_WPA", "WLAN_SEC_WPA2", "WLAN_SEC_WPA_ENTERPRISE", "WLAN_SEC_WPA2_ENTERPRISE"};
String cypher[4] = {"N/A","WLAN_CIPHER_AES", "WLAN_CIPHER_TKIP", "WLAN_CIPHER_AES_TKIP"};

//Uncomment the below to get full diagnostics
//SerialLogHandler LogHandler(LOG_LEVEL_ALL);


void setup() {
  Serial.begin(9600);
  waitFor(Serial.isConnected, 10000);

  WiFi.on();
  delay(1000);
  WiFi.macAddress(mac);
  Serial.printf("mac: %02X:%02X:%02X:%02X:%02X:%02X \n", mac[0],mac[1],mac[2],mac[3],mac[4],mac[5]);

  WiFi.connect();
  while(WiFi.connecting()) {
    Serial.printf(".");
    delay(250);
  }
  Serial.printf("\nWaiting for IP Address\n");
  delay(1000);
  Serial.printf("Scan Argon for WiFi Information \n");
  Serial.printf("ip address: %s \n", WiFi.localIP().toString().c_str());
  WiFi.macAddress(mac);
  Serial.printf("mac: %02X:%02X:%02X:%02X:%02X:%02X \n", mac[0],mac[1],mac[2],mac[3],mac[4],mac[5]);
  found = WiFi.getCredentials(ap, 5);
  Serial.printf("Credentials for %d Access Points Found \n",found);
  for (i = 0; i < found; i++) {
    sectype = (int) ap[i].security;
    cytype = (int) ap[i].cipher;
    for(int j=0;j<6;j++){
      mac[j] = ap[i].bssid[j];
    }
    
    Serial.printf("AP%d - ssid: %s \n", i,ap[i].ssid);
    Serial.printf("AP%d - mac: %02X:%02X:%02X:%02X:%02X:%02X \n", i,mac[0],mac[1],mac[2],mac[3],mac[4],mac[5]);
    Serial.printf("AP%d - security: %d (security %s) \n", i,sectype,security[sectype].c_str());
    Serial.printf("AP%d - cipher:   %d (cipher %s) \n\n", i,cytype, cypher[cytype].c_str());
  }


  Serial.printf("\n \nWifi Scan of available networks \n");
  found = WiFi.scan(aps, 20); 
  for (i=0; i<found; i++) {
      Serial.printf("ssid=%s security=%d cipher=%d, channel=%d rssi=%d \n", aps[i].ssid, (int)aps[i].security, (int)aps[i].cipher, aps[i].channel, aps[i].rssi);
  }
}

void loop() {} // nothing to loop
