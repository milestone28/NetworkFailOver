#include <ESP8266WiFi.h>
 
//const char* ssid = "failoverBONI";
//const char* password = "P@ssw0rd";

const char* ssid = "garzhouse";
const char* password = "P@ssw0rd";


WiFiServer server(80);
 
void setup() {
  Serial.begin(115200);
  delay(10);
  pinMode(5, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(0, OUTPUT);
  pinMode(13, OUTPUT);
  digitalWrite(5, LOW);
  digitalWrite(4, LOW);
  digitalWrite(0, LOW);
  digitalWrite(13, LOW);
 
  // Connect to WiFi network
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
 
  WiFi.begin(ssid, password);
 //IPAddress ip(10,140,146,11); 
 //IPAddress gateway(10,140,146,1);
 IPAddress ip(192,168,1,200);    
  IPAddress gateway(192,168,1,1);   
  IPAddress subnet(255,255,255,0);   
  WiFi.config(ip, gateway, subnet);
 
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
 
  // Start the server
  server.begin();
  Serial.println("Server started");
 
  // Print the IP address
  Serial.print("Use this URL to connect: ");
  Serial.print("http://");
  Serial.print(WiFi.localIP());
  Serial.println("/");
 
}
 
void loop() {
  // Check if a client has connected
 WiFiClient client = server.available();
   if (!client) {
    return;
  }
 
  // Wait until the client sends some data
  Serial.println("new client");
  while(!client.available()){
   delay(1000);
  }
 
  // Read the first line of the request
  String request = client.readStringUntil('\r');
  Serial.println(request);
  //client.flush();
 
  // Match the request
 
 
  if (request.indexOf("/GLOBE") > 0)  {
    digitalWrite(5, HIGH);
   
  }
  if (request.indexOf("/PLDT") >0)  {
    digitalWrite(5, LOW);
   
  }

   //if (request.indexOf("/light2on") > 0)  {
    //digitalWrite(4, HIGH);
   
 // }
 // if (request.indexOf("/light2off") >0)  {
  //  digitalWrite(4, LOW);
   
 // }
  //  if (request.indexOf("/light3on") >0)  {
  //  digitalWrite(0, HIGH);
   
 // }
 // if (request.indexOf("/light3off") > 0)  {
  //  digitalWrite(0, LOW);
   
 // }
 //  if (request.indexOf("/light4on") > 0)  {
  //  digitalWrite(13, HIGH);
   
//  }
//  if (request.indexOf("/light4off") > 0)  {
  //  digitalWrite(13, LOW);
   
//  }
// Set ledPin according to the request
//digitalWrite(ledPin, value);
 
  // Return the response
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println(""); //  do not forget this one
  client.println("<!DOCTYPE HTML>");
  client.println("<html>");
  client.println("<head>");
  client.println("<meta name='apple-mobile-web-app-capable' content='yes' />");
  client.println("<meta name='apple-mobile-web-app-status-bar-style' content='black-translucent' />");
 client.println("</head>");
  client.println("<body bgcolor = \"#f7e6ec\">"); 
  client.println("<hr/><hr>");
  client.println("<h1><center> Manual Failover Via Network by: Gary Yu </center></h1>");
  client.println("<h5><center> Bonifacio Branch </center></h5>");
  client.println("<hr/><hr>");
  client.println("<br><br>");
  client.println("<br><br>");
  client.println("<center>");
  client.println("<a href=\"/GLOBE\"\"><button>USED GLOBE Lines</button></a>");
  client.println("<a href=\"/PLDT\"\"><button>USED PLDT Lines</button></a><br />"); 
  client.println("<br><br>"); 
  client.println("Please Use it Carefully thanks !");
  client.println("</center>");   
  client.println("<br><br>");
 //  client.println("<center>");
  // client.println("Device 2");
 // client.println("<a href=\"/light2on\"\"><button>Turn On </button></a>");
//  client.println("<a href=\"/light2off\"\"><button>Turn Off </button></a><br />");  
//client.println("</center>"); 
//  client.println("<br><br>");
//    client.println("<center>");
//   client.println("Device 3");
 // client.println("<a href=\"/light3on\"\"><button>Turn On </button></a>");
//  client.println("<a href=\"/light3off\"\"><button>Turn Off </button></a><br />");  
//client.println("</center>"); 
//  client.println("<br><br>");
  // client.println("<center>");
 //  client.println("Device 4");
//  client.println("<a href=\"/light4on\"\"><button>Turn On </button></a>");
//  client.println("<a href=\"/light4off\"\"><button>Turn Off </button></a><br />");  
//client.println("</center>"); 
  client.println("<br><br>");
  client.println("<center>");
  client.println("<table border=\"5\">");
 client.println("<tr>");
  if (digitalRead(5))
         { 
           client.print("<td>STATUS: GLOBE Lines</td>");
        
         }
          else
          {
            client.print("<td>STATUS: PLDT Lines</td>");
      
        }
     
        client.println("<br />");
             
      //   if (digitalRead(4))
       //   { 
        //   client.print("<td>Light 2 is ON</td>");

      //   }
       //   else
       //   {

      //      client.print("<td>Light 2 is OFF</td>");
//
       //   }
      //    client.println("</tr>");


      //    client.println("<tr>");

      //    if (digitalRead(0))

      //    { 
      //     client.print("<td>Light 3 is ON</td>");

     //     }

      //    else

      //    {
       //     client.print("<td>Light 3 is OFF</td>");
        //  }


       //   if (digitalRead(13))


        //  { 


       //    client.print("<td>Light 4 is ON</td>");

      //    }


         // else


       //   {


        //    client.print("<td>Light 4 is OFF</td>");


       //   }

          client.println("</tr>");


          client.println("</table>");

          client.println("</center>");
  client.println("</html>"); 
  delay(1000);
  Serial.println("Client disonnected");
  Serial.println("");
 
}
