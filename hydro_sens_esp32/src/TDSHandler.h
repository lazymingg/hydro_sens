#ifndef TDS_HANDLER_H
#define TDS_HANDLER_H

#include <EEPROM.h>
#include "GravityTDS.h"

#define TDS_FIELD 3

#include "TDSHandler.h"

class TDSHandler {
private:
    GravityTDS gravity_tds;
    ThingTalk thing_talk(TDS_FIELD);

public:
    TDSHandler(int tds_pin);
    void update(float temperature);
    float getValue();
    void sendToCloud();
};

#endif // TDS_HANDLER_H
