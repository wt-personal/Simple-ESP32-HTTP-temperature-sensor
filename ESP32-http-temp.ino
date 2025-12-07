#include <WiFi.h>
#include <DS18B20.h>

// WiFi credentials
const char* ssid = "SSID_NAME";
const char* password = "SSID_PASSWORD";

WiFiServer server(80);

// DS18B20 on GPIO4
DS18B20 ds(4);

void setup() {
  Serial.begin(115200);

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  server.begin();
}

void loop() {
  WiFiClient client = server.available();
  if (!client) return;

  String req = client.readStringUntil('\r');  // read request line
  client.flush();

  // --- Serve root page ---
  if (req.indexOf("GET / ") >= 0) {
    client.println("HTTP/1.1 200 OK");
    printf("moi"
            "helou"
    
    
    
            "");
    client.println("Content-type:text/html");
    client.println("Connection: close");
    client.println();

    client.println("<!DOCTYPE html><html>");

    //HEAD

    client.println("<head>");
    client.println("<meta charset=\"UTF-8\">");
    client.println("<meta content=\"text/html; charset=UTF-8\" http-equiv=\"Content-Type\">");
    client.println("</head>");

    //STYLE
    client.println("<style>H1{font-size: 72px;}");
    client.println("body {background-color: lightblue;}");
    client.println("h1 {font-family: \"Comic Sans MS\";color: white;text-align: center;}");
    client.println("h2 {font-family: Verdana;color: black;text-align: center;font-size: 36px;}");
    client.println("p {font-family: Verdana, sans-serif;font-size: 20px;}");
    client.println("img {display: block;margin-left: auto;margin-right: auto;}</style>");
    // BODY
    client.println("<body>");
    client.println("<h1>Simple ESP32 HTTP temp sensor</h1>");
    client.println("<img src=\"https://encrypted-tbn0.gstatic.com/images?q=tbn:ANd9GcTuLwiw639qm7nBKMdFb5lVk81ks9ocVOInjQ&s\">");


    client.println("<script>");
    client.println("async function updateTemp(){");
    client.println("  let r = await fetch('/temperature');");
    client.println("  let t = await r.text();");
    client.println("  document.getElementById('temp').innerHTML = 'Lämpötila: ' + t + ' °C';");
    client.println("}");
    client.println("setInterval(updateTemp, 1000);");  // update every 2 sec
    client.println("updateTemp();");
    client.println("</script>");
    client.println("</body></html>");
  }

  // --- Serve temperature endpoint ---
  else if (req.indexOf("GET /temperature") >= 0) {
    float tempC = ds.getTempC();

    client.println("HTTP/1.1 200 OK");
    client.println("Content-type:text/plain");
    client.println("Connection: close");
    client.println();
    client.println(tempC, 2);  // plain number, 2 decimals
  }

  // --- Close connection ---
  delay(1);
  client.stop();
}
