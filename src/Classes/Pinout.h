#ifndef CLFW_PINOUT_H
#define CLFW_PINOUT_H

#include <stdint.h>

struct pinout {
    uint8_t up         ;
    uint8_t down       ;
    uint8_t left       ;
    uint8_t right      ;
    uint8_t modX       ;
    uint8_t modY       ;
    uint8_t start      ;
    uint8_t select     ;
    uint8_t home       ;
    uint8_t a          ;
    uint8_t b          ;
    uint8_t x          ;
    uint8_t y          ;
    uint8_t l1         ;
    uint8_t r1         ;
    uint8_t l2         ;
    uint8_t r2         ;
    uint8_t lightshield;
    uint8_t midshield  ;
    uint8_t cUp        ;
    uint8_t cDown      ;
    uint8_t cLeft      ;
    uint8_t cRight     ;
};

#endif