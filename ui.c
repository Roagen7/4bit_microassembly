#include "ui.h"


#define BIT3_TO_BINARY_PATTERN "%c%c%c"
#define BIT4_TO_BINARY_PATTERN "%c%c%c%c"

#define SPRINTF_REGISTER(x,r) sprintf(r, "R%c %c%c%c%c", x, BIT4_TO_BINARY(bus->r));
#define DRAW_REGISTER(r, y) ui = ui_draw_string(ui,r , 2 * ui->width / 3, y, 3);


#define BIT2_TO_BINARY(byte) \
  (byte & 0x02 ? '1' : '0'), \
  (byte & 0x01 ? '1' : '0')

#define BIT3_TO_BINARY(byte) \
  (byte & 0x04 ? '1' : '0'), \
  (byte & 0x02 ? '1' : '0'), \
  (byte & 0x01 ? '1' : '0')

#define BIT4_TO_BINARY(byte) \
    (byte & 0x08 ? '1' : '0'), \
    (byte & 0x04 ? '1' : '0'), \
    (byte & 0x02 ? '1' : '0'), \
    (byte & 0x01 ? '1' : '0')


struct ui_t* ui_init(uint16_t width, uint16_t height){

    static struct ui_t* ui = NULL;


    if(ui == NULL) {

        ui = (struct ui_t*) malloc(sizeof (struct ui_t));
        SDL_Init(SDL_INIT_EVERYTHING);

        ui->window = SDL_CreateWindow("MICROASSEMBLY",
                                      SDL_WINDOWPOS_UNDEFINED,
                                      SDL_WINDOWPOS_UNDEFINED,
                                       width,
                                      height,
                                      SDL_WINDOW_SHOWN);

        ui->renderer = SDL_CreateRenderer(ui->window,
                                          -1,
                                          SDL_RENDERER_ACCELERATED);

        SDL_Surface* chs = SDL_LoadBMP("../cs8x8.bmp");
        ui->charset = SDL_CreateTextureFromSurface(ui->renderer,chs);
        ui->width = width;
        ui->height = height;

        ui->run = 1;

    }


    return ui;
}

struct ui_t* ui_handle(struct ui_t* ui){

    SDL_Event e;
    SDL_PollEvent(&e);

    switch (e.type) {

        case SDL_QUIT:
            ui->run = 0;
            break;


    }

    return ui;


}


/*
 * hardcoded ui function idk
 */

struct ui_t *ui_render(struct ui_t *ui, struct bus_t *bus) {

    SDL_SetRenderDrawColor(ui->renderer,
                           0,0,0xFF, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(ui->renderer);


    char RA[256] = {0 };
    char RB[256] = {0 };
    char RC[256] = { 0 };
    char RI[256] = { 0 };
    char RO[256] = { 0 };
    char S_MICROCYCLE[256] = { 0 };
    char S_CYCLE[256] = { 0 };

    SPRINTF_REGISTER('A',RA);
    DRAW_REGISTER(RA,ui->height/10 + ui->height/20 * 1);

    SPRINTF_REGISTER('B',RB);
    DRAW_REGISTER(RB,ui->height/10 + ui->height/20* 2);

    SPRINTF_REGISTER('C',RC);
    DRAW_REGISTER(RC,ui->height/10 + ui->height/20 * 3);

    SPRINTF_REGISTER('I',RI);
    DRAW_REGISTER(RI,ui->height/10 + ui->height/20 * 4);

    SPRINTF_REGISTER('O',RO);
    DRAW_REGISTER(RO,ui->height/10 + ui->height/20 * 5);


//    sprintf(RB, "RB %c%c%c%c", BIT4_TO_BINARY(bus->RB));

//    ui = ui_draw_string(ui, RB, 2 * ui->width / 3, ui->height / 10 + ui->height / 20, 3);


    sprintf(S_MICROCYCLE, "%c %c", BIT2_TO_BINARY(bus->selected_microcycle));


    ui = ui_draw_string(ui,"REGISRS", ui->width * 2 / 3, ui->height/10,3);
    ui = ui_draw_string(ui,"RAM", 0, ui->height/10 - ui->height/20, 3);
    ui = ui_draw_string(ui,"III",0,ui->height/10,3);
    ui = ui_draw_string(ui,"MICROCYCLES",ui->width/8,ui->width/10,3);

    ui = ui_draw_string(ui, "INS", 0, ui->height /2 + ui->width/10,3);
    ui = ui_draw_string(ui, "TRA REC ALU", ui->width/8, ui->height/2 + ui->width/10, 3);

    ui = ui_draw_string(ui,"K K", 0, ui->height/3 * 2, 3);
    ui = ui_draw_string(ui, "CBA CBA W W", ui->width/8, ui->height/3 * 2, 3);
    ui = ui_draw_string(ui, S_MICROCYCLE, 0, ui->height/3 * 2 + ui->height/20,3 );

    for(uint8_t i = 0; i < INSTRUCTIONS/4; i++){

        int posy = ui->height/10 + (i+1) * ui->height/20;

        char label[256] = { 0 };
        char data[256] = { 0 };



        sprintf(label, BIT3_TO_BINARY_PATTERN, BIT3_TO_BINARY(i));
        sprintf(data,"%02x %02x %02x %02x",
                bus->instructions[4 * i],
                bus->instructions[4 * i + 1],
                bus->instructions[4 * i + 2],
                bus->instructions[4 * i + 3]);




        ui = ui_draw_string(ui,label,0,posy,3);
        ui = ui_draw_string(ui,data,ui->width/8,posy,3);

    }




    SDL_RenderPresent(ui->renderer);

    return ui;
}


struct ui_t* ui_draw_string(struct ui_t* ui, const char* str, uint16_t posx, uint16_t posy, uint8_t scale){

    while (*str) {

        int c = *str % 255;
        int px = (c % 16) * 8;
        int py = (c / 16) * 8;

        SDL_Rect letterRect = { px,py,8,8 };
        SDL_Rect posRect = { posx,posy,scale * 8,scale * 8 };
        SDL_RenderCopy(ui->renderer, ui->charset, &letterRect, &posRect);

        posx += scale * 8;
        str++;

    }

    return ui;

}