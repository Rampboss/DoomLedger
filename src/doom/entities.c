#include "doom/entities.h"

void set_player(Player *p, uint8_t x, uint8_t y) {
  set_coords(&p->pos ,(double) x + (double)0.5, (double) y + (double)0.5);
  p->dir = create_coords(1.0,0.0);
  p->keys = 0;
  p->health= 100;
  p->plane = create_coords(0.0, -0.66);
  p->velocity = 0;
}

Entity create_entity(uint8_t type, uint8_t x,  uint8_t y, uint8_t initialState, uint8_t initialHealth) {
  UID uid = create_uid(type, x, y);
  Coords pos = create_coords((double) x + 0.5, (double) y + 0.5);
  Entity new_entity = { uid, pos, initialState, initialHealth, 0, 0 };
  return new_entity;
}