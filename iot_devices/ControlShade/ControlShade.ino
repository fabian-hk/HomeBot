#include <WiFi.h>

// up, hold, down, led
byte output[4] = {16, 17, 18, 19};

// window shade 0, shade 1, shade 2, led
byte state[4] = {100, 100, 100, 0};

// time to move the shade from up to down
const float TIME = 20000.0;

const short LED_TIMEOUT = 4000;

const short HIGH_PHASE = 100;

byte action = 255;
byte a = 255;
byte b = 255;
byte c = 255;

// Wifi variables
const char* ssid     = "";
const char* password = "";

byte wifi_retry = 0;

// variable for LDR
byte ldrPin = 34;
short val;

WiFiServer server(8448);

void setup() {
  Serial.begin(115200);

  // initialize output ports
  for(byte i=0; i<4; i++) {
    pinMode(output[i], OUTPUT);
    digitalWrite(output[i], LOW);
  }

  // configure analog input
  analogReadResolution(12);

  // setup the TCP socket
  delay(100);

  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  checkWifiConnect();

  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  
  server.begin();
}

void loop() {
    // check if WIFI ist still connected
    checkWifiConnect();
  
    // control through server
    WiFiClient client = server.available();

    if (client) {
      Serial.println("New Client.");
      client.write("shade");

      // check which action is requested
      while(client.connected()) {
        if (client.available() > 0) {
          action = client.read();
          break;
        } else {
          delay(100);
        }
      }
      Serial.println(action);

      if(action == 0) {
        while (client.connected()) {
          if (client.available() >= 3) {
            a = client.read();
            Serial.print("a: ");
            Serial.println(a);
            b = client.read();
            Serial.print("b: ");
            Serial.println(b);
            c = client.read();
            Serial.print("c: ");
            Serial.println(c);
            break;
          }
        }
        client.write(byte(0));        
        Serial.println("Client Disconnected.");
        if(a != 255 && b != 255 && c != 255) {
          control(a, b, c);
          Serial.println("Finished");
          a = 255;
          b = 255; 
          c = 255;
        } 
      } else if (action == 1) {
        client.write(state, 3);
      }
      client.stop();
      action = 255;
      Serial.println("Client disconnected");
    }
   
    // control through LDR
    val = analogRead(ldrPin);    
    if(val < 800 && state[0] == 0 && state[1] == 20 && state[2] == 0) {
      control(99, 100, 100);
      Serial.println("Finished");
    }
}

/**
 * Checks if wifi is connected and connect if it's
 * not connected.
 */
void checkWifiConnect() {
    while(WiFi.status() != WL_CONNECTED) {
      WiFi.disconnect();
      Serial.println("Try connecting to wifi");
      // connect with wifi
      WiFi.begin(ssid, password);
      delay(500);
      wifi_retry = 0;
      // waiting for reconnection
      while(WiFi.status() != WL_CONNECTED) {
        wifi_retry++;
        if(wifi_retry == 10) {
          break;
        }
        Serial.print(".");
        delay(500);
      }
      Serial.println();
  }
}


/*
 * Move all window shades in the given position.
 */
void control(byte a, byte b, byte c) {
  // calculate the distance in which the window shade has to be moved
  short in[3] = {a - state[0], b - state[1], c - state[2]};
  for(byte j=0; j<3; j++) {
    Serial.print("Windows: ");
    Serial.print(j);
    Serial.print(" state: ");
    Serial.print(state[j]);
    Serial.print(" down: ");
    Serial.println(in[j]);
  }
  
  // sort elements from highest to lowest
  byte con[3];
  if(((abs(in[0]) <= abs(in[1]) && abs(in[0]) <= abs(in[2])) || a == 100 || a == 0) && b != 100 && b != 0 && c != 100 && c != 0) {
    con[0] = 0;
    if(((abs(in[1]) <= abs(in[2])) || b == 100) && c != 100 && c != 0) {
      con[1] = 1;
      con[2] = 2;
    } else {
      con[1] = 2;
      con[2] = 1;
    }
  }
  else if(((abs(in[1]) <= abs(in[0]) && abs(in[1]) <= abs(in[2])) || b == 100 || b == 0) && c != 100 && c != 0) {
    con[0] = 1;
    if(((abs(in[0]) <= abs(in[2])) || a == 100) && c != 100 && c != 0) {
      con[1] = 0;
      con[2] = 2;
    } else {
      con[1] = 2;
      con[2] = 0;
    }
  }
  else if((abs(in[2]) <= abs(in[0]) && abs(in[2]) <= abs(in[1])) || c == 100 || c == 0) {
    con[0] = 2;
    if(((abs(in[1]) <= abs(in[0])) || b == 100) && a != 100 && a != 0) {
      con[1] = 1;
      con[2] = 0;
    } else {
      con[1] = 0;
      con[2] = 1;
    }
  }

  // move all window shades in the given position
  for(byte i=0; i < 3; i++) {
    controlOne(con[i], in[con[i]]);
  }  
}

/*
 * Moves one window shade in the given position.
 */
void controlOne(byte shade, short down) {  
  if((state[shade] + down) == 100 && down != 0) {
    // switch controlle mode to the current window
    toLEDState(shade);
  
    // move shade fully down
    moveUpOrDown(2, down, shade);
    
  } else if((state[shade] + down) == 0 && down != 0) {
    // switch controlle mode to the current window
    toLEDState(shade);

    // move shade fully up
    moveUpOrDown(0, down, shade);
    
  } else if(down > 0 && abs(down) > 10) { 
    // switch controlle mode to the current window
    toLEDState(shade);
    
    // move shade in given position
    moveShade(2, down, shade);
    
  } else if (down < 0 && abs(down) > 10) {
    // switch controlle mode to the current window
    toLEDState(shade);

    // move shade in given position
    moveShade(0, down, shade);
  }
}

/*
 * Control the remote to move the window shade
 * to a given position.
 */
void moveShade(byte d, short down, byte shade) {
    int delay_time = delayTime(down, state[shade]);
    Serial.print("Window: ");
    Serial.print(shade);
    Serial.print(" move. Time: ");
    Serial.print(delay_time);
    Serial.print(" Direction: ");
    Serial.println(down);
    digitalWrite(output[d], HIGH);
    delay(HIGH_PHASE);
    digitalWrite(output[d], LOW);
    delay(delay_time);
    digitalWrite(output[1], HIGH);
    delay(HIGH_PHASE);
    digitalWrite(output[1], LOW);
    state[shade] += down;
    delay(LED_TIMEOUT);      
}

/*
 * Move a window shade fully up or down.
 */
void moveUpOrDown(byte d, short down, byte shade) {
    Serial.print("Window: ");
    Serial.print(shade);
    Serial.println(" fully");
    digitalWrite(output[d], HIGH);
    delay(HIGH_PHASE);
    digitalWrite(output[d], LOW);
    state[shade] += down;
    delay(LED_TIMEOUT);
}


/*
 * Calculates the time the window shade has to move.
 * Its not a linear process.
 */
int delayTime(short down, byte s) {
  int t = (abs(down)/100.0) * TIME;
  if(s == 100) {
    t += 10000;
  }
  return t;
}


/*
 * Switches the remote state to the state given
 * by s.
 */
void toLEDState(byte s) {
  Serial.print("\tLED state: ");
  Serial.println(state[3]);
  Serial.print("\tShade: ");
  Serial.println(s);
  if(state[3] != s) {
    digitalWrite(output[3], HIGH);
    delay(HIGH_PHASE);
    digitalWrite(output[3], LOW);
    delay(200);
    while(state[3] != s) {
      digitalWrite(output[3], HIGH);
      delay(HIGH_PHASE);
      digitalWrite(output[3], LOW);
      delay(200);  
      state[3] = (state[3] + 1) % 6;
      Serial.print("LED state: ");
      Serial.println(state[3]);
    }
  }
}
