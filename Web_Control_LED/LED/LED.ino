#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

#ifndef STASSID
#define STASSID "20304"
#define STAPSK "20001130"
#endif

const char* ssid = STASSID;
const char* password = STAPSK;

ESP8266WebServer server(80);

void setup(){
    Serial.begin(115200);

    pinMode(LED_BUILTIN, OUTPUT);
    digitalWrite(LED_BUILTIN, HIGH);

    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, password);
    Serial.println("");

    while(WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }

    Serial.print("Connected to ");
    Serial.println(ssid);
    Serial.print("ESP8266's IP address is: ");
    Serial.println(WiFi.localIP());

    server.begin();
    server.on("/", HTTP_GET, handleRoot);
    server.on("/LEDChange", HTTP_POST, LEDon);
    server.on("/LEDblink", HTTP_POST, LEDblink);
    server.on("/LEDbreathe", HTTP_POST, LEDbreathe);
    server.on("/LEDstop", HTTP_POST, LEDstop);
    server.onNotFound(handleNotFound);
}

void loop(){
    server.handleClient();
}

void handleRoot(){
    String s;
    s += "<!DOCTYPE html><html lang=\"en\"><head><meta charset=\"UTF-8\">";
    s += "<style>body{margin: auto 50%;display: flex;align-items: center;justify-content: center;}button{margin: 20px;width: 50px;height: 30px;}</style>";
    s += "<title>Control the LED_BUILTIN</title></head>";
    s += "<body><form action=\"/LEDChange\" method=\"POST\"><button>开</button></form>";
    s += "<form action=\"/LEDblink\" method=\"POST\"><button>闪烁</button></form>";
    s += "<form action=\"/LEDbreathe\" method=\"POST\"><button>呼吸</button></form>";
    s += "<form action=\"/LEDstop\" method=\"POST\"><button>停止</button></form>";
    s += "</body></html>";
    server.send(200, "text/html", s);
}

void handleNotFound(){
    server.send(404, "text/html", "<!DOCTYPE html><html lang=\"en\"><head><meta charset=\"UTF-8\"><meta name=\"viewport\"content=\"width=device-width, initial-scale=1.0\"><title>开关灯</title></head><body><h1>404 NOT FOUND</h1></body>");
}

void LEDon(){
    digitalWrite(LED_BUILTIN, LOW);
    server.sendHeader("Location", "/");
    server.send(303);
}

void LEDblink() {
    for(unsigned int i = 0;i < 5;++i) {
        digitalWrite(LED_BUILTIN, LOW);
        delay(500);
        digitalWrite(LED_BUILTIN, HIGH);
        delay(500);
    }
    server.sendHeader("Location", "/");
    server.send(303);
}

void LEDbreathe() {
    for(unsigned int i = 0;i < 5;++i) {
        for (int i=1023;i >= 0;i--) {
            analogWrite(LED_BUILTIN,i);
            delay(1);
        }
        for (int i=0;i <= 1023;i++) {
            analogWrite(LED_BUILTIN,i);
            delay(1);
        }
    }
    server.sendHeader("Location", "/");
    server.send(303);
}

void LEDstop() {
    digitalWrite(LED_BUILTIN, HIGH);
    server.sendHeader("Location", "/");
    server.send(303);
}
