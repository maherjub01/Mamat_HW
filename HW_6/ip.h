#ifndef IP_H
#define IP_H
#include "string.h"
#include "generic-field.h"

#define SIZE 4
class Ip : public GenericField
{
String my_field;
int Ip_Nums[SIZE];
int bits_to_check;// the number after slash(which bits to take)
bool aux_match(String input);
public:

	Ip(String p);
   
    bool set_value(String packet);
    bool match(String value);//const cause this function is a getter
    
};

#endif 