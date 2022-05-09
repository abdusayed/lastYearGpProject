/*
 Basic ESP8266 MQTT example
 This sketch demonstrates the capabilities of the pubsub library in combination
 with the ESP8266 board/library.
 It connects to an MQTT server then:
  - publishes "hello world" to the topic "outTopic" every two seconds
  - subscribes to the topic "inTopic", printing out any messages
    it receives. NB - it assumes the received payloads are strings not binary
  - If the first character of the topic "inTopic" is an 1, switch ON the ESP Led,
    else switch it off
 It will reconnect to the server if the connection is lost using a blocking
 reconnect function. See the 'mqtt_reconnect_nonblocking' example for how to
 achieve the same result without blocking the main loop.
 To install the ESP8266 board, (using Arduino 1.6.4+):
  - Add the following 3rd party board manager under "File -> Preferences -> Additional Boards Manager URLs":
       http://arduino.esp8266.com/stable/package_esp8266com_index.json
  - Open the "Tools -> Board -> Board Manager" and click install for the ESP8266"
  - Select your ESP8266 in "Tools -> Board"
*/

#include <WiFi.h>
#include <PubSubClient.h>


#define RXD2 16
#define TXD2 17
#define MSG_BUFFER_SIZE  (200)
// Update these with values suitable for your network.

const char* ssid =  "Moouniir1998";
const char* password ="m0h@m3dm0un1r19";
//const char* mqtt_server = "broker.mqtt-dashboard.com";
const char* mqtt_server = "broker.hivemq.com";


int received_data[16] = {0} , Event_number ;
long int Dtc_number;
char i = 0 ;

WiFiClient espClient;
PubSubClient client(espClient);
unsigned long lastMsg = 0;
char msg[MSG_BUFFER_SIZE];
int value = 0;

void setup_wifi() {

  delay(10);
  // We start by connecting to a WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }


  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();

  // Switch on the LED if an 1 was received as first character
  if ((char)payload[0] == '0') {
    digitalWrite(2, LOW);   // Turn the LED on (Note that LOW is the voltage level
    // but actually the LED is on; this is because
    // it is active low on the ESP-01)
  } else {
    digitalWrite(2, HIGH);  // Turn the LED off by making the voltage HIGH
  }

}

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Create a random client ID

    // Attempt to connect
    if (client.connect("ESP32")) {
      Serial.println("connected");
      // Once connected, publish an announcement...
      // ... and resubscribe
      client.subscribe("event");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

void setup() {
  pinMode(2, OUTPUT);     // Initialize the BUILTIN_LED pin as an output
  Serial.begin(115200);
  setup_wifi();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
  Serial2.begin(115200, SERIAL_8N1, RXD2, TXD2);
}
long int get_power( int base , int exp)
{
    long int result =  1 ;
    int i ;
    for (i=exp; i>0; i--)
    {
      result = result * base;
    }
    return result ;
   
}
char statuss ;
/*****************
 * Event Frame   *
 *****************/
/********************************************************************************************************************/
/*  Event ID 2 bytes    |  5 byte dtc  |  1 byte erroeStatusChanged | 1 byte occurrence  | 1 byte DemEventAvailable */
/********************************************************************************************************************/
void loop() {


  if (!client.connected()) {
    reconnect();
    client.publish("event", msg);
  }
   while(Serial2.available())
  {
  
    Serial.print("while ");
    received_data[i] = Serial2.read() ;
    
    Serial.println(received_data[i]);
    Serial.println();
    if(received_data[i] >= 0 )
    {
      i++;
    } 
    if( i == 7 )
    {
    /*  Event_number = received_data[0] *256 + received_data[1];
      Dtc_number    = received_data[10]                     \
                    + received_data[9]*(16)                \
                    + received_data[8]*(get_power(16,2))    \
                    + received_data[7]*(get_power(16,3))    \
                    + received_data[6]*(get_power(16,4))    \
                    + received_data[5]*(get_power(16,5))    \
                    + received_data[4]*(get_power(16,6))    \
                    + received_data[3]*(get_power(16,7))    \
                    + received_data[2]*(get_power(16,8))    ; */
      Event_number  =  ( received_data[1] << 8 ) | (received_data[0])  ;
      Dtc_number    =  (received_data[5] << 24)  | (received_data[4] << 16 )| (received_data[3]<< 8 )| ( received_data[2] );
      
      client.loop(); 
      snprintf (msg, 
      500,
      "Event number : %ld \nDTC number : %1d   \nDemEventAvailable : %1d \n"
      ,Event_number , Dtc_number , received_data[6] );
      Serial.print("Publish message: ");
      Serial.println(msg);
      client.publish("event", msg);
      i = 0 ;
    }
    
    
  }
   
   
    
   
    
  
  

}
