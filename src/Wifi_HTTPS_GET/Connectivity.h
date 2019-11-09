/********************************************************************************
 * Management of the connectivity with the backend (Wifi)
 * Author: Olivier Staquet
 *******************************************************************************/
#ifndef _CONNECTIVITY_H_
#define _CONNECTIVITY_H_

#include <Arduino.h>
#include <WiFiNINA.h>

#define HTTP_OK                         0x00
#define HTTP_UNABLE_TO_CONNECT_SERVER   0x01
#define HTTP_READ_TIMEOUT_ERROR         0x02

#define JSON_BUFFER_SIZE                1024

class ConnectivityClass {
  public:
    // Initialize and check the Internet connectivity with a ping (RC 0 = OK)
    uint8_t begin(const char* network_name, const char* network_password, const char* ping_to_test);

    // Manage the establishment of the connection
    bool connect();
    bool disconnect();

    // Execute HTTP GET request and write it on Serial, return 0 if OK (only SSL on standard port)
    uint8_t get(char* server, char* path, uint16_t read_timeout);

    // Display basic information (network and wifi connectivity)
    void displayNetworkConfig();
    void displayWifiConfig();

  protected:
    // Display a mac address in readable format
    void displayMacAddress(byte mac[]);
    void prettyMacAddress(byte mac[], char *prettyMacAddress);

  private:
    // Internal variables
    // Keep network information to connect after the initialization
    const char* network_name;
    const char* network_password;
};

extern ConnectivityClass Connectivity;

#endif // _CONNECTIVITY_H_
