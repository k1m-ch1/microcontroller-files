#include "logging.h"
#include "nec.h"

//LogMessage logMessage;

void setup(){
  loggingInit();
  necInit();
}

void loop(){
  /*
  logMessage.timestamp = millis();
  logMessage.logSource = NEC;
  sprintf(logMessage.text, "hello world");
  xQueueSend(logQueueHandle, &logMessage, 0);
  delay(1000);
*/
}
