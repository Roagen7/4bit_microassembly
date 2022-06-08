#ifndef UI_H
#define UI_H

#include <SDL.h>
#include <stdlib.h>

#include "bus.h"

struct ui_t {

    SDL_Window* window;
    SDL_Renderer* renderer;

    SDL_Texture* charset;

    uint16_t width, height;

    uint8_t run;


};



struct ui_t* ui_init(uint16_t width, uint16_t height);


struct ui_t* ui_draw_string(struct ui_t* ui, const char* str, uint16_t posx, uint16_t posy, uint8_t scale);

struct ui_t* ui_handle(struct ui_t* ui);
struct ui_t* ui_update(struct ui_t* ui);
struct ui_t *ui_render(struct ui_t *ui, struct bus_t* bus);



#endif
