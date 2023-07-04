#include<16f887.h>
#include<stdlib.h>
#fuses hs, put, noprotect, nowdt
#use delay(clock=20MHz)

#define laser_signal    pin_c5
#define laser_output    pin_b0
#define buzzer          pin_d0
#define door            pin_b2
#define led_door        pin_c0
#define led_liquid      pin_c1
#define led_set         pin_c2
#define truong_hop      pin_b1

#define dir             pin_a4
#define step            pin_a5
#define m1              pin_e0
#define m0              pin_e1
#define enable_motor    pin_e2

#define motor_a0     pin_c6
#define motor_a1     pin_c7
#define motor_b0     pin_c3
#define motor_b1     pin_c4
   
#include<tv_key_matrix_4x4.c>

#define LCD_RS_PIN      PIN_D1
#define LCD_RW_PIN      PIN_D2
#define LCD_ENABLE_PIN  PIN_D3
#define  LCD_DATA4      PIN_D4
#define  LCD_DATA5      PIN_D5
#define  LCD_DATA6      PIN_D6
#define  LCD_DATA7      PIN_D7
#include<lcd.c>
