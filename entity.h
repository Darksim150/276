#ifndef ENTITY_H
#define ENTITY_H

#include "graphics.h"

#define IDLE	0
#define WALK	1
#define	JUMP	2
#define WALKL	4

typedef struct Entity_T
{
	int used;
	Sprite* spr;
	int x;
	int y;
	int vy;
	int onGround;
	long flag;
	int frame;
}Entity;

Entity* InitEnt(Entity *ent, int x, int y, int vy, int onGround, char* image, int xframe, int yframe);
void Move(Entity* ent);
void FreeEnt(Entity* ent);
void Pull(Uint8* keys, Entity* ent);
void Draw(SDL_Surface* screen, Entity* ent);

#endif