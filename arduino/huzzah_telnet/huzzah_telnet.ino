/**
 * Arduino ESP8266 telnet server with some ansi experiments
 * @author: shawn_a
 */

#include <ESP8266WiFi.h>
#include <Arduino.h>

/* Set these to your desired AP credentials. */
const char *APssid = "Rmando 2.4Ghz";
const char *APpassword = "NoCat007";
IPAddress ip(192,168,1,177);
IPAddress gateway(192,168,1,1);
IPAddress subnet(255,255,255,0);
int port = 23;

// ansi stuff, could always use printf instead of concat
String ansiPRE  = "\033"; // escape code
String ansiHOME = "\033[H"; // cursor home
String ansiESC  = "\033[2J"; // esc
String ansiCLC  = "\033[?25l"; // invisible cursor

String ansiEND  = "\033[0m";   // closing tag for styles
String ansiBOLD = "\033[1m";

String ansiRED  = "\033[41m"; // red background
String ansiGRN  = "\033[42m"; // green background
String ansiBLU  = "\033[44m"; // blue background

String ansiREDF = "\033[31m"; // red foreground
String ansiGRNF = "\033[34m"; // green foreground
String ansiBLUF = "\033[32m"; // blue foreground
String BELL     = "\a";

// declare telnet server (do NOT put in setup())
WiFiServer TelnetServer(port);
WiFiClient Telnet;

void handleTelnet(){
  if (TelnetServer.hasClient()){
    // client is connected
    if (!Telnet || !Telnet.connected()){
      if(Telnet) Telnet.stop();          // client disconnected
      Telnet = TelnetServer.available(); // ready for new client
    } else {
      TelnetServer.available().stop();  // have client, block new conections
    }
  }

  if (Telnet && Telnet.connected() && Telnet.available()){
    // client input processing
    while(Telnet.available())
      Serial.write(Telnet.read()); // pass through
      // do other stuff with client input here
  } 
}

void startAP(){
  WiFi.mode(WIFI_AP);
  //Serial.print("Setting soft-AP configuration ... ");
  //Serial.println(WiFi.softAPConfig(ip, gateway, subnet) ? "Ready" : "Failed!");
  WiFi.softAP(APssid, APpassword);
  IPAddress myIP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(myIP);
}

void setup() {
  Serial.begin(115200);
  // Serial.setDebugOutput(true);
  delay(1000); // serial delay

  Serial.println();
  Serial.println("Staring AP");
  startAP();   // startup is async ?
  delay(4000); // ap delay

  TelnetServer.begin();
  Serial.print("Starting telnet server on port " + (String)port);
  // TelnetServer.setNoDelay(true); // ESP BUG ?
  Serial.println();
  delay(100);
}

void loop() {
  handleTelnet();

  Telnet.print(ansiHOME+ansiCLC); // clear screen
  Telnet.println("uptime: "+ansiBLU + ansiBOLD + (String)millis() + ansiEND + ansiEND+" ms");
  delay(20); // to fast might crash terminals
}
