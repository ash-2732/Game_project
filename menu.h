#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <string>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include <sstream>
#include <algorithm>
// #include "initial.h"
// #include "media.h"


int mainMenu(SDL_Event e)
{

	int gameState;
	while( SDL_PollEvent( &e ) != 0 )
	{   

		if( e.type == SDL_QUIT )
		{
			gameState=4;
		}

		else if(e.type == SDL_MOUSEBUTTONDOWN){
				//printf("%d %d\n", e.button.x, e.button.y);

			if(e.button.x > (139*SCREEN_WIDTH)/1280 && e.button.x < (527*SCREEN_WIDTH)/1280 && e.button.y > (521*SCREEN_HEIGHT)/720 && e.button.y < (574*SCREEN_HEIGHT)/720){
				gameState = 1;
				Mix_OpenAudio(44100,MIX_DEFAULT_FORMAT,2,2048);
	    			// load music
				Mix_Music*backgroundSound=Mix_LoadMUS("FINE.mp3");
				Mix_PlayMusic(backgroundSound, -1);

			}
			else if(e.button.x > (631*SCREEN_WIDTH)/1280 && e.button.x < (1259*SCREEN_WIDTH)/1280 && e.button.y > (529*SCREEN_HEIGHT)/720 && e.button.y < (572*SCREEN_HEIGHT)/720){
				gameState = 2;
			}
			else if(e.button.x > (18*SCREEN_WIDTH)/1280 && e.button.x < (759*SCREEN_WIDTH)/1280 && e.button.y > (623*SCREEN_HEIGHT)/720 && e.button.y < (672*SCREEN_HEIGHT)/720){
				gameState = 3;
			}
			else if(e.button.x > (834*SCREEN_WIDTH)/1280 && e.button.x < (1103*SCREEN_WIDTH)/1280 && e.button.y > (627*SCREEN_HEIGHT)/720 && e.button.y < (678*SCREEN_HEIGHT)/720){
				gameState = 4;
			}
		}
	}
	//Clear screen
	//SDL_RenderClear( gRenderer );
	SDL_RenderCopy( gRenderer, gmenuTexture, NULL, NULL );
	//Update screen
	SDL_RenderPresent( gRenderer );
	return gameState;
}
