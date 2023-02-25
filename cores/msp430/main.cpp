#include <Arduino.h>
#include "api/HardwareSerial.h"

int main(void){
    init();
    setup();
    while(1){
        loop();
        if (arduino::serialEventRun) arduino::serialEventRun();
    }
    return 0;
}
