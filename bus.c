#include "bus.h"

struct bus_t* bus_init(){

    static struct bus_t* bus = NULL;

    if(bus == NULL){

        bus = (struct bus_t*) malloc(sizeof(struct bus_t));
        for(int i = 0; i < RAM_SIZE; i++) bus->ram[i] = 0;
        bus->RA = 0;
        bus->RB = 0;
        bus->RC = 0;
        bus->RI = 0;
        bus->RO = 0;
        bus->selected_cycle = 0;
        bus->selected_microcycle = 0;
        bus->input_microcycle = 0;

    }

    return bus;

}