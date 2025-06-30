#include <WiFi.h>

// Replace with your network credentials
const char* ssid = "Connecting.....";
const char* password = "Janmejay@2005";

WiFiServer server(80);


const int ledPin = 2;


void setup() {
  Serial.begin(115200);
  delay(1000);
  Serial.println("Booting...");

  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);

  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  int attempts = 0;
  while (WiFi.status() != WL_CONNECTED && attempts < 20) {
    delay(500);
    Serial.print(".");
    attempts++;
  }

  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("\nWiFi connected!");
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());
    server.begin();
  } else {
    Serial.println("\nFailed to connect to WiFi.");
  }
}

void loop() {
  WiFiClient client = server.available();
  if (client) {
    Serial.println("New Client.");
    String request = client.readStringUntil('\r');
    Serial.println(request);
    client.flush();

    if (request.indexOf("/ON") != -1) {
      digitalWrite(ledPin, HIGH);
    }
    if (request.indexOf("/OFF") != -1) {
      digitalWrite(ledPin, LOW);
    }

    // Webpage response
    client.println("HTTP/1.1 200 OK");
    client.println("Content-type:text/html");
    client.println();

    client.println("<!DOCTYPE html><html>");
    client.println("<head><title>ESP32 LED Control</title></head>");
    client.println("<body><h1>LED Control</h1>");
    client.println("<a href=\"/ON\"><button>Turn ON</button></a>");
    client.println("<a href=\"/OFF\"><button>Turn OFF</button></a>");
    client.println("</body></html>");

    client.println();
    delay(1);
    Serial.println("Client disconnected.");
  }
}
