#include "ESPAsyncWebServer.h"
#include <AsyncTCP.h>
#include <DNSServer.h>
#include <WiFi.h>

#define PORT 80

// #######################
// CAPTIVE REQUEST HANDLER
class CaptiveRequestHandler: public AsyncWebHandler {
public:
  CaptiveRequestHandler() {}
  virtual ~CaptiveRequestHandler() {}

  bool canHandle(AsyncWebServerRequest *req) {
    return true;
  }

  void handleRequest(AsyncWebServerRequest *req) {
    req->send_P(200, "text/html", "<h1>DEFAULT HTML TO CHANGE</h1>");
  }
};
// END CAPTIVE REQUEST HANDLER
// ###########################


// #############
// SERIAL LOGGER
enum LogLevel {
  DEBUG = 0,
  INFO = 1,
  ERROR = 2
};

class SerialLogger {
private:
  LogLevel _lvl;

public:
  SerialLogger(LogLevel l = DEBUG): _lvl(l) {}
  void debug(String s) { if (this->_lvl <= DEBUG) Serial.printf("[d]: %s\n", s.c_str()); }
  void info(String s) { if (this->_lvl <= INFO) Serial.printf("[i]: %s\n", s.c_str()); }
  void error(String s) { if (this->_lvl <= ERROR) Serial.printf("[e]: %s\n", s.c_str()); }
};
// END SERIAL LOGGER
// #################


// #############
// MESSAGE QUEUE
class CommandQueue {
private:
  struct s_cmd_ptr {
    const char *cmd;
    void (CommandQueue::*fct)();
  };
  struct s_cmd_ptr _cmd_ptr[] = {
    { "set_ap", &CommandQueue::setAP },
    { NULL, NULL }
  };

public:
  CommandQueue() {}
  ~CommandQueue() {}

  String[] getNextCommand() {
    String[] res;

    if (Serial.available() > 0) {
      const char *msg = Serial.readString().c_str();
      

    }
  }
};
// END MESSAGE QUEUE
// #################


// ###########
// EVIL SERVER
class EvilApp {
private:
  DNSServer _dns;
  AsyncWebServer *_server;
  SerialLogger _logger;
  CommandQueue _queue;

  void _initRoutes() {
    this->_server->on("/", HTTP_GET, [](AsyncWebServerRequest *req) {
      // Here send a page
      // req->send_P(200, "text/html", "")
    })
  }

public:
  EvilApp() {
    this->_server = new AsyncWebServer(PORT);
  }

  void start() {
    this->_logger.debug("Starting evil app...");
    WiFi.mode(WIFI_AP);
    WiFi.softAP("TODO AP NAME");

    // TODO: init routes here

    this->_dns.start(53, "*", WiFi.softAPIP());
    this->_server->addHandler(new CaptiveRequestHandler()).setFilter(ON_AP_FILTER);
    this->_server->begin();
    
    this->_logger.debug("App started");
  }

  ~EvilApp() {
    delete this->_server;
  }
};
// END EVIL SERVER
// ###############


void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:

}
