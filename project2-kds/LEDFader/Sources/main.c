#include "mbed.h"

int main() {
    DigitalOut gpo(PTB8);
    DigitalOut led(LED_RED);

    while (true) {
        gpo = 1;
        led = 1; // Off
        wait(2);
        gpo = 0;
        led = 0; // on
        wait(2);
    }
}
