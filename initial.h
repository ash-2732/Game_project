#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <string>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include <sstream>
#include <algorithm>

const int SCREEN_WIDTH = 1240;
const int SCREEN_HEIGHT = 720;

SDL_Window* gWindow = NULL;
SDL_Renderer* gRenderer = NULL;

 bool init()
{
	//Initialization flag
	Mix_OpenAudio(44100,MIX_DEFAULT_FORMAT,2,2048);
	    			// load music
								Mix_Music*backgroundSound=Mix_LoadMUS("bike.mp3");
								Mix_PlayMusic(backgroundSound, -1);
	bool success = true;

	//Initialize SDL
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
		printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
		success = false;
	}
	else
	{
		//Create window
		gWindow = SDL_CreateWindow( "UNLIMITED RACING", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
		if( gWindow == NULL )
		{
			printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
			success = false;
		}
		else
		{
			
			gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
			if( gRenderer == NULL )
			{
				printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
				success = false;
			}
			else
			{
                //Initialize renderer color

				SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
			}
			TTF_Init();
		}

	}
	return success;
}
