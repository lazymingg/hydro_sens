#ifndef TDS_HANDLER_H
#define TDS_HANDLER_H

#include <EEPROM.h>
#include <GravityTDS.h>

class TDSHandler {
private:
    GravityTDS gravity_tds;
    int TDS_FIELD=3;
public:
    TDSHandler(int tds_pin);
    void begin();
    void update(int temperature);
    float getTDS();
    int getField();
};

#endif // TDS_HANDLER_H