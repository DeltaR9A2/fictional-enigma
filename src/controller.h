#ifndef controller_h
#define controller_h

#include <stdbool.h>

#include <SDL2/SDL.h>

extern const uint32_t BTN_L;
extern const uint32_t BTN_R;
extern const uint32_t BTN_U;
extern const uint32_t BTN_D;
    
extern const uint32_t BTN_A;
extern const uint32_t BTN_B;
extern const uint32_t BTN_X;
extern const uint32_t BTN_Y;
    
extern const uint32_t BTN_LB;
extern const uint32_t BTN_RB;
extern const uint32_t BTN_LT;
extern const uint32_t BTN_RT;
    
extern const uint32_t BTN_LS;
extern const uint32_t BTN_RS;
extern const uint32_t BTN_BACK;
extern const uint32_t BTN_STRT;

extern const uint32_t BTN_NONE;

typedef struct controller_t controller_t;
struct controller_t{
    uint32_t pressed;
    uint32_t previous;
};

controller_t *controller_create(void);
void controller_delete(controller_t *controller);

void controller_reset(controller_t *c);
void controller_poll_events(controller_t *c);

bool controller_pressed(controller_t *c, uint32_t buttons);
bool controller_released(controller_t *c, uint32_t buttons);

bool controller_just_pressed(controller_t *c, uint32_t buttons);
bool controller_just_released(controller_t *c, uint32_t buttons);

#endif
