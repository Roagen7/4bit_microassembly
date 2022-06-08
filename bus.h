#ifndef BUS_H
#define BUS_H

#include <inttypes.h>
#include <stdlib.h>

#define INSTRUCTIONS 32
#define ORDER 8

#define RAM_SIZE ORDER+INSTRUCTIONS

struct bus_t {

    union {

        struct {

            uint8_t instructions[INSTRUCTIONS];
            uint8_t order[ORDER];

        };

        uint8_t ram[RAM_SIZE];

    };

    uint8_t RA, RB, RC, RI, RO;


    uint8_t input_microcycle;
    uint8_t selected_cycle;
    uint8_t selected_microcycle;
};


struct bus_t* bus_init();


#endif
