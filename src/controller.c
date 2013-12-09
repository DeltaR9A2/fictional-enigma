#include "controller.h"

const uint32_t BTN_L =    0x00000001;
const uint32_t BTN_R =    0x00000002;
const uint32_t BTN_U =    0x00000004;
const uint32_t BTN_D =    0x00000008;
    
const uint32_t BTN_A =    0x00000010;
const uint32_t BTN_B =    0x00000020;
const uint32_t BTN_X =    0x00000040;
const uint32_t BTN_Y =    0x00000080;
    
const uint32_t BTN_LB =   0x00000100;
const uint32_t BTN_RB =   0x00000200;
const uint32_t BTN_LT =   0x00000400;
const uint32_t BTN_RT =   0x00000800;
    
const uint32_t BTN_LS =   0x00001000;
const uint32_t BTN_RS =   0x00002000;
const uint32_t BTN_BACK = 0x00004000;
const uint32_t BTN_NEXT = 0x00008000;

const uint32_t BTN_NONE = 0x00000000;

bool controller_pressed(controller_t *c, uint32_t buttons){
    return ((c->pressed & buttons) == buttons);
}

bool controller_released(controller_t *c, uint32_t buttons){
    return !((c->pressed & buttons) == buttons);
}

bool controller_just_pressed(controller_t *c, uint32_t buttons){
    return ((c->pressed & buttons) == buttons) && !((c->previous & buttons) == buttons);
}

bool controller_just_released(controller_t *c, uint32_t buttons){
    return !((c->pressed & buttons) == buttons) && ((c->previous & buttons) == buttons);
}

void controller_reset(controller_t *c){
    c->pressed = BTN_NONE;
    c->previous = BTN_NONE;
}

void controller_poll_events(controller_t *c){
    SDL_Event e;

    c->previous = c->pressed;
    while(SDL_PollEvent(&e)){
        if(e.type == SDL_KEYDOWN){
            switch(e.key.keysym.scancode){
            case SDL_SCANCODE_W:
                c->pressed |= BTN_U; break;
            case SDL_SCANCODE_S:
                c->pressed |= BTN_D; break;
            case SDL_SCANCODE_A:
                c->pressed |= BTN_L; break;
            case SDL_SCANCODE_D:
                c->pressed |= BTN_R; break;
            case SDL_SCANCODE_SPACE:
                c->pressed |= BTN_A; break;
            case SDL_SCANCODE_X:
                c->pressed |= BTN_B; break;
            case SDL_SCANCODE_C:
                c->pressed |= BTN_X; break;
            case SDL_SCANCODE_V:
                c->pressed |= BTN_Y; break;
            case SDL_SCANCODE_Q:
                c->pressed |= BTN_LB; break;
            case SDL_SCANCODE_E:
                c->pressed |= BTN_RB; break;
            case SDL_SCANCODE_1:
                c->pressed |= BTN_LT; break;
            case SDL_SCANCODE_3:
                c->pressed |= BTN_RT; break;
            case SDL_SCANCODE_RETURN:
                c->pressed |= BTN_NEXT; break;
            case SDL_SCANCODE_BACKSPACE:
                c->pressed |= BTN_BACK; break;
            default:
                break;
            }
        }else if(e.type == SDL_KEYUP){
            switch(e.key.keysym.scancode){
            case SDL_SCANCODE_W:
                c->pressed &= ~BTN_U; break;
            case SDL_SCANCODE_S:
                c->pressed &= ~BTN_D; break;
            case SDL_SCANCODE_A:
                c->pressed &= ~BTN_L; break;
            case SDL_SCANCODE_D:
                c->pressed &= ~BTN_R; break;
            case SDL_SCANCODE_SPACE:
                c->pressed &= ~BTN_A; break;
            case SDL_SCANCODE_X:
                c->pressed &= ~BTN_B; break;
            case SDL_SCANCODE_C:
                c->pressed &= ~BTN_X; break;
            case SDL_SCANCODE_V:
                c->pressed &= ~BTN_Y; break;
            case SDL_SCANCODE_Q:
                c->pressed &= ~BTN_LB; break;
            case SDL_SCANCODE_E:
                c->pressed &= ~BTN_RB; break;
            case SDL_SCANCODE_1:
                c->pressed &= ~BTN_LT; break;
            case SDL_SCANCODE_3:
                c->pressed &= ~BTN_RT; break;
            case SDL_SCANCODE_RETURN:
                c->pressed &= ~BTN_NEXT; break;
            case SDL_SCANCODE_BACKSPACE:
                c->pressed &= ~BTN_BACK; break;
            default:
                break;
            }
        }
    }
}
