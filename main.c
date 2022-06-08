#include "ui.h"
#include "bus.h"

#define WIDTH 700
#define HEIGHT 700


int main() {

    struct ui_t* ui = ui_init(WIDTH,HEIGHT);
    struct bus_t* bus = bus_init();




    while (ui->run){

        ui = ui_handle(ui);
        ui = ui_render(ui, bus);

    }

    free(ui);
    return 0;
}
