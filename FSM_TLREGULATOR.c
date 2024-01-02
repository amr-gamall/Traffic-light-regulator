#include"config.h"
#include<xc.h>

#define _XTAL_FREQ 2000000
#define NO 0b100001 // state 0 (initial state)
#define NW 0b010001 // state 1
#define EO 0b001100 // state 2
#define EW 0b001010 // state 3

struct state{
    short LED;
    short next_state[4];
};
const struct state states[4] = {
    {NO, {0b00,0b01, 0b00, 0b01}},
    {NW, {0b10, 0b10, 0b10, 0b10}},
    {EO, {0b10, 0b10, 0b11, 0b11}},
    {EW, {0b00, 0b00, 0b00, 0b00}}
};
void set_leds(short current_state){
    short led_out = states[current_state].LED;
    RD1 = led_out & 0b000001?1 : 0;
    RD2 = led_out & 0b000010?1 : 0;
    RD3 = led_out & 0b000100?1 : 0;
    RD4 = led_out & 0b001000?1 : 0;
    RD5 = led_out & 0b010000?1 : 0;
    RD6 = led_out & 0b100000?1 : 0;
}

void main(void){
    TRISB0 = 1;TRISB1 = 1; //sensor buffers as input
    TRISD1 = 0;TRISD2 = 0;TRISD3 = 0;TRISD4 = 0;TRISD5 = 0;TRISD6 = 0;//leds buffer as output
    int current_state = 0b00;// initial state set to NO;        
    while(1){
        set_leds(current_state);
        __delay_ms(700);
        short tmp = RB1 << 1;
        short sensor = tmp | RB0; // getting sensor data
        current_state = states[current_state].next_state[sensor];
    }
    
}
