#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <string>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include <sstream>
#include <algorithm>


//SDL_Renderer* gRenderer = NULL;

SDL_Texture* loadTexture( std::string path )
{
    //The final texture
	SDL_Texture* newTexture = NULL;

    //Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
	if( loadedSurface == NULL )
	{
		printf( "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError() );
	}
	else
	{
        //Create texture from surface pixels
		newTexture = SDL_CreateTextureFromSurface( gRenderer, loadedSurface );
		if( newTexture == NULL )
		{
			printf( "Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
		}
        //Get rid of old loaded surface
		SDL_FreeSurface( loadedSurface );
	}
	return newTexture;
}
