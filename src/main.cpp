#include "Arduino.h"

struct button_map {
    int pin;
    int key;
};

#define BUTTON_COUNT (sizeof(maps) / sizeof(maps[0]))
const struct button_map maps[] = {
    { 16, KEY_D },
    { 17, KEY_E },
    { 18, KEY_W },
    { 19, KEY_Q },
    { 20, KEY_A },
    { 21, KEY_Z },
    { 22, KEY_X },
    { 23, KEY_C },
};

int timeouts[BUTTON_COUNT] = {};
bool states[BUTTON_COUNT] = {};

#define TIMEOUT 20

void setup() {
    for (size_t i = 0; i < BUTTON_COUNT; i++) {
        pinMode(maps[i].pin, INPUT_PULLUP);
    }
}

void loop() {
    for (size_t i = 0; i < BUTTON_COUNT; i++) {
        if (timeouts[i] > TIMEOUT) {
            bool s = digitalReadFast(maps[i].pin);
            if (s != states[i]) {
                states[i] = s;
                timeouts[i] = 0;
                if (s) {
                    // if high
                    Keyboard.release(maps[i].key);
                }
                else {
                    // if low
                    Keyboard.press(maps[i].key);
                }
            }
        }
        else {
            timeouts[i]++;
        }
    }
    delay(1);
}
