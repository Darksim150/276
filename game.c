#include <stdlib.h>
#include "SDL.h"
#include "SDL_image.h"
#include "graphics.h"
#include "entity.h"

extern SDL_Surface *screen;
extern SDL_Surface *buffer; /*pointer to the draw buffer*/
extern SDL_Rect Camera;
extern Entity* player;

void Init_All();

/*this program must be run from the directory directly below images and src, not from within src*/
/*notice the default arguments for main.  SDL expects main to look like that, so don't change it*/
int main(int argc, char *argv[])
{
  SDL_Surface *temp;
  SDL_Surface *bg;
  int done;
  int keyn;
  Uint8 *keys;
  Init_All();
  temp = IMG_Load("images/bg.png");/*notice that the path is part of the filename*/
  if(temp != NULL)						/*ALWAYS check your pointers before you use them*/
    bg = SDL_DisplayFormat(temp);
  SDL_FreeSurface(temp);
  if(bg != NULL)
    SDL_BlitSurface(bg,NULL,buffer,NULL);
  player = InitEnt(player, 410, 310, 0, 0, "images/joojoo_no_color.png",360,240);
  done = 0;
  do
  {
    ResetBuffer ();
    SDL_PumpEvents();
    keys = SDL_GetKeyState(&keyn);	
	Pull(keys, player);
	Draw(screen, player);
    NextFrame();
    if(keys[SDLK_ESCAPE] || keys[SDL_QUIT])done = 1;
  }while(!done);
  FreeEnt(player);
  exit(0);		/*technically this will end the program, but the compiler likes all functions that can return a value TO return a value*/
  return 0;
}

void CleanUpAll()
{
  CloseSprites();
  /*any other cleanup functions can be added here*/ 
}

void Init_All()
{
  Init_Graphics();
  atexit(CleanUpAll);
}

