#include "ip.h"
#include <iostream>
#include <stddef.h>
#include "string.h"

const int MAX_INTERVAL=255;
const int BITS_NUM=32;
const int BYTES=8;
const int DOTS_SIZE=3;
const int SLASH_SIZE=1;
const int IP_NUMS=4;

Ip::Ip(String p) : my_field(p) {

    for (int i = 0; i < IP_NUMS; i++) {
        this->Ip_Nums[i] = -1;
    }
    this->bits_to_check = 0;
}

int Bits_To_Check(int check_bits, int value) {

    int aux = value;
    for (int i = 0; i < (BYTES - check_bits); i++) {
        aux = aux / 2;
    }
    return aux;
}

bool Ip::set_value(String packet) {

    char dots_delim[] = ".";
    char slash_delim[] = "/";

    String *dots = nullptr;
    String *slash = nullptr;

    size_t dots_num = DOTS_SIZE;
    size_t slash_num = SLASH_SIZE;
   
    packet.split(dots_delim, &dots, &dots_num);
    packet.split(slash_delim, &slash, &slash_num);
  
    // Checking if the bits 
    if (slash[1].to_integer() > BITS_NUM || slash[1].to_integer() < 0) {

        delete[] dots;
        delete[] slash;
        return false;
    }

    // Checking if our ip numbers are in the legal range
    int i = 0;

    while(i < (int)dots_num){
         if (dots[i].to_integer() < 0 || dots[i].to_integer() > MAX_INTERVAL){
            delete[] slash;
            delete[] dots;
            return false;
         }

          i++;
    }


    int j = 0;

    while( j < (int)dots_num){

         this->Ip_Nums[j] = dots[j].to_integer();
         j++;
    }

    this->bits_to_check = slash[1].to_integer();


    delete[] dots;
    delete[] slash;

    return true;
}



bool Ip::aux_match(String value) {

    char dots_delim[] = ".";
    int check_bits = this->bits_to_check;
    String *dots = nullptr;
    value = value.trim();

    int aux_split_Dots[IP_NUMS];
    for (int i = 0; i < IP_NUMS; i++) {
        aux_split_Dots[i] = this->Ip_Nums[i];
    }
    size_t dots_num = DOTS_SIZE;
    value.split(dots_delim, &dots, &dots_num);

    if (check_bits == 0) {
        
        delete[] dots;
        return true;
    }
   
    for (int i = 0; check_bits > 0; i++) {

        if (check_bits >= BYTES) {

            if (dots[i].to_integer() != Ip_Nums[i]){
                return false;
            }
        } 
        else {

            if (Bits_To_Check(check_bits, dots[i].to_integer()) !=
                Bits_To_Check(check_bits, aux_split_Dots[i])) {

            delete[] dots;
            return false;
            }
        }

    check_bits -= BYTES;
    }

    delete[] dots;
    return true;
}

bool Ip::match(String input) {
    
    size_t len;
    bool value = false;
    String *aux_split = nullptr;

    input.split("=, ", &aux_split, &len);

    if (!len) {

        delete[] aux_split;
        return false;
    }

    for (size_t i = 0; i < len; i += 2) {

        if (my_field.equals(aux_split[i])) {

            value = aux_match(aux_split[i + 1]);
            break;
        }
    }
    delete[] aux_split;
    return value;
}