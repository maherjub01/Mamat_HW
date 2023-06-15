#ifndef PORT_H
#define PORT_H


#include "generic-field.h"
#include "string.h"

#define SIZE_PORT 2

class Port : public GenericField
{
String my_field;
public:
    Port(String pkt);
    int port_range[SIZE_PORT];
    bool aux_match(String input);
    bool set_value(String packet);
    bool match(String value);
};

#endif 