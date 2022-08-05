#define TRIGGER1 5
#define ECHO1    4
#include <ESP8266WiFi.h>
//#define BLYNK_PRINT Serial 
//#include <BlynkSimpleEsp8266.h>

const char* ssid = "soms";// username
const char* password = "sunny007"; // password

int WiFiStrength = 0;
WiFiServer server(80);
void setup() 
{
  Serial.begin(9600);
  delay(10);
  pinMode(TRIGGER1, OUTPUT);
  pinMode(ECHO1, INPUT);
  pinMode(BUILTIN_LED, OUTPUT);

  // Connect to WiFi network
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);
  // connect to WiFi router
  while (WiFi.status() != WL_CONNECTED) 
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  // Start the server
  server.begin();
  Serial.println("Server started");
  Serial.print("Use this URL to connect: ");
  Serial.print("http://");
  Serial.print(WiFi.localIP());
  Serial.println("/");
}

 float duration1, distance1,a1;
void loop() 
{

  WiFiStrength = WiFi.RSSI(); // get dBm from the ESP8266
  Serial.print(WiFiStrength); 
  Serial.println("dBm");
  Serial.println(" ");
  delay(1000); // slows amount of data sent via serial
  ///Sensor 1 Readings
   digitalWrite(TRIGGER1, LOW);  // ultrasonic sensor
  delayMicroseconds(2); 
  digitalWrite(TRIGGER1, HIGH);
  delayMicroseconds(10); 
  digitalWrite(TRIGGER1, LOW);;
  duration1 = pulseIn(ECHO1, HIGH);
  Serial.println("Garbage 1");
  distance1 = (duration1/2) / 29.1;
  Serial.println(distance1);
  Serial.println("cm");
  distance1 = ((15-distance1)/15)*100;
  if(distance1>100 ||distance1<0)
  {
    distance1=0;
  }
  Serial.println(distance1);
  Serial.println("%");
 
  // check to for any web server requests. ie - browser requesting a page from the webserver
  WiFiClient client = server.available();
  if (!client) 
  {
    return;
  }

  // Wait until the client sends some data
  Serial.println("new client");

  // Read the first line of the request
  String request = client.readStringUntil('\r');
  Serial.println(request);
  client.flush();

  // Return the response
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println(""); //  do not forget this one
  client.println("<!DOCTYPE HTML>");

  client.println("<html>");
  client.println("  <head>");
   client.println(" <meta charset=\"utf-8\">");
  client.println("<meta http-equiv=\"X-UA-Compatible\" content=\"IE=edge,chrome=1\">");
  client.println("<meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
   client.println("<style>");
    client.println("body {");
     client.println("background: #B0E0E6;");
   client.println("}");

   client.println("canvas {");
     client.println("display: block;");
     client.println("float: left;");
     client.println("margin: 10px auto;");
   client.println("}");
  client.println(" </style>");
       client.println(" <link href=\"http://www.jqueryscript.net/css/jquerysctipttop.css\" rel=\"stylesheet\" type=\"text/css\">");
client.println("<script src=\"http://ajax.googleapis.com/ajax/libs/jquery/2.1.3/jquery.min.js\"></script>");
client.println("<script src=\"http://www.jqueryscript.net/demo/jQuery-Plugin-To-Draw-Animated-Gauges-using-Canvas-2D-API/src/jquery.gauge.js\"></script>");
  client.println("  <script>");
      client.println("setTimeout(function(){");
     client.println("window.location.reload(1);");
 client.println("}, 58000);");///change this value to alter page auto load speed
       client.println("  </script>");
       client.println("  <script>");
    client.print(" $(document).ready(function (){");
    client.print(" $(\"#gauge2\").gauge(");
  client.print(distance1);
   client.print(",{ unit: \"%\",min:0,max:100, color:\"#006400\",font: \"100px verdana\",type: \"halfcircle\"});");
   client.println("  });");
  client.println(" </script>");
       client.println("  </head>");
  client.println("  <body>");
   client.println(" <h1 style=\"margin:20px auto 30px auto; color:#696969;\" align=\"center\">IOT GARBAGE MONITORING DASHBOARD</h1>"); /////Page title
    client.println("<table border=\"1\" align=\"center\"><tr><th>DUSTBIN</th></tr>");
  client.println("<tr>");

  //client.println("<td><canvas id=\"gauge2\" width=\"300\" height=\"200\"></canvas></td>");
         //client.println("<td><canvas id=\"gauge3\" width=\"300\" height=\"200\"></canvas></td>");
     client.println("<td><canvas id=\"gauge2\" width=\"300\" height=\"200\"></canvas></td>");
  client.println("</tr></table>");
  //client.println("</table>");
  client.println("<br><br><table border=\"1\" align=\"center\"><tr><th>DUSTBIN LEVEL INDICATOR </th></tr>");
  client.println("</table>");
  client.print("WiFi Signal Strength: ");
  client.println(WiFiStrength);
  client.println("dBm<br>");
  delay(1);
  Serial.println("Client disonnected");
  Serial.println("");
}


 
