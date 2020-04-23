#ifndef GAME_H
#define GAME_H

#include <stdint.h>

typedef struct
{
    double x;
    double y;
    double angle;
    double scale;
} coord_t;

void reset_sim( uint32_t ticks );

void update_sim( uint32_t ticks, int8_t pitch, bool burn );

void get_coord_earth( coord_t* c );

void get_coord_rocket( coord_t* c );

void get_coord_satellite( coord_t* c );

void get_coord_fire( coord_t* c );

#endif /* GAME_H */