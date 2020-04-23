#include <stdbool.h>
#include <stdint.h>
#include <math.h>

#include "game.h"

uint32_t g_ticks = 0;

void reset_sim( uint32_t ticks )
{
    g_ticks = ticks;
}

void update_sim( uint32_t ticks, int8_t pitch, bool burn )
{
    uint32_t delta_ticks = ticks - g_ticks;
    g_ticks = ticks;
}