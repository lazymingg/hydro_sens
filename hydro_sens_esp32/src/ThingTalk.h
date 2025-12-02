#ifndef THING_TALK_H
#define THING_TALK_H

#include "ENVReader.h"
#include <string>

class ThingTalk {
private:
    std::string API_KEY_READ;
    std::string API_KEY_WRITE;
    unsigned long CHANNEL;
    int field;
    
public:
    ThingTalk(int _field);
    float get();
    int send(float value);
};

#endif // THING_TALK_H
