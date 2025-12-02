#include "ThingTalk.h"

ThingTalk::ThingTalk(int _field) {
    ENVReader envReader;
    this->API_KEY_READ = envReader.get("API_KEY_READ");
    this->API_KEY_WRITE = envReader.get("API_KEY_WRITE");
    this->CHANNEL = envReader.get("CHANNEL");

    this->field = _field;
}

float ThingTalk::get() {
    return ThingSpeak.readField(CHANNEL, field, API_KEY_READ);
}

int ThingTalk::send(float value) {
    return ThingSpeak.writeField(CHANNEL, field, value, API_KEY_WRITE);
}
