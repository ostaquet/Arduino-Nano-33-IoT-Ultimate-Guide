/********************************************************************************
 * Management of the connectivity with the backend (Wifi)
 * Author: Olivier Staquet
 *******************************************************************************/
#include "Connectivity.h"

/**
 * Initialize and manage the errors
 */
uint8_t ConnectivityClass::begin(const char* network_name, const char* network_password, const char* ping_to_test) {
  // Add some logging
  Serial.println(F("Initialize wifi connectivity"));

  // Keep the local variables
  this->network_name = network_name;
  this->network_password = network_password;

  // Check if the WiFi module is present
  if(WiFi.status() == WL_NO_MODULE) {
    Serial.println(F("Communication with Wifi module failed!"));
    return 4;
  }

  // Check the firmware version
  String firmware_version = WiFi.firmwareVersion();
  if(firmware_version < WIFI_FIRMWARE_LATEST_VERSION) {
    Serial.println(F("Firmware is not the latest version. Please upgrade."));
    return 8;
  }
  
  // If something goes wrong, set the system in problem
  if(!this->connect()) {
    return 16;
  }

  // Show connectivity details
  displayWifiConfig();
  displayNetworkConfig();

  // Check connectivity
  uint16_t ping_result = WiFi.ping(ping_to_test);
  if(ping_result < 0) {
    Serial.print(F("Failed to ping the internet (error "));
    Serial.print(ping_result);
    Serial.println(F(")"));
    return 32;
  }

  // Show that we're OK here
  Serial.print(F("Internet connectivity validated (ping "));
  Serial.print(ping_result);
  Serial.println(F(" ms)"));

  // Switch off the connectivity
  disconnect();

  return 0;
}

/**
 * Manage the establishment of the connection
 */
bool ConnectivityClass::connect() {
  // Attempt to connect (5 retry max)
  uint16_t wifi_status = WL_IDLE_STATUS;
  for(uint8_t retry = 0; retry < 5 && wifi_status != WL_CONNECTED; retry++) {
    // Add some logging
    Serial.print(F("Attempting to connect to network "));
    Serial.print(this->network_name);
    Serial.print(F(" (attempt "));
    Serial.print(retry + 1);
    Serial.println(F(")"));

    // Connect
    wifi_status = WiFi.begin(this->network_name, this->network_password);

    // Wait 10 seconds for connection
    delay(10000);
  }

  // If something goes wrong, disconnect all and return false
  if(wifi_status != WL_CONNECTED) {
    Serial.print(F("Failed to connect on the wifi network (error "));
    Serial.print(wifi_status);
    Serial.println(F(")"));
    disconnect();
    return false;
  }

  // Show that we're OK here
  Serial.println(F("Connection established"));

  // Wait for stable network
  delay(1000);
  return true;
}

/**
 * Manage the establishment of the connection
 */
bool ConnectivityClass::disconnect() {
  // Switch off the connectivity and the wifi module (save power ;-) )
  WiFi.end();

  // Wait for stable stop
  delay(1000);
}

/**
 * Execute HTTP GET request and store in in the buffer (only with SSL on standard port)
 * Return code :
 *  - HTTP_OK = OK
 *  - HTTP_UNABLE_TO_CONNECT_SERVER = Unable to connect the server
 *  - HTTP_READ_TIMEOUT_ERROR = Read timeout
 */
uint8_t ConnectivityClass::get(char* server, char* path, uint16_t read_timeout) {
  // Prepare the client
  WiFiSSLClient client;
  
  // Connect to the server
  Serial.print(F("Attempt to connect "));
  Serial.print(server);
  Serial.println(F(":443 ..."));
  
  if(client.connect(server, 443)) {
    // Connection established
    Serial.println(F("Connection to server established"));
    client.print("GET ");
    client.print(path);
    client.println(" HTTP/1.1");
    client.print("Host: ");
    client.println(server);
    client.println("User-Agent: ArduinoWiFiNINA/1.4.0");
    client.println("Connection: close");
    client.println();
  } else {
    Serial.println(F("Unable to connect to the server"));
    client.stop();
    return HTTP_UNABLE_TO_CONNECT_SERVER;
  }

  // Listen and manage a timeout
  unsigned long startTime = millis();
  bool received = false;

  while ((millis() - startTime < read_timeout) && !received) {
    while(client.available()) {
      received = true;
      char c = client.read();
      Serial.write(c);
    }
  }

  client.stop();

  if(!received) {
    Serial.println(F("Read timeout"));
    disconnect();
    return HTTP_READ_TIMEOUT_ERROR;  
  } else {
    // Return OK
    return HTTP_OK;
  }
}

/**
 * Display details of network configuration
 */
void ConnectivityClass::displayNetworkConfig() {
  // Get network data
  IPAddress ip = WiFi.localIP();
  Serial.print(F("IP address : "));
  Serial.println(ip);

  Serial.print(F("Subnet mask : "));
  Serial.println((IPAddress)WiFi.subnetMask());

  Serial.print(F("Gateway IP : "));
  Serial.println((IPAddress)WiFi.gatewayIP());

  // Get MAC address
  byte mac[6];
  WiFi.macAddress(mac);
  Serial.print(F("MAC address : "));
  displayMacAddress(mac);
}

/**
 * Display details of Wifi configuration
 */
void ConnectivityClass::displayWifiConfig() {
  // Get SSID
  Serial.print(F("SSID : "));
  Serial.println(WiFi.SSID());

  // Get data from the AP
  byte bssid[6];
  WiFi.BSSID(bssid);
  Serial.print(F("BSSID : "));
  displayMacAddress(bssid);
  
  // Get signal strength
  long rssi = WiFi.RSSI();
  Serial.print(F("Signal strength (RSSI) : "));
  Serial.print(rssi);
  Serial.println(F(" dBm"));

  // Get encryption type
  byte encryption = WiFi.encryptionType();
  Serial.print(F("Encryption Type : "));
  switch(encryption) {
    case 0x02 :
      Serial.println(F("TKIP (WPA)"));
      break;
    case 0x05 :
      Serial.println(F("WEP"));
      break;
    case 0x04 :
      Serial.println(F("CCMP (WPA)"));
      break;
    case 0x07 :
      Serial.println(F("None"));
      break;
    case 0x08 :
      Serial.println(F("Auto"));
      break;
    default :
      Serial.println(F("Unknown"));
      break;
  }
}

/**
 * Display a mac address in readable format
 */
void ConnectivityClass::displayMacAddress(byte mac[]) {
  char *pretty = new char[17];
  prettyMacAddress(mac, pretty);
  Serial.println(pretty);
}

/**
 * Prepare a char array with the MAC address
 * Requires in input a char array of 17 char
 */
void ConnectivityClass::prettyMacAddress(byte mac[], char *prettyMacAddress) {
  sprintf(prettyMacAddress, "%X:%X:%X:%X:%X:%X", mac[5], mac[4], mac[3], mac[2], mac[1], mac[0]);
}

ConnectivityClass Connectivity;
