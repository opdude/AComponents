#include <stdarg.h>
#include <Arduino.h>
#include "ArduinoUtils.h"

void ArduinoUtils::print(char *fmt, ... ){
        char tmp[255]; // resulting string limited to 255 chars
        va_list args;
        va_start (args, fmt );
        vsnprintf(tmp, 128, fmt, args);
        va_end (args);
        Serial.print(tmp);
}