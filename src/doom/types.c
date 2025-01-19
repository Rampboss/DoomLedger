#include "doom/types.h"

#define PIC_COORDS(x) ((Coords*) (PIC(x)))

Coords create_coords(double x, double y) {
  Coords c = { x, y };
  return c;
}

void set_coords(Coords *c, double x, double y) {
  c->x = x;
  c->y = y;
}

float coords_distance(Coords* a, Coords* b) {
  if(PIC_COORDS(a)->x == PIC_COORDS(b)->x && PIC_COORDS(a)->y == PIC_COORDS(b)->x)
    return 0.0f;
  return sqrt_optimized(pow(PIC_COORDS(a)->x - PIC_COORDS(b)->x,2) + pow(PIC_COORDS(a)->y - PIC_COORDS(b)->y,2)) * DISTANCE_MULTIPLIER;
}

UID create_uid(uint8_t type, uint8_t x, uint8_t y) {
  return ((y << LEVEL_WIDTH_BASE) | x) << 4 | type;
}
  
uint8_t uid_get_type(UID uid) {
  return uid & 0x0F;
}
