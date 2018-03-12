
void handleRoot() {
  char temp[400];
  int sec = millis() / 1000;
  int min = sec / 60;
  int hr = min / 60;

  snprintf ( temp, 400,

"<html>\
  <head>\
    <meta http-equiv='refresh' content='5'/>\
    <title>ESP8266 Demo</title>\
    <style>\
      body { background-color: #cccccc; font-family: Arial, Helvetica, Sans-Serif; Color: #000088; }\
    </style>\
  </head>\
  <body>\
    <h1>Hello from ESP8266!</h1>\
    <p>Uptime: %02d:%02d:%02d</p>\
    <img src=\"/test.svg\" />\
  </body>\
</html>",

    hr, min % 60, sec % 60
  );
  server.send ( 200, "text/html", temp );
}

void handleNotFound() {

  String message = "File Not Found\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += ( server.method() == HTTP_GET ) ? "GET" : "POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";

  for ( uint8_t i = 0; i < server.args(); i++ ) {
    message += " " + server.argName ( i ) + ": " + server.arg ( i ) + "\n";
  }

  server.send ( 404, "text/plain", message );
  
}


void drawGraph() {
  String out = "";
  char temp[100];
  out += "<svg xmlns=\"http://www.w3.org/2000/svg\" version=\"1.1\" width=\"400\" height=\"150\">\n";
  out += "<rect width=\"400\" height=\"150\" fill=\"rgb(250, 230, 210)\" stroke-width=\"1\" stroke=\"rgb(0, 0, 0)\" />\n";
  out += "<g stroke=\"black\">\n";
  int y = rand() % 130;
  for (int x = 10; x < 390; x+= 10) {
    int y2 = rand() % 130;
    sprintf(temp, "<line x1=\"%d\" y1=\"%d\" x2=\"%d\" y2=\"%d\" stroke-width=\"1\" />\n", x, 140 - y, x + 10, 140 - y2);
    out += temp;
    y = y2;
  }
  out += "</g>\n</svg>\n";

  server.send ( 200, "image/svg+xml", out);
}



// myDFPlayer.play(1);  
void handlePlay() {
  
  String track = server.arg("track");
  if (track.length() > 0 ) {
    
    int trackNumber = track.toInt();
    myDFPlayer.play(trackNumber);  
    
    content = "{\"play\":\"";
    content +=  track;
    content += "\"}";
    server.send(200, "application/json", content);  
    
  } else {
    content = "{\"Error\":\"404 not found\"}";
    server.send(404, "application/json", content);
  }
}




// myDFPlayer.pause();
// myDFPlayer.start(); 
void handlePause() {
  
  String state = server.arg("state");
  if (state.length() > 0 ) {
    
    int stateInt = state.toInt();

    if ( stateInt > 0 ) {
      myDFPlayer.start();  
    } else {
      myDFPlayer.pause();
    }
    
    content = "{\"pause\":\"";
    content +=  stateInt;
    content += "\"}";
    server.send(200, "application/json", content);  
    
  } else {
    content = "{\"Error\":\"404 not found\"}";
    server.send(404, "application/json", content);
  }
}


// myDFPlayer.volume(10);
// myDFPlayer.volumeUp();
// myDFPlayer.volumeDown();
void handleVolume() {
  
  String level = server.arg("level");
  if (level.length() > 0 ) {

    int levelInt = level.toInt();
    if ( levelInt >=0 && levelInt <= 30 ) {
      myDFPlayer.volume(levelInt); 
      content = "{\"volume\":\"";
      content +=  levelInt;
      content += "\"}";
      server.send(200, "application/json", content);  
    } else {
      content = "{\"Error\":\"volume level out of bounds\"}";
      server.send(404, "application/json", content);
    } 
    
  } else {
    content = "{\"Error\":\"404 not found\"}";
    server.send(404, "application/json", content);
  }
}

