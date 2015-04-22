#include "entity.h"

Entity EntityList[1000];
Entity* player;

Entity* InitEnt(Entity *ent, int x, int y, int vy, int onGround, char* image, int xframe, int yframe)
{
	ent = (Entity*)malloc(sizeof(Entity));
	ent->x = x;
	ent->y = y;
	ent->vy = vy;
	ent->flag = IDLE;
	ent->spr = LoadSprite(image, xframe, yframe);
	ent->frame = 0;
	ent->used = 1;
	ent->onGround = 0;
	return ent;
}
void Move(Entity* ent)
{
	if(ent->flag == WALK)
		ent->x = ent->x + 10;
	if(ent->flag == WALKL)
		ent->x = ent->x - 10;

	if(ent->flag == JUMP){

		ent->vy = -30;
	}

	ent->y = ent->y + ent->vy;
	ent->vy += 2;

	if(ent->y > 500){
		ent->y = 500;
		ent->vy = 0;
		ent->onGround = 1;
	}
	else if(ent->y < 500)
		ent->onGround = 0;
}
void FreeEnt(Entity* ent)
{
	FreeSprite(ent->spr);
	ent->x = NULL;
	ent->y = NULL;
	ent->flag = NULL;
	ent->spr = NULL;
	ent->used = 0;
}

void Pull(Uint8* keys, Entity* ent)
{
	if(keys[SDLK_RIGHT])
	{
		ent->flag = WALK;
	}
	else if(keys[SDLK_LEFT])
	{
		ent->flag = WALKL;
	}
	
	else {
		ent->flag = IDLE;
	}

	if(keys[SDLK_SPACE])
	{
		if(ent->onGround == 1)
		{
			ent->flag = JUMP;
		}
		
	}

	Move(ent);

}
void Draw(SDL_Surface* screen, Entity* ent)
{
	if(ent->onGround == 0)
	{
		DrawSprite(ent->spr, screen, ent->x, ent->y, ent->frame+62);
		ent->frame = (ent->frame + 1)%6;
	}
	else if(ent->flag == WALK)
	{
		DrawSprite(ent->spr, screen, ent->x, ent->y, ent->frame+29);
		ent->frame = (ent->frame + 1)%12;
	}
	else if(ent->flag == WALKL)
	{
		DrawSprite(ent->spr, screen, ent->x, ent->y, ent->frame+44);
		ent->frame = (ent->frame + 1)%12;
	}
	else if(ent->flag == JUMP)
	{
		DrawSprite(ent->spr, screen, ent->x, ent->y, ent->frame+62);
		ent->frame = (ent->frame + 1)%6;
	}
	else
	{
		DrawSprite(ent->spr, screen, ent->x, ent->y, ent->frame);
		ent->frame = (ent->frame + 1)%5;
	}

}