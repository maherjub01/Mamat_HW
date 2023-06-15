#include "port.h"
#include <iostream>
#include <stddef.h>
#include "string.h"


#define VALID_SIZE 2
#define MAX_PORT 65535
#define MIN_PORT 0


Port::Port(String pkt) : my_field(pkt) {
    port_range[0] = 0;
    port_range[1] = 0;
}

bool Port::set_value(String packet){

    String *substr = new String[2];
    size_t size = 0;
    packet.split("-", &substr, &size);

    if ((int)size != VALID_SIZE){

        if((int)size != 0) {
            delete[] substr;
        }

        return false;
    }

    port_range[0] = substr[0].trim().to_integer();
    port_range[1] = substr[1].trim().to_integer();
    delete[] substr;

    if (port_range[0] > port_range[1] || port_range[0] < MIN_PORT || 
        port_range[1] > MAX_PORT)
    {
        return false;
    }
    return true ;
}

bool Port::aux_match(String value) {
    int port = (value.trim()).to_integer();
    return (port >= port_range[0]) && (port <= port_range[1]);
}

bool Port::match(String input) {
    size_t length;
    bool result = false;
    String *input_fields;

    input.split("=, ", &input_fields, &length);

    if (length == 0) {
        delete[] input_fields;
        return false;
    }

    for (size_t i = 0; i < length; i += 2) {
        if (my_field.equals(input_fields[i])) {
            result = aux_match(input_fields[i + 1]);
            break;
        }
    }

    delete[] input_fields;
    return result;
}