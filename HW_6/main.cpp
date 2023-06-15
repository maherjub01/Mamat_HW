#include <iostream>
#include "port.h"
#include "ip.h"
#include "input.h"
#include "string.h"


int main(int argc, char** argv) {



    if (check_args(argc, argv)) {
        
        return -1;
    }


    String trim_arr = String(argv[1]);
    trim_arr = trim_arr.trim();
    char delimiters[2] = {'=', ','};
    String* dst_src_arr = nullptr;
    size_t length = 0;

    trim_arr.split(delimiters, &dst_src_arr, &length);

    if (dst_src_arr[0].equals("dst-ip")) {

        Ip dst_ip("dst-ip");
        dst_ip.set_value(dst_src_arr[1]);
        parse_input(dst_ip);
    }

    if (dst_src_arr[0].equals("src-ip")) {

        Ip src_ip("src-ip");
        src_ip.set_value(dst_src_arr[1]);
        parse_input(src_ip);
    }

    if (dst_src_arr[0].equals("src-port")) {

        Port src_port("src-port");
        src_port.set_value(dst_src_arr[1]);
        parse_input(src_port);
    }

    if (dst_src_arr[0].equals("dst-port")) {

        Port dst_port("dst-port");
        dst_port.set_value(dst_src_arr[1]);
        parse_input(dst_port);
    }


    delete[] dst_src_arr;

    return 0;
}
