#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <string>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include <sstream>
#include <algorithm>

TTF_Font* Sans =NULL;
SDL_Texture* loadTexture( std::string path );

SDL_Texture* gBGTexture = NULL;
SDL_Texture* gCARTexture[5] = {NULL};
SDL_Texture* gmenuTexture=NULL;
SDL_Texture* ghighscoreTexture=NULL;
SDL_Texture* ginstructionTexture = NULL;
SDL_Texture* glifeTexture=NULL;
SDL_Texture* glife1Texture=NULL;
SDL_Texture* gboyTexture=NULL;
SDL_Texture* gGameTexture = NULL;
SDL_Texture* glevel2Texture= NULL;
SDL_Texture* glevel1Texture= NULL;
SDL_Texture* gloadingTexture= NULL;
SDL_Texture* glevel3Texture= NULL;
SDL_Texture* gcoinTexture=NULL;
SDL_Texture* gcoin1Texture=NULL;


bool loadMedia()
{
	//Loading success flag
	bool success = true;

	//Load background image
	gBGTexture=loadTexture( "background.bmp" );
	if( gBGTexture== NULL )
	{
		printf( "Unable to load image %s! SDL Error: %s\n", "background.bmp", SDL_GetError() );
		success = false;
	}
	//Load menu and instruction
	gmenuTexture=loadTexture("menu.png");
	ghighscoreTexture=loadTexture("highscore.png");
	ginstructionTexture=loadTexture("instruction.png");
	glevel2Texture=loadTexture("lv2.png");
	glevel1Texture=loadTexture("lv1.png");
	gloadingTexture=loadTexture("loading.bmp");
	glevel3Texture=loadTexture("lv3.png");
	gGameTexture=loadTexture("GameOver.png");
	//Load car
	gCARTexture[0]=loadTexture( "bike.png" );
	gCARTexture[1]=loadTexture( "10.png" );
	gCARTexture[2]=loadTexture( "carwhite.bmp" );
	gCARTexture[3]=loadTexture( "ultacar.jpg" );
	gCARTexture[4]=loadTexture( "carash.bmp" );
    //load other things	
	glifeTexture=loadTexture("life.bmp");
	glife1Texture=loadTexture("life1.bmp");
	gboyTexture=loadTexture("truck.png");
	gcoinTexture=loadTexture("coin.bmp");
	gcoin1Texture=loadTexture("coin1.bmp");
	Sans = TTF_OpenFont("my.ttf",20);
	return success;
}
