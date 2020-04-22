#ifndef GAME_H
#define GAME_H

typedef struct
{
    double x;
    double y;
    double angle;
    double scale;
} coord_t;

void reset_sim();

void update_sim();

void get_coord_earth();

void get_coord_rocket();

void get_coord_satellite();

void get_coord_fire();

#endif /* GAME_H */