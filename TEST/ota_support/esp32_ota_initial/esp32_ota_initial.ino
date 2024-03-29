// WIFI
#include <WiFi.h>
#include <WiFiClient.h>
int status = WL_IDLE_STATUS;     // the Wifi radio's status
const char* ssid = "SSID";  // SSID Wifi / Hotspot
const char* password = "SSIDPASSWORD"; // Password Wifi / Hotspot
WiFiClient client;

//OTA
#include <WebServer.h>
#include <ESPmDNS.h>
#include <Update.h>
WebServer server(80);
const char* host = "rino-esp32"; // nama-esp32

///////////////////////////////////////////////////LAYOUT PAGE LOGIN OTA///////////////////////////////////////////////////////////////////
/* Style */
String style =
  "<style>#file-input,input{width:100%;height:44px;border-radius:4px;margin:10px auto;font-size:15px}"
  "input{background:#f1f1f1;border:0;padding:0 15px}body{background:#3498db;font-family:sans-serif;font-size:14px;color:#777}"
  "#file-input{padding:0;border:1px solid #ddd;line-height:44px;text-align:left;display:block;cursor:pointer}"
  "#bar,#prgbar{background-color:#f1f1f1;border-radius:10px}#bar{background-color:#3498db;width:0%;height:10px}"
  "form{background:#fff;max-width:258px;margin:75px auto;padding:30px;border-radius:5px;text-align:center}"
  ".btn{background:#3498db;color:#fff;cursor:pointer}</style>";

/* Login page */
String loginIndex =
  "<form name=loginForm>" // Nama Form Login
  "<h1>OTA ESP32S</h1>"
  "<input name=userid placeholder='User ID'> "
  "<input name=pwd placeholder=Password type=Password> "
  "<input type=submit onclick=check(this.form) class=btn value=Login></form>"
  "<script>"
  "function check(form) {"
  "if(form.userid.value=='rino' && form.pwd.value=='password')" //Username & Password Login OTA
  "{window.open('/serverIndex')}"
  "else"
  "{alert('Error Password or Username')}" // Ketika Gagal Login
  "}"
  "</script>" + style;

/* Server Index Page */
String serverIndex =
  "<script src='https://ajax.googleapis.com/ajax/libs/jquery/3.2.1/jquery.min.js'></script>"
  "<form method='POST' action='#' enctype='multipart/form-data' id='upload_form'>"
  "<input type='file' name='update' id='file' onchange='sub(this)' style=display:none>"
  "<label id='file-input' for='file'>   Choose file...</label>"
  "<input type='submit' class=btn value='Update'>"
  "<br><br>"
  "<div id='prg'></div>"
  "<br><div id='prgbar'><div id='bar'></div></div><br></form>"
  "<script>"
  "function sub(obj){"
  "var fileName = obj.value.split('\\\\');"
  "document.getElementById('file-input').innerHTML = '   '+ fileName[fileName.length-1];"
  "};"
  "$('form').submit(function(e){"
  "e.preventDefault();"
  "var form = $('#upload_form')[0];"
  "var data = new FormData(form);"
  "$.ajax({"
  "url: '/update',"
  "type: 'POST',"
  "data: data,"
  "contentType: false,"
  "processData:false,"
  "xhr: function() {"
  "var xhr = new window.XMLHttpRequest();"
  "xhr.upload.addEventListener('progress', function(evt) {"
  "if (evt.lengthComputable) {"
  "var per = evt.loaded / evt.total;"
  "$('#prg').html('progress: ' + Math.round(per*100) + '%');"
  "$('#bar').css('width',Math.round(per*100) + '%');"
  "}"
  "}, false);"
  "return xhr;"
  "},"
  "success:function(d, s) {"
  "console.log('success!') "
  "},"
  "error: function (a, b, c) {"
  "}"
  "});"
  "});"
  "</script>" + style;

//////////////////////////////////////////////////////FINISHED LAYOUT PAGE LOGIN///////////////////////////////////////////////////////////

//LED setup
#define LED_PIN 2
int ledState = HIGH;
unsigned long lastMillis = 0;
unsigned long ledInterval = 1000;

void setup() {
  Serial.begin(115200);
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, ledState);
  wifiInit();
  openOTA();
  lastMillis = millis();
}

void loop() {
  server.handleClient();
  delay(1);
  if(millis()- lastMillis >= ledInterval)
  {
    ledState = !ledState;
    digitalWrite(LED_PIN, ledState);
    lastMillis = millis();
  }
}
